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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include"scanner.h"

//Array for all key words
const char* keyWords[] =
{
  [LEX_KEYWORD_DEF] = "def",
  [LEX_KEYWORD_DO] = "do",
  [LEX_KEYWORD_ELSE] = "else",
  [LEX_KEYWORD_END] = "end",
  [LEX_KEYWORD_IF] = "if",
  [LEX_KEYWORD_NOT] = "not",
  [LEX_KEYWORD_NIL] = "nil",
  [LEX_KEYWORD_THEN] = "then",
  [LEX_KEYWORD_WHILE] = "while",
  [LEX_KEYWORD_BEGIN] = "begin"
};

/*
 * Load next lexeme, analyze it and return it as a token struct via param.
 *
 * t        through this struct function returns data of token
 * return   returns success value or error value (LEX or INTERNAL)
 */
bool copyToken(tToken *src, tToken *dest)
{
  dest->type = src->type;
  if(!dStringCopy(&(src)->lexData, &(dest)->lexData))
  {
    return true;
  }
  return false;
}

int getToken(tToken *t)
{
  static bool wasEOL = true; //If last token was EOL or if this is first token -> true
  FILE *f = stdin;
  int c;
  scanState state = wasEOL ? AWAITING_COMMENT : INIT; //If wasEOL is true, there could be block comment.
  dString buffer;
  char hex[2] = {0,}; //Array for hex escape in STRING_ESCAPE_HEX
  char* endPtr; //End pointer for strtod/strtol

  //Initializate buffer for token data.
  if(!dStringInit(&buffer))
  {
    return INTERNAL_ERROR;
  }

  //Read input char by char and analyze lex type.
  while(1)
  {
    c = fgetc(f);
    switch (state)
    {
      /************************ AWAITING_COMMENT STATE ************************/
      case AWAITING_COMMENT:
        wasEOL = false;
        if(c == '=')
        {
          c = fgetc(f);
          if(c == 'b')
          {
            c = fgetc(f);
            if(c == 'e')
            {
              c = fgetc(f);
              if(c == 'g')
              {
                c = fgetc(f);
                if(c == 'i')
                {
                  c = fgetc(f);
                  if(c == 'n')
                  {
                    c = fgetc(f);
                    if(isspace(c) && c != '\n')
                    {
                      state = COMMENT;
                      continue;
                    }
                    else if(c == '\n')
                    {
                      state = COMMENT;
                      wasEOL = true;
                      continue;
                    }
                  }
                }
              }
            }
          }
        }
        else
        {
          state = INIT;
          ungetc(c, f);
          continue;
        }
        t->type = LEX_UNKNOWN;
        dStringFree(&buffer);
        return LEX_ERROR;


      /************************ INIT STATE ************************/
      case INIT:
        //Go through white spaces.
        if(isspace(c) && c != '\n')
        {
          continue;
        }
        //End of line.
        else if(c == '\n')
        {
          t->type = LEX_EOL;
          dStringFree(&buffer);
          wasEOL = true;
          return LEX_CORRECT;
        }
        //End of file.
        else if(c == EOF)
        {
          t->type = LEX_EOF;
          dStringFree(&buffer);
          wasEOL = true;
          return LEX_CORRECT;
        }
        //Identificator lexeme.
        else if(islower(c) || c == '_')
        {
          //Save loaded char, if saving fails, free memory and return error value. This repeats many times so one comment is enough.
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }

          state = ID;
          continue;
        }
        //Unnecessary zeros in the number beginning.
        else if(c == '0')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = ZERO;
          continue;
        }
        //Number lexeme.
        else if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = INT;
          continue;
        }
        //Line comment
        else if(c == '#')
        {
          state = LINE_COMMENT;
          continue;
        }
        //All operators and brackets
        else if(c == '\"')
        {
          state = STRING;
          continue;
        }
        else if(c == '>')
        {
          state = GREATER;
          continue;
        }
        else if(c == '<')
        {
          state = LESS;
          continue;
        }
        else if(c == '=')
        {
          state = ASSIGN;
          continue;
        }
        else if(c == '+')
        {
          t->type = LEX_ADD;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == '-')
        {
          t->type = LEX_SUB;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == '*')
        {
          t->type = LEX_MUL;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == '/')
        {
          t->type = LEX_DIV;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == '(')
        {
          t->type = LEX_LEFT_BRACKET;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == ')')
        {
          t->type = LEX_RIGHT_BRACKET;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == ',')
        {
          t->type = LEX_COMA;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else if(c == '!')
        {
          state = NOT_EQUAL;
          continue;
        }
        //Unknown lexeme.
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }

      /************************ GREATER STATE ************************/
      case GREATER:
        if(c == '=')
        {
          t->type = LEX_GREATER_EQUAL;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_GREATER;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ LESS STATE ************************/
      case LESS:
        if(c == '=')
        {
          t->type = LEX_LESS_EQUAL;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_LESS;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ ASSIGN STATE ************************/
      case ASSIGN:
        if(c == '=')
        {
          t->type = LEX_EQUAL;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_ASSIGN;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ NOT_EQUAL STATE ************************/
      case NOT_EQUAL:
      {
        if(c == '=')
        {
          t->type = LEX_NOT_EQUAL;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }
      }

      /************************ IDENTIFICATOR STATE ************************/
      case ID:
        if(isalnum(c) || c == '_')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }

          continue;
        }
        //Function identificator.
        else if(c == '?' || c == '!')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          t->type = LEX_FUNCTION_ID;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          ungetc(c, f);

          //Check if loaded identificator is key word
          {
            for(int i = LEX_KEYWORD_DEF; i <= LEX_KEYWORD_BEGIN; i++)
            if(!strcmp(buffer.data,keyWords[i]))
            {
              t->type = i;
              dStringFree(&buffer);
              return LEX_CORRECT;
            }
          }

          //Not a key word -> identificator
          t->type = LEX_ID;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ ZERO STATE ************************/
      case ZERO:
        //Unnecessary zeros are handled as error.
        if(isdigit(c))
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }
        //Could be double
        else if(c == '.')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = AWAITING_DOUBLE;
          continue;
        }
        //Could be exponent
        else if(c == 'e' || c == 'E')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = AWAITING_EXPONENT;
          continue;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_INT;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ INT STATE ************************/
      case INT:
        if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          continue;
        }
        //Could be double
        else if(c == '.')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = AWAITING_DOUBLE;
          continue;
        }
        //Could be exponent
        else if(c == 'e' || c == 'E')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = AWAITING_EXPONENT;
          continue;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_INT;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ AWAITING DOUBLE STATE ************************/
      case AWAITING_DOUBLE:
        if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = DOUBLE;
          continue;
        }
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }

      /************************ AWAITING EXPONENT STATE ************************/
      case AWAITING_EXPONENT:
        if(c == '-' || c == '+')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = EXPONENT_FIRST_DIGIT;
          continue;
        }
        else if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = EXPONENT;
          continue;
        }
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }

      /************************ DOUBLE STATE ************************/
      case DOUBLE:
        if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          continue;
        }
        //Could be double with exponent
        else if(c == 'e' || c == 'E')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = AWAITING_EXPONENT;
          continue;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_DOUBLE;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
      /************************ EXPONENT FIRST DIGIT STATE ************************/
      case EXPONENT_FIRST_DIGIT:
        if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = EXPONENT;
          continue;
        }
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }

      /************************ EXPONENT STATE ************************/
      case EXPONENT:
        if(isdigit(c))
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          continue;
        }
        else
        {
          ungetc(c, f);
          t->type = LEX_DOUBLE;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }

      /************************ STRING STATE ************************/
      case STRING:
        //These char can be in string without restriction
        if(c > 31 && c != '"' && c != '\\')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          continue;
        }
        //Could be espace sequence
        else if(c == '\\')
        {
          state = STRING_ESCAPE;
          continue;
        }
        //End of string
        else if(c == '"')
        {
          t->type = LEX_STRING;
          if(!dStringCopy(&buffer, &(t->lexData)))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        //String with no end
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }

      /************************ STRING_ESCAPE STATE ************************/
      case STRING_ESCAPE:
        if(c == '"' || c == '\\')
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = STRING;
          continue;
        }
        else if(c == 'n')
        {
          if(!dStringAppend(&buffer, '\n'))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = STRING;
          continue;
        }
        else if(c == 't')
        {
          if(!dStringAppend(&buffer, '\t'))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = STRING;
          continue;
        }
        else if(c == 's')
        {
          if(!dStringAppend(&buffer, ' '))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = STRING;
          continue;
        }
        //Could be hex escape sequence
        else if(c == 'x')
        {
          state = STRING_ESCAPE_HEX;
          continue;
        }
        else
        {
          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          state = STRING;
          continue;
        }

      /************************ STRING_ESCAPE_HEX STATE ************************/
      case STRING_ESCAPE_HEX:
        //Could be 2-digit hex
        if(isdigit(c) || (toupper(c) >= 'A' && toupper(c) <= 'F'))
        {
          hex[0] = c;
          state = STRING_ESCAPE_HEX_2;
          continue;
        }
        else
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }

      /************************ STRING_ESCAPE_HEX_2 STATE ************************/
      case STRING_ESCAPE_HEX_2:
        if(isdigit(c) || (toupper(c) >= 'A' && toupper(c) <= 'F'))
        {
          hex[1] = c;
          //Convert 1-digit hex
          c = strtol(hex, &endPtr, 16);
          if(*endPtr)
          {
            errorMsg("Failed to convert string to hexa\n");
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }

          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          memset(hex, 0, 2);
          state = STRING;
          continue;
        }
        else
        {
          ungetc(c, f);
          //Convert 2 digit hex
          c = strtol(hex, &endPtr, 16);
          if(*endPtr)
          {
            errorMsg("Failed to convert string to hexa\n");
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }

          if(!dStringAppend(&buffer, c))
          {
            dStringFree(&buffer);
            return INTERNAL_ERROR;
          }
          memset(hex, 0, 2);
          state = STRING;
          continue;
        }


      /************************ COMMENT STATE ************************/
      case COMMENT:
        if(c == '\n')
        {
          wasEOL = true;
          continue;
        }
        else if(c == '=' && wasEOL)
        {
          wasEOL = false;
          state = AWAITING_COMMENT_END;
          continue;
        }
        else if(c == EOF)
        {
          t->type = LEX_UNKNOWN;
          dStringFree(&buffer);
          return LEX_ERROR;
        }
        else
        {
          wasEOL = false;
          continue;
        }

      /************************ AWAITING_COMMENT_END STATE ************************/
      case AWAITING_COMMENT_END:
        if(c == 'e')
        {
          c = fgetc(f);
          if(c == 'n')
          {
            c = fgetc(f);
            if(c == 'd')
            {
              c = fgetc(f);
              if(isspace(c) && c != '\n')
              {
                state = COMMENT_END_LINE;
                continue;
              }
              else if(c == '\n')
              {
                wasEOL = true;
                state = AWAITING_COMMENT;
                continue;
              }
            }
          }
        }
        state = COMMENT;
        continue;

      /************************ COMMENT_END_LINE STATE ************************/
      case COMMENT_END_LINE:
        if(c == '\n')
        {
          wasEOL = true;
          state = AWAITING_COMMENT;
          continue;
        }
        else if(c == EOF)
        {
          t->type = LEX_EOF;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          continue;
        }

      /************************ LINE_COMMENT STATE ************************/
      case LINE_COMMENT:
        if(c == '\n')
        {
          wasEOL = true;
          t->type = LEX_EOL;
          dStringFree(&buffer);
          return LEX_CORRECT;
        }
        else
        {
          continue;
        }
    }
  }
}
