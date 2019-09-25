/**
 * Project: IFJ18 compiler implementation.
 *
 * Symtable implementation.
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */


#include"symtable.h"

//Symtable init size -> should be prime number
#define SYM_TAB_SIZE 1543

/*
 * Generates ID of given key
 *
 * str    key from which ID is generated
 *
 * return ID of given key
 */
unsigned symTabHashFunction(const char *str)
{
  unsigned int h=0;
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
    h = 65599*h + *p;
  return h % SYM_TAB_SIZE;
}

/*
 * Initialize symtable
 *
 * return pointer to initialized symtable or NULL
 */
symTab *symTabInit()
{
  symTab* table = malloc(sizeof(symTab));
	if(!table)
  {
    errorMsg("Failed memory allocation for table.\n");
    return NULL;
  }

  if(!(table->item = calloc(SYM_TAB_SIZE, sizeof(symTabListItem))))
  {
    errorMsg("Failed memory allocation array of items in table.\n");
    free(table);
    return NULL;
  }
  table->size = 0;
	return table;
}

/*
 * Adds new item to symtable with given key.
 * If item with the same key already exists, returns pointer to this item.
 *
 * t    pointer to symtable
 * key  key of item, which is about to be added
 *
 * return pointer to added item or NULL if memory allocation fails
 */
symTabListItem *symTabAdd(symTab *t, const char *key)
{
  //Symtable must be initialized
  if(!t || !key)
  {
    errorMsg("Table or key is NULL\n");
    return NULL;
  }

  //Getting ID for hash table
  unsigned index = symTabHashFunction(key);
  symTabListItem *item = t->item[index];
  symTabListItem *prevItem = NULL;

  //There is no item on this index yet
  if(!item)
  {
    if(!(item = malloc(sizeof(symTabListItem))))
    {
      errorMsg("Failed memory allocation for item in table.\n");
      return NULL;
    }

    if(!(item->key = malloc(strlen(key)+1)))
    {
      errorMsg("Failed memory allocation for key\n");
      free(item);
      return NULL;
    }

    if(!(item->sData.ID = malloc(strlen(key)+1)))
    {
      errorMsg("Failed memory allocation for ID\n");
      free(item);
      return NULL;
    }

    //Initialize data of item
    strcpy(item->key, key);
    strcpy(item->sData.ID, key);
    item->sData.defined = false;
    item->sData.firstCalled = false;
    item->sData.params = 0;
    item->next = NULL;
    t->item[index] = item;
    t->size++;
  }
  //There is already an item on given index
  else
  {
    //Searching for item with given key
    while(item)
    {
      if(!strcmp(item->key, key))
      {
        //Item with given key found -> return pointer on it
        return item;
      }
      prevItem = item;
      item = item->next;
    }

    //We didn't find item with given key -> add new item with this key to table
    if(!(item = malloc(sizeof(symTabListItem))))
    {
      errorMsg("Failed memory allocation for item in table.\n");
      return NULL;
    }

    if(!(item->key = malloc(strlen(key)+1)))
    {
      errorMsg("Failed memory allocation for key\n");
      free(item);
      return NULL;
    }

    if(!(item->sData.ID = malloc(strlen(key)+1)))
    {
      errorMsg("Failed memory allocation for ID\n");
      free(item);
      return NULL;
    }

    //Initialize data of item
    strcpy(item->key, key);
    strcpy(item->sData.ID, key);
    item->next = NULL;
    prevItem->next = item;
    t->size++;
  }
  //Returning pointer to newly added item
  return item;
}

/*
 * Searches for item with given key
 *
 * t    pointer to symtable
 * key  key of item we want to find
 *
 * return pointer to found item or NULL
 */
symTabListItem *symTabFind(symTab *t, const char *key)
{
  //Symtable must be initialized
  if(!t || !key)
  {
    errorMsg("Table or key is NULL\n");
    return NULL;
  }

  //Getting ID for hash table
  unsigned index = symTabHashFunction(key);
  symTabListItem *item = t->item[index];

  //Searching for item with given key
  while(item)
  {
    if(!strcmp(item->key, key))
    {
      //Item with given key found -> return pointer on it
      return item;
    }
    item = item->next;
  }
  //Item with given key not found -> return NULL
  return NULL;
}

/*
 * Deletes and frees all items from symtable
 *
 * t    pointer to symtable
 *
 */
void symTabClear(symTab *t)
{
  //Symtable must be initialized
  if(!t)
  {
    return;
  }

  symTabListItem *item;
  symTabListItem *tmpItem;

  //Clearing items on each ID
  for(unsigned i = 0; i < SYM_TAB_SIZE; i++)
  {
    item = t->item[i];
    while(item)
    {
      tmpItem = item->next;
      free(item->key);
      free(item->sData.ID);
      free(item);
      item = tmpItem;
    }
    t->item[i] = NULL;
  }
}

/*
 * Disposes symtable
 *
 * t    pointer to symtable
 */
void symTabFree(symTab *t)
{
  if(t)
  {
    symTabClear(t);
    free(t->item);
    free(t);
  }
}
