#ifndef _SCANNERH_
#define _SCANNERH_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"dstring.h"

#define INTERNAL_ERROR 99
#define LEX_CORRECT 0
#define LEX_ERROR 1

typedef enum
{
  INIT,
  ID,
  INT,
  ZERO,
  AWAITING_DOUBLE,
  AWAITING_EXPONENT,
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
  /*LEX_KEYWORD_INPUTS = 10,
  LEX_KEYWORD_INPUTI = 11,
  LEX_KEYWORD_INPUTF = 12,
  LEX_KEYWORD_PRINT = 13,
  LEX_KEYWORD_LENGTH = 14,
  LEX_KEYWORD_SUBSTR = 15,
  LEX_KEYWORD_ORD = 16,
  LEX_KEYWORD_CHR = 17,*/

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

/*union lexData
{
  int i;
  double d;
  dString s;
};*/

typedef struct token
{
  lexType type;
  dString lexData;
}tToken;

bool saveInt(dString *s, tToken *t);

bool saveDouble(dString *s, tToken *t);

bool isKeyword(dString *s);

int getToken(tToken *t);

bool copyToken(tToken *src, tToken *dest);

#endif
