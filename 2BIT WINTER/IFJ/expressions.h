
/**
 * Project: IFJ18 compiler implementation.
 *
 * Expressions for syntax analysis implementation
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#ifndef _EXPRESSIONSH_
#define _EXPRESSIONSH_

#include<stdio.h>
#include<stdbool.h>
#include"scanner.h"
#include"symtable.h"

#ifndef GENERATE_H
  #include"generate.h"
#endif

#define SYNTAX_ERROR 2
#define SEMANTIC_ERROR 3
#define TYPE_ERROR 4
#define PARAMS_ERROR 5

typedef enum
{
  N = 0,  //    in table
  E = 1,  // =  in table
  L = 2,  // <  in table
  G = 3,   // >  in table //Last one

//Substract 10 to get place of these lexes in precedency table
  ADD = 10, //Must be first one
  MULT = 11,
  COMP = 12,
  EQUAL = 13,
  L_BRACKET = 14,
  R_BRACKET = 15,
  INTEGER = 16,
  DOLLAR = 17,  // $

  EXPRESSION = 18 //Must be last one
}precedency;

typedef struct analysisData
{
  symTab *funcTable;
  symTab *globalTable;
  symTab *localTable;
  symTab *overallTable;

  unsigned paramCount;
  bool defParams;
  unsigned scope;
  bool inDefinition;
  bool callBeforeDef;
  dString tmp;
}aData;

int Expression(tToken *t, tToken *preloaded, aData *d, int ender, bool isPreloaded);  //Bottom-up precedency analysis, which implememnts general algorythm (from lecture no. 8)

// Element of precedency analysis stack
typedef struct tElem {
    struct tElem *rptr; //previous element
    struct tElem *lptr; //next element
    precedency data; //precedency values
    int token; //lexType of token (used to go back from simplification of precedency table)
} *tElemPtr;

// Stack (double-linked list) of precedency analysis
typedef struct {
    tElemPtr Last;
    tElemPtr Top; //Top is topmost element which is not EXPRESSION
    tElemPtr First;
} tList;

bool RuleFound(tList *L, int *ruleID, int *rLenght);        //Tries to find any rule on top of the stack
bool FindInList(tList *L, precedency rule[], int length);   //Find the sequence of precedencies on the top of the stack
int ClearRule(tList *L, int length, tToken *t);             //Replaces (length) amount of precedencies from top of the stack with E (Expression is left side of every rule)
int LoadToken(tToken *t, int *input, int ender, aData *d, bool *oneCompareOp);  //Load next token and convert it to precedency
int TokenTypeToPrecedency(int type, int ender);   //Converts token to precedency symbol
int PlaceInPrecTable(precedency key);                       //Returns index in precedencyTable

int CodeGen(int operation, int detail, tToken *tokenValue); //Generation of code

void InitList (tList *L);                                   //Initialise list and make its first value to be DOLLAR
void DisposeList (tList *L);                                //Delete list and free the allocated memory
void PushList (tList *L, precedency element, int tokenData);  //Push new element to the top of the list
void PostList (tList *L, precedency element);               //Push new element after the "top" (topmost ,not Expression element) of the list
void TopList(tList *L);                                     //Move Top pointer to the topmost element of the list, which is not Expression

#endif
