/*
 *  Soubor: htab_free.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

void htab_free(htab_t *t)
{
  if(t != NULL)
  {
    htab_clear(t);
    free(t->item);
    free(t);
  }
}
