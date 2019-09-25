/*
 *  Soubor: htab_find.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

htab_listitem* htab_find(htab_t *t, const char *key)
{
  if(t == NULL || key == NULL) // Kontrola existence tabulky a hledaneho klice
    return NULL;

  unsigned index = htab_hash_function(key) % htab_bucket_count(t);
  htab_listitem *item = t->item[index];

  while(item != NULL) // Prohledavani seznamu
  {
    if(!strcmp(item->key, key)) // Nalezen zaznam
    {
      item->data = item->data + 1;
      return item;
    }
    item = item->next;
  }
  return NULL; // Pokud nebyl nalezen zaznam vraci NULL
}
