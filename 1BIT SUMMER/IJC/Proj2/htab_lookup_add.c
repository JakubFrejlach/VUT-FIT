/*
 *  Soubor: htab_lookup_add.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

htab_listitem* htab_lookup_add(htab_t *t, const char *key)
{
  if(t == NULL || key == NULL) // Kontrola existence tabulky a hledaneho klice
    return NULL;

  unsigned index = htab_hash_function(key) % htab_bucket_count(t); // Vygenerovani indexu

  htab_listitem *item = t->item[index];
  htab_listitem *prev_item;

  if(item == NULL) // Na indexu jeste neni zadna polozka -> vytvorit novou
  {
    item = malloc(sizeof(htab_listitem)); // Alokace pameti pro polozku
    if(item == NULL) // Kontrola alokace pameti
      return NULL;

    item->key = malloc((strlen(key)+1) * sizeof(char)); // Alokace pameti pro key
    if(item->key == NULL) // Kontrola alokace pameti
    {
      free(item);
      return NULL;
    }

    memcpy(item->key, key, strlen(key)+1);
    item->next = NULL;
    item->data = 0;
    t->size = t->size+1;
    t->item[index] = item;
  }
  else // Na indexu jiz polozky jsou
  {
    while(item != NULL) // Hledani polozky
    {
      if(!strcmp(item->key, key)) // Polozka nalezena
      {
        return item;
      }
      prev_item = item; // Uchovani predchozi polozky
      item = item->next; // Dalsi polozka v seznamu
    }

    //Polozka v seznamu nenalezena -> pripojeni na konec seznamu
    item = malloc(sizeof(htab_listitem)); // Alokace pameti pro polozku
    if(item == NULL) // Kontrola alokace
      return NULL;

    item->key = malloc((strlen(key)+1) * sizeof(char)); // Alokace pameti pro key
    if(item->key == NULL) // Kontrola alokace
    {
      free(item);
      return NULL;
    }

    memcpy(item->key, key, strlen(key)+1);
    item->next = NULL;
    item->data = 0;
    t->size = t->size+1;
    prev_item->next = item;
  }

  return item;
}
