/*
 *  Soubor: bit_array.h
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

typedef unsigned long bit_array_t[];

/*
 * Velikost unsigned long v bitech
 */
#define BIT_SIZE (sizeof(unsigned long) * __CHAR_BIT__)

/*
 * Makra pro praci s bitovym polem
 */

#define bit_array_create(array, size) unsigned long array[((size + 1) / BIT_SIZE) + ((size + 1) % BIT_SIZE > 0 ? 1 : 0) + 1] = {size, 0}

#ifndef USE_INLINE

#define bit_array_size(array) array[0]

#define bit_array_setbit(array, index, value) \
    do\
    {\
      if((unsigned)index > bit_array_size(array)) \
        error_exit("Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bit_array_size(array)); \
        else if(value == 1) \
          array[index / BIT_SIZE + 1] |= (1UL << index % BIT_SIZE); \
        else if(value == 0) \
          array[index / BIT_SIZE + 1] ^= (1UL << index % BIT_SIZE); \
    }while(0)


#define bit_array_getbit(array, index)((unsigned)index > bit_array_size(array)) ? error_exit("Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bit_array_size(array)), 2 : (array[index / BIT_SIZE + 1] & 1UL << index % BIT_SIZE) / (1UL << index % BIT_SIZE)

#endif

/*
 *  INLINE funkce pro praci s bitovym polem
 */

#ifdef USE_INLINE

static inline unsigned long bit_array_size(bit_array_t array)
{
  return array[0];
}

static inline void bit_array_setbit(bit_array_t array, int index, char value)
{
  if((unsigned)index > bit_array_size(array) || index < 0)
    error_exit("Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bit_array_size(array));
  else if(value == 1)
    array[index / BIT_SIZE + 1] |= (1UL << index % BIT_SIZE);
  else if(value == 0)
    array[index / BIT_SIZE + 1] ^= (1UL << index % BIT_SIZE);
}

static inline char bit_array_getbit(bit_array_t array, int index)
{
  if((unsigned)index > bit_array_size(array) || index < 0)
  {
    error_exit("Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bit_array_size(array));
    return 1;
  }
  else
    return (array[index / BIT_SIZE + 1] & 1UL << index % BIT_SIZE) / (1UL << index % BIT_SIZE);
}

#endif
