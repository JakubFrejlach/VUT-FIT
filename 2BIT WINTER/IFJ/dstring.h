/**
 * Project: IFJ18 compiler implementation.
 *
 * Dynamic string implementation.
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#ifndef _DSTRINGH_
#define _DSTRINGH_

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include"error.h"

// Macro for reallocs
#define DSTRING_INIT_SIZE 8

// dString (dynamic string) struct
typedef struct string
{
  int stringLenght;
  int stringSize;
  char *data;
}dString;

bool dStringInit(dString *s);

bool dStringResize(dString *s, int newSize);

bool dStringAppend(dString *s, char c);

bool dStringCopy(dString *src, dString *dest);

void dStringFree(dString *s);

void dStringClear(dString *s);

#endif
