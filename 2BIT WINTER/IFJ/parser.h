/**
 * Project: IFJ18 compiler implementation.
 *
 * Parser implementation
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#ifndef _SYNTAXH_
#define _SYNTAXH_

#include<stdio.h>
#include<stdbool.h>
#include"scanner.h"
#include"expressions.h"
#include "generate.h"

//Marcos for return codes
#define SYNTAX_ERROR 2
#define SEMANTIC_ERROR 3
#define DEBUG 0
#define LEX_CORRECT 0
#define ANALYSIS_CORRECT 0

//Macro for symtable init size
#define SYM_TAB_SIZE 1543

int Term(tToken *t, aData *d);
int ParametersUntilToken(tToken *t, aData *, lexType ender);
int FirstParameter(tToken *t, aData *d, lexType ender);
int FunctionCall(tToken *t, aData *d);
int VariableAssign(tToken *t, aData *d);
int Item(tToken *t, aData *d);
int IdSwitch(tToken *t, aData *d);
int ListUntilToken(tToken *t, aData *d, lexType ender);
int analysis();
bool parserInit(aData *d);
bool saveId(dString *src, dString *dest);
void parserDispose();

#endif
