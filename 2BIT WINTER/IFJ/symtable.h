/**
 * Project: IFJ18 compiler implementation.
 *
 * Symtable implementation.
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#ifndef _SYMTABLEH_
#define _SYMTABLEH_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"dstring.h"
#include"scanner.h"

//Data of item
typedef struct symTabData
{
  char *ID;
  unsigned params;
  bool defined;
  bool firstCalled;
}symTabData;

//Item of symtable
typedef struct symTabListItem
{
  char *key;
  symTabData sData;
  struct symTabListItem *next;
}symTabListItem;

//Symtable struct
typedef struct symTab
{
  unsigned size;
  struct symTabListItem **item;
}symTab;

unsigned symTabHashFunction(const char *str);

symTab *symTabInit();

symTabListItem *symTabAdd(symTab *t, const char *key);

symTabListItem *symTabFind(symTab *t, const char *key);

void symTabClear(symTab *t);

void symTabFree(symTab *t);

void symTabClearData(symTab *t);

#endif
