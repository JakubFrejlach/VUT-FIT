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

#include<stdio.h>
#include<string.h>
#include"dstring.h"

/*
 * Initializes given dString struct
 *
 * s        pointer to dString struct
 * return   false, when memory alloc fails
 */
bool dStringInit(dString *s)
{
  if(!(s->data = malloc(sizeof(char) * DSTRING_INIT_SIZE)))
  {
    errorMsg("Failed to allocate memory for string.\n");
    return false;
  }
  s->stringSize = DSTRING_INIT_SIZE;
  s->stringLenght = 0;
  s->data[0] = '\0';
  return true;
}

/*
 * Resizes given dString to new size
 *
 * s        pointer to dString struct
 * newSize  requested new size
 * return   false, when memory alloc fails
 */
bool dStringResize(dString *s, int newSize)
{
  if(!(s->data = realloc(s->data, newSize)))
  {
    errorMsg("Failed to resize string.\n");
    return false;
  }
  s->stringSize = newSize;
  return true;
}

/*
 * Appends new char to dString struct
 * If its size is not enough, resize is executed
 *
 * s        pointer to dString struct
 * c        char that we want to append to dString
 * return   false, when memory alloc fails
 */
bool dStringAppend(dString *s, char c)
{
  s->data[s->stringLenght++] = c;
  if(s->stringLenght == s->stringSize)
  {
    if(!(dStringResize(s, s->stringSize + DSTRING_INIT_SIZE)))
    {
      errorMsg("Failed to append char to string.\n");
      return false;
    }
  }
  s->data[s->stringLenght] = '\0';
  return true;
}

/*
 * Copies data from one dString to another
 * If destinations size is not enough, resize is executed
 *
 * src      pointer to source dString
 * dest     pointer to destination dString
 * return   false, when memory alloc fails
 */
bool dStringCopy(dString *src, dString *dest)
{
  if(dest->stringSize <= src->stringLenght)
  {
    if(!(dest->data = realloc(dest->data, src->stringLenght + 1)))
    {
      errorMsg("Failed to copy string.\n");
      return false;
    }
    dest->stringSize = src->stringLenght + 1;
  }
  strcpy(dest->data, src->data);
  dest->stringLenght = src->stringLenght;
  return true;
}

/*
 * Clears data of dString
 *
 * s     pointer to dString
 */
void dStringClear(dString *s)
{
  memset(s->data, 0, s->stringSize);
  s->stringLenght = 0;
  s->data[0] = '\0';
}

/*
 * Frees memory allocated to dString
 *
 * s     pointer to dString
 */
void dStringFree(dString *s)
{
  free(s->data);
}
