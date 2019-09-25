/*
 *  Soubor: htab_init.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

htab_t *htab_init(int size)
{
  if(size <= 0) // Kontrola platne velikosti tabulky
    return NULL;

  htab_t* table = malloc(sizeof(htab_t)); // Alokace misto pro tabulku
	if(table == NULL) // Kontrola alokace
		return NULL;

  table->item = calloc(size, sizeof(htab_listitem)); // Alokuje misto pro flexible array a inicializuje ho
  if(table->item == NULL) // Kontrola alokace
  {
    free(table);
    return NULL;
  }

  table->arr_size = size;
  table->size = 0;

	return table;
}
