/**
 * Project: IFJ18 compiler implementation.
 *
 * Error message printing.
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#include<stdio.h>
#include"error.h"


/**
 *
 * Prints given string as error message to stderr
 *
 * fmt formated string
 */
void errorMsg(const char *fmt, ...)
{
  va_list arguments;
  va_start(arguments, fmt);

  fprintf(stderr, "ERROR: ");
  vfprintf(stderr, fmt, arguments);

  va_end(arguments);
}
