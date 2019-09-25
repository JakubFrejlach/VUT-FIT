/*
 *  Soubor: error.c
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include"error.h"

void warning_msg(const char *fmt, ...)
{
  va_list arguments;
  va_start(arguments, fmt);

  fprintf(stderr, "CHYBA: ");
  vfprintf(stderr, fmt, arguments);

  va_end(arguments);
}

void error_exit(const char *fmt, ...)
{
  va_list arguments;
  va_start(arguments, fmt);

  fprintf(stderr, "CHYBA: ");
  vfprintf(stderr, fmt, arguments);

  va_end(arguments);
  exit(1);
}
