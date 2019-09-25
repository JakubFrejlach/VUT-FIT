/*
 *  Soubor: htab-private.h
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab.h"

struct htab_t
{
  unsigned size;
  unsigned arr_size;
  struct htab_listitem **item;
};
