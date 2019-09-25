/**
 * Project: IFJ18 compiler implementation.
 *
 * Scanner implementation.
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#ifndef _SCANNERH_
#define _SCANNERH_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"dstring.h"

// Macros for errors
#define INTERNAL_ERROR 99
#define LEX_CORRECT 0
#define LEX_ERROR 1

// All scanner states
typedef enum
{
  INIT,
  ID,
  INT,
  ZERO,
  AWAITING_DOUBLE,
  AWAITING_EXPONENT,
  EXPONENT_FIRST_DIGIT,
  DOUBLE,
  EXPONENT,
  AWAITING_COMMENT,
  AWAITING_COMMENT_END,
  COMMENT,
  COMMENT_END_LINE,
  LINE_COMMENT,
  STRING,
  STRING_ESCAPE,
  STRING_ESCAPE_HEX,
  STRING_ESCAPE_HEX_2,
  GREATER,
  LESS,
  ASSIGN,
  NOT_EQUAL
}scanState;

// All LEX types
typedef enum
{
  //xx -> keywords
  LEX_KEYWORD_DEF = 0,
  LEX_KEYWORD_DO = 1,
  LEX_KEYWORD_ELSE = 2,
  LEX_KEYWORD_END = 3,
  LEX_KEYWORD_IF = 4,
  LEX_KEYWORD_NOT = 5,
  LEX_KEYWORD_NIL = 6,
  LEX_KEYWORD_THEN = 7,
  LEX_KEYWORD_WHILE = 8,
  LEX_KEYWORD_BEGIN = 9, //Must be the last one!!!!!

  //1xx -> classic lex
  LEX_ID = 100,
  LEX_STRING = 101,
  LEX_INT = 102,
  LEX_DOUBLE = 103,
  LEX_FUNCTION_ID = 104,
  LEX_EOL = 105,
  LEX_EOF = 106,

  //2xx -> operators and brackets
  LEX_ASSIGN = 200,
  LEX_GREATER_EQUAL = 201,
  LEX_GREATER = 202,
  LEX_LESS_EQUAL = 203,
  LEX_LESS = 204,
  LEX_EQUAL = 205,
  LEX_NOT_EQUAL = 206,
  LEX_ADD = 207,
  LEX_SUB = 208,
  LEX_MUL = 209,
  LEX_DIV = 210,
  LEX_LEFT_BRACKET = 211,
  LEX_RIGHT_BRACKET = 212,
  LEX_COMA = 213,

  LEX_UNKNOWN = 666
}lexType;

//Token struct
typedef struct token
{
  lexType type;
  dString lexData;
}tToken;

int getToken(tToken *t);

bool copyToken(tToken *src, tToken *dest);

#endif
