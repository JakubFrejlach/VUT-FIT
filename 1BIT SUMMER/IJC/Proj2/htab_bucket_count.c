/*
 *  Soubor: htab_bucket_count.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

unsigned htab_bucket_count(htab_t *t)
{
  if(t == NULL) // Kontrola existence tabulky
    return 0;
  return t->arr_size;
}
