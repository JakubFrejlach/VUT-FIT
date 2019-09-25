/*
 *  Soubor: htab_hash_function.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"htab-private.h"

unsigned htab_hash_function(const char *str)
{
  unsigned int h=0;
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
    h = 65599*h + *p;
  return h;
}
