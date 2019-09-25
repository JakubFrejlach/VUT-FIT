/*
 *  Soubor: htab_remove.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

bool htab_remove(htab_t *t, const char *key)
{
  if(t == NULL || key == NULL) // Kontrola existence tabulky a hledaneho klice
    return false;

  unsigned index = htab_hash_function(key) % htab_bucket_count(t);
  htab_listitem *item = t->item[index];
  htab_listitem *prev_item = NULL;

  while(item != NULL) // Hledani zadane polozky
  {
    if(!strcmp(key, item->key)) // Polozka nalezena
    {
      if(item->next == NULL) // Polozka se nachazi na konci seznamu
      {
        free(item->key);
        free(item);

        if(prev_item == NULL) // Polozka je v seznamu jedina
          t->item[index] = NULL;

        t->size = t->size - 1; // Uprava zaznamu o poctu polozek
        return true;
      }
      else if(prev_item == NULL) // Polozka se nachazi na zacatku seznamu
      {
        t->item[index] = t->item[index]->next;
        free(item->key);
        free(item);
        t->size = t->size - 1; // Uprava zaznamu o poctu polozek
        return true;
      }
      else // Polozka se nachazi nekde uprostred seznamu
      {
        prev_item->next = item->next; // Provazani predchozi polozky s nasledujici polozkou
        free(item->key);
        free(item);
        t->size = t->size - 1; // Uprava zaznamu o poctu polozek
        puts("kokote");
        return true;
      }
    }

    prev_item = item; // Uchovani ukazatele na predchozi polozku
    item = item->next; // Posun na dalsi polozku
  }
  return false; // Pokud se kod dostane sem, polozka nebyla nalezena
}
