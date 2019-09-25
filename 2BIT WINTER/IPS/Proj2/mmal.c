//xvenkr01
//xfrejl00

#include <stdio.h>
#include "mmal.h"
#include <sys/mman.h> // mmap
#include <stdbool.h> // bool
#include <assert.h> // assert

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#endif

#ifdef NDEBUG
/**
 * The structure header encapsulates data of a single memory block.
 *   ---+------+----------------------------+---
 *      |Header|DDD not_free DDDDD...free...|
 *   ---+------+-----------------+----------+---
 *             |-- Header.asize -|
 *             |-- Header.size -------------|
 */
typedef struct header Header;
struct header {

	/**
	 * Pointer to the next header. Cyclic list. If there is no other block,
	 * points to itself.
	 */
	Header *next;

	/// size of the block
	size_t size;

	/**
	 * Size of block in bytes allocated for program. asize=0 means the block
	 * is not used by a program.
	 */
	size_t asize;
};

/**
 * The arena structure.
 *   /--- arena metadata
 *   |     /---- header of the first block
 *   v     v
 *   +-----+------+-----------------------------+
 *   |Arena|Header|.............................|
 *   +-----+------+-----------------------------+
 *
 *   |--------------- Arena.size ---------------|
 */
typedef struct arena Arena;
struct arena {

	/**
	 * Pointer to the next arena. Single-linked list.
	 */
	Arena *next;

	/// Arena size.
	size_t size;
};

#define PAGE_SIZE (128*1024)

#endif // NDEBUG

Arena *first_arena = NULL;

/**
 * Return size alligned to PAGE_SIZE
 */
static
size_t allign_page(size_t size)
{
	return ((size-1)/(PAGE_SIZE) + 1) * (PAGE_SIZE);
}

/**
 * Allocate a new arena using mmap.
 * @param req_size requested size in bytes. Should be alligned to PAGE_SIZE.
 * @return pointer to a new arena, if successfull. NULL if error.
 * @pre req_size > sizeof(Arena) + sizeof(Header)
 */

/**
 *   +-----+------------------------------------+
 *   |Arena|....................................|
 *   +-----+------------------------------------+
 *
 *   |--------------- Arena.size ---------------|
 */
static
Arena *arena_alloc(size_t req_size)
{
	assert(req_size > sizeof(Arena) + sizeof(Header));

	Arena *arena = mmap(NULL, req_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if(arena == MAP_FAILED)
		return NULL;
	return arena;
}

/**
 * Appends a new arena to the end of the arena list.
 * @param a     already allocated arena
 */
static
void arena_append(Arena *a)
{
	Arena *tmp = first_arena;
	Arena *tmp2;
	while(tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next = a;
}

/**
 * Header structure constructor (alone, not used block).
 * @param hdr       pointer to block metadata.
 * @param size      size of free block
 * @pre size > 0
 */
/**
 *   +-----+------+------------------------+----+
 *   | ... |Header|........................| ...|
 *   +-----+------+------------------------+----+
 *
 *                |-- Header.size ---------|
 */
static
void hdr_ctor(Header *hdr, size_t size)
{
	assert(size > 0);

	hdr->next = NULL;
	hdr->size = size;
	hdr->asize = 0;
}

/**
 * Checks if the given free block should be split in two separate blocks.
 * @param hdr       header of the free block
 * @param size      requested size of data
 * @return true if the block should be split
 * @pre hdr->asize == 0
 * @pre size > 0
 */
static
bool hdr_should_split(Header *hdr, size_t size)
{
	assert(hdr->asize == 0);
	assert(size > 0);

	if(sizeof(Header) * 2 + size <= hdr->size)
		return true;
	return false;
}

/**
 * Splits one block in two.
 * @param hdr       pointer to header of the big block
 * @param req_size  requested size of data in the (left) block.
 * @return pointer to the new (right) block header.
 * @pre   (hdr->size >= req_size + 2*sizeof(Header))
 */
/**
 * Before:        |---- hdr->size ---------|
 *
 *    -----+------+------------------------+----
 *         |Header|........................|
 *    -----+------+------------------------+----
 *            \----hdr->next---------------^
 */
/**
 * After:         |- req_size -|
 *
 *    -----+------+------------+------+----+----
 *     ... |Header|............|Header|....|
 *    -----+------+------------+------+----+----
 *             \---next--------^  \--next--^
 */
static
Header *hdr_split(Header *hdr, size_t req_size)
{
	assert((hdr->size >= req_size + 2*sizeof(Header)));

	Header *split;
	split = (Header*)&(hdr[req_size]);

	hdr_ctor(split, hdr->size - req_size - sizeof(Header));

	split->next = hdr->next;
	hdr->next = split;
	split->size = hdr->size - req_size - sizeof(Header);
	hdr->size = req_size;
	hdr->asize = req_size;

	return split;
}

/**
 * Detect if two adjacent blocks could be merged.
 * @param left      left block
 * @param right     right block
 * @return true if two blocks are free and adjacent in the same arena.
 * @pre left->next == right
 * @pre left != right
 */
static
bool hdr_can_merge(Header *left, Header *right)
{
	assert(left->next == right);
	assert(left != right);

	if(left->asize == 0 && right->asize == 0)
		return true;
	return false;
}

/**
 * Merge two adjacent free blocks.
 * @param left      left block
 * @param right     right block
 * @pre left->next == right
 * @pre left != right
 */
static
void hdr_merge(Header *left, Header *right)
{
	assert(left->next == right);
	assert(left != right);

	left->size = left->size + right->size + sizeof(Header);
	left->next = right->next;
}

/**
 * Finds the first free block that fits to the requested size.
 * @param size      requested size
 * @return pointer to the header of the block or NULL if no block is available.
 * @pre size > 0
 */
static
Header *first_fit(size_t size)
{
	assert(size > 0);
	Header *h1, *h2;
	Arena *tmp = first_arena;
	while(tmp != NULL)
	{
		h1 = (Header*)(&tmp[1]);
		h2 = (Header*)(&tmp[1]);
		do
		{
			if(h2->asize == 0 && h2->size >= size)
			{
				return h2;
			}
			h2 = h2->next;
		} while(h1 != h2);
		tmp = tmp->next;
	}
	return NULL;
}

/**
 * Search the header which is the predecessor to the hdr. Note that if
 * @param hdr       successor of the search header
 * @return pointer to predecessor, hdr if there is just one header.
 * @pre first_arena != NULL
 * @post predecessor->next == hdr
 */
static
Header *hdr_get_prev(Header *hdr)
{
	assert(first_arena != NULL);
	Header *h1 = (Header*)(&first_arena[1]);
	if(h1 == hdr && (h1->next == hdr || h1->next == NULL))
		return hdr;
	while(h1->next != hdr)
		h1 = h1->next;
	return h1;
}

/**
 * Allocate memory. Use first-fit search of available block.
 * @param size      requested size for program
 * @return pointer to allocated data or NULL if error or size = 0.
 */
void *mmalloc(size_t size)
{
	Arena *first_arena_tmp = first_arena;
	Arena *first_arena_tmp_prev;
	//Header *next_header = NULL;
	Header *first_header;

	if(first_arena == NULL)
	{
		first_arena = arena_alloc(allign_page(size + sizeof(Header)+ sizeof(Arena)));
		if(first_arena == NULL)
		{
			return NULL;
		}
		first_arena->next = NULL;
		first_arena->size = allign_page(size + sizeof(Header)+ sizeof(Arena));
		first_header = (Header*)(&first_arena[1]);
		hdr_ctor(first_header, first_arena->size - sizeof(Header) - sizeof(Arena));
		first_header->next = first_header;
	}
	Header *insert = first_fit(size);
	Header *tmp;

	if(insert != NULL && hdr_should_split(insert, size))
	{
		tmp = hdr_split(insert, size);
		tmp = hdr_get_prev(tmp);
		return (((char*)tmp) + sizeof(Header));
	}

	while(1)
	{
		first_arena_tmp_prev = first_arena_tmp;
		first_arena_tmp = first_arena->next;
		if(first_arena_tmp == NULL)
		{
			first_arena_tmp = arena_alloc(allign_page(size + sizeof(Header)+ sizeof(Arena)));
			if(first_arena_tmp == NULL)
			{
				return NULL;
			}
			first_arena_tmp->next = NULL;
			first_arena_tmp->size = allign_page(size + sizeof(Header)+ sizeof(Arena));
			first_header = (Header*)(&first_arena_tmp[1]);
			hdr_ctor(first_header, first_arena_tmp->size - sizeof(Header) - sizeof(Arena));
			first_header->next = first_header;
			first_arena_tmp_prev->next = first_arena_tmp;
		}
		Header *insert_next = first_fit(size);

		Header *tmp_next;

		if(insert_next != NULL && hdr_should_split(insert_next, size))
		{
			tmp_next = hdr_split(insert_next, size);
			tmp_next = hdr_get_prev(tmp_next);
			return (((char*)tmp_next) + sizeof(Header));
		}
	}
}

/**
 * Free memory block.
 * @param ptr       pointer to previously allocated data
 * @pre ptr != NULL
 */
void mfree(void *ptr)
{
	assert(ptr != NULL);

	Header *tmp = ((void*)ptr - sizeof(Header));
	tmp->asize = 0;

	if(hdr_can_merge(tmp, tmp->next))
	{
		hdr_merge(tmp, tmp->next);
	}

	if(tmp != (Header*)(&first_arena[1]))
	{
		Header *tmp_prev = hdr_get_prev(tmp);
		if(hdr_can_merge(tmp_prev, tmp))
		{
			 hdr_merge(tmp_prev, tmp);
		}
	}
}

/**
 * Reallocate previously allocated block.
 * @param ptr       pointer to previously allocated data
 * @param size      a new requested size. Size can be greater, equal, or less
 * then size of previously allocated block.
 * @return pointer to reallocated space or NULL if size equals to 0.
 */
void *mrealloc(void *ptr, size_t size)
{
	// FIXME
	(void)ptr;
	(void)size;
	return NULL;
}
