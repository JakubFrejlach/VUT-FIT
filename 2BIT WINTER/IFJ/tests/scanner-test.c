#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"scanner.h"

const char* getTokenType(lexType type)
{
  switch(type)
  {
    case LEX_KEYWORD_DEF: return "LEX_KEYWORD_DEF";
    case LEX_KEYWORD_DO: return "LEX_KEYWORD_DO";
    case LEX_KEYWORD_ELSE: return "LEX_KEYWORD_ELSE";
    case LEX_KEYWORD_END: return "LEX_KEYWORD_END";
    case LEX_KEYWORD_IF: return "LEX_KEYWORD_IF";
    case LEX_KEYWORD_NOT: return "LEX_KEYWORD_NOT";
    case LEX_KEYWORD_NIL: return "LEX_KEYWORD_NIL";
    case LEX_KEYWORD_THEN: return "LEX_KEYWORD_THEN";
    case LEX_KEYWORD_WHILE: return "LEX_KEYWORD_WHILE";
    case LEX_KEYWORD_BEGIN: return "LEX_KEYWORD_BEGIN";
    case LEX_ID: return "LEX_ID";
    case LEX_STRING: return "LEX_STRING";
    case LEX_INT: return "LEX_INT";
    case LEX_DOUBLE: return "LEX_DOUBLE";
    case LEX_FUNCTION_ID: return "LEX_FUNCTION_ID";
    case LEX_EOL: return "LEX_EOL";
    case LEX_EOF: return "LEX_EOF";
    case LEX_ASSIGN: return "LEX_ASSIGN";
    case LEX_GREATER_EQUAL: return "LEX_GREATER_EQUAL";
    case LEX_GREATER: return "LEX_GREATER";
    case LEX_LESS_EQUAL: return "LEX_LESS_EQUAL";
    case LEX_LESS: return "LEX_LESS";
    case LEX_EQUAL: return "LEX_EQUAL";
    case LEX_NOT_EQUAL: return "LEX_NOT_EQUAL";
    case LEX_ADD: return "LEX_ADD";
    case LEX_SUB: return "LEX_SUB";
    case LEX_MUL: return "LEX_MUL";
    case LEX_DIV: return "LEX_DIV";
    case LEX_LEFT_BRACKET: return "LEX_LEFT_BRACKET";
    case LEX_RIGHT_BRACKET: return "LEX_RIGHT_BRACKET";
    case LEX_COMA: return "LEX_COMA";
    case LEX_UNKNOWN: return "LEX_UNKNOWN";

  }
}

void red()
{
  printf("\033[0;31m");
}

void green()
{
    printf("\033[0;32m");
}

void normal()
{
  printf("\033[0m");
}

void checkToken(lexType type, tToken *t)
{
  getToken(t);
  printf("Token should be type ");
  printf("\033[0;32m\"%s\"\033[0m and it's type ", getTokenType(type));
  if(type == t->type)
  {
    printf("\033[0;32m\"%s\"\033[0m\n", getTokenType(t->type));
  }
  else
  {
    printf("\033[0;31m\"%s\"\033[0m\n", getTokenType(t->type));
  }
  //assert(type == t->type);
}

int main()
{
  tToken token;
  tToken *t = &token;
  dStringInit(&(t)->lexData);

  FILE *f = freopen("tests/scanner-tests/test1", "r", stdin);
  puts("-------------------------------");
  puts("--           test1           --");
  puts("-------------------------------");
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test2", "r", stdin);
  puts("-------------------------------");
  puts("--           test2           --");
  puts("-------------------------------");
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test3", "r", stdin);
  puts("-------------------------------");
  puts("--           test3           --");
  puts("-------------------------------");
  checkToken(LEX_KEYWORD_DEF, t);
  checkToken(LEX_KEYWORD_DO, t);
  checkToken(LEX_KEYWORD_ELSE, t);
  checkToken(LEX_KEYWORD_END, t);
  checkToken(LEX_KEYWORD_IF, t);
  checkToken(LEX_KEYWORD_NOT, t);
  checkToken(LEX_KEYWORD_NIL, t);
  checkToken(LEX_KEYWORD_THEN, t);
  checkToken(LEX_KEYWORD_WHILE, t);
  checkToken(LEX_KEYWORD_BEGIN, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test4", "r", stdin);
  puts("-------------------------------");
  puts("--           test4           --");
  puts("-------------------------------");
  checkToken(LEX_INT, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test5", "r", stdin);
  puts("-------------------------------");
  puts("--           test5           --");
  puts("-------------------------------");
  checkToken(LEX_STRING, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test6", "r", stdin);
  puts("-------------------------------");
  puts("--           test6           --");
  puts("-------------------------------");
  checkToken(LEX_NOT_EQUAL, t);
  checkToken(LEX_EQUAL, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_NOT_EQUAL, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_LEFT_BRACKET, t);
  checkToken(LEX_RIGHT_BRACKET, t);
  checkToken(LEX_LEFT_BRACKET, t);
  checkToken(LEX_RIGHT_BRACKET, t);
  checkToken(LEX_RIGHT_BRACKET, t);
  checkToken(LEX_LESS, t);
  checkToken(LEX_GREATER, t);
  checkToken(LEX_LESS, t);
  checkToken(LEX_GREATER, t);
  checkToken(LEX_LESS_EQUAL, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_GREATER_EQUAL, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_ADD, t);
  checkToken(LEX_MUL, t);
  checkToken(LEX_DIV, t);
  checkToken(LEX_SUB, t);
  checkToken(LEX_ADD, t);
  checkToken(LEX_MUL, t);
  checkToken(LEX_DIV, t);
  checkToken(LEX_SUB, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test7", "r", stdin);
  puts("-------------------------------");
  puts("--           test7           --");
  puts("-------------------------------");
  checkToken(LEX_EOL, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_KEYWORD_DEF, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_LEFT_BRACKET, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_COMA, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_RIGHT_BRACKET, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_KEYWORD_IF, t);
  checkToken(LEX_LEFT_BRACKET, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_RIGHT_BRACKET, t);
  checkToken(LEX_KEYWORD_THEN, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_KEYWORD_ELSE, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_KEYWORD_END, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_KEYWORD_END, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test8", "r", stdin);
  puts("-------------------------------");
  puts("--           test8           --");
  puts("-------------------------------");
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_UNKNOWN, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test9", "r", stdin);
  puts("-------------------------------");
  puts("--           test9           --");
  puts("-------------------------------");
  checkToken(LEX_INT, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_STRING, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_DOUBLE, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test10", "r", stdin);
  puts("-------------------------------");
  puts("--           test10          --");
  puts("-------------------------------");
  checkToken(LEX_EOL, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);

  f = freopen("tests/scanner-tests/test11", "r", stdin);
  puts("-------------------------------");
  puts("--           test11          --");
  puts("-------------------------------");
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_INT, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_ASSIGN, t);
  checkToken(LEX_FUNCTION_ID, t);
  checkToken(LEX_ID, t);
  checkToken(LEX_EOL, t);
  checkToken(LEX_EOF, t);


  dStringFree(&(t)->lexData);
}
