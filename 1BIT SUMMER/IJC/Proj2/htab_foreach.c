/*
 *  Soubor: htab_foreach.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

void htab_foreach(htab_t *t, void(*fnc)(const char *key, unsigned data))
{
  if(t == NULL) // Kontrola existence tabulky
  {
    fprintf(stderr, "ERROR: Table is NULL.\n");
    return;
  }
  else if(fnc == NULL) // Kontrola existence funkce
  {
    fprintf(stderr, "ERROR: Function doesn't exists.\n");
    return;
  }

  htab_listitem *item;
  unsigned size = htab_bucket_count(t);

  for(unsigned i = 0; i < size; i++) // Volani funkce pro kazdy prvek tabulky
  {
    item = t->item[i];
    while(item != NULL)
    {
      fnc(item->key, item->data);
      item = item->next;
    }
  }
}
