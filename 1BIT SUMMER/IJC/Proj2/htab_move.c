/*
 *  Soubor: htab_move.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

htab_t *htab_move(int newsize, htab_t *t2)
{
  if(newsize <= 0)
    return NULL;

  htab_t *t = htab_init(newsize); // Vytvoreni a inicializace tabulky
  htab_listitem *old_item;
  htab_listitem *item;
  unsigned oldsize = htab_bucket_count(t2); // Velikost puvodni tabulky

  for(unsigned i = 0; i < oldsize; i++)
  {
    old_item = t2->item[i]; // Ukazatel na zaznam ve stare tabulce
    while(old_item != NULL) // Projde cely seznam na indexu "i"
    {
      item = htab_lookup_add(t, old_item->key); // Pridani zaznamu ze stare tabulku do nove
      if(item == NULL) // Alokace pameti pro polozku selhala -> zruseni tabulky
      {
        htab_free(t);
        fprintf(stderr, "ERROR: Allocating memory faile.\n");
        return NULL;
      }

      item->data = old_item->data; // Zachovani dat
      old_item = old_item->next; // Dalsi zaznam v seznamu
    }
  }
  t->size = newsize;
  htab_clear(t2); // Vyprazdneni stare tabulky
  return t;
}
