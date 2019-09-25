/*
 *  Soubor: htab_clear.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

void htab_clear(htab_t *t)
{
  if(t == NULL) // Kontrola existence tabulky
    return;

  if(!htab_bucket_count(t)) // Kontrola prazdnosti tabulky
    return;

  htab_listitem *item;
  unsigned size = htab_bucket_count(t);

  for(unsigned i = 0; i < size; i++)
  {
    item = t->item[i];
    while(item != NULL) // Rusi polozky, dokud neni seznam na indexu "i" prazdny
    {
      htab_remove(t, item->key);
      item = t->item[i];
    }
  }
}
