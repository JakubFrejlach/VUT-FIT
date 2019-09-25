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

#include<stdbool.h>
#include"parser.h"

/*
 * Parser works like a giant switch which
 * calls recursive functions until it expects term.
 * Then if correct term is read it returns true, otherwise false is returned.
 * Everytime the term is succesfully read, new token is requested from scanner.
 */

/*
 * Terminals
 * Term->ID
 * Term->STRING
 * Term->INT
 * Term->FLOAT
 * Term->NIL
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return 0 if everything is correct or error code
 */
int Term(tToken *t, aData *d)
{
  switch (t->type)
  {
    symTabListItem *item;
    case LEX_ID: //Term->ID
      if(DEBUG)
      {
        printf("Term->ID\n");
      }
      //Indicates these are terms for function definition
      if(d->defParams)
      {
        //Params could not be function ID
        if(symTabFind(d->funcTable, t->lexData.data)){return SEMANTIC_ERROR;}

        //You cannot have 2 params with same ID
        else if(symTabFind(d->localTable, t->lexData.data) && !d->callBeforeDef){return SEMANTIC_ERROR;}

        //Adding params IDs to local table
        else if(!(item = symTabAdd(d->localTable, t->lexData.data))){return INTERNAL_ERROR;}

        //Param count increases
        d->paramCount++;
      }
      //These terms are in function call
      else
      {
        //We are in definition -> local table
        if(d->inDefinition)
        {
          //Params could not be function ID
          if(symTabFind(d->funcTable, t->lexData.data)){return SEMANTIC_ERROR;}

          //Function call with undefined variable as param
          if(!(item = symTabFind(d->localTable, t->lexData.data))){return SEMANTIC_ERROR;}

          //Param count increases
          d->paramCount++;
        }
        //We are in "main" -> global table
        else
        {
          //Same as "in definition" branch
          if(symTabFind(d->funcTable, t->lexData.data)){return SEMANTIC_ERROR;}
          if(!(item = symTabFind(d->globalTable, t->lexData.data))){return SEMANTIC_ERROR;}
          d->paramCount++;
        }
      }
      //Inserting parameter to stack for code generator
      stackInsertLast(&funcParams, STACK_ID, item->sData.ID);
      if(d->defParams)
      {
        item->sData.defined = true;
      }
      return getToken(t);
      break;

    case LEX_STRING: //Term->STRING
      if(DEBUG)
      {
        printf("Term->STRING\n");
      }
      //We can only have variables as a function params in definiton
      if(d->defParams && !(d->callBeforeDef)){return SYNTAX_ERROR;}
      d->paramCount++;
      stackInsertLast(&funcParams, STACK_STRING, t->lexData.data);
      return getToken(t);
      break;

    case LEX_INT: //Term->INT
      if(DEBUG)
      {
        printf("Term->INT\n");
      }
      //We can only have variables as a function params in definiton
      if(d->defParams && !(d->callBeforeDef)){return SYNTAX_ERROR;}
      d->paramCount++;
      stackInsertLast(&funcParams, STACK_INT, t->lexData.data);
      return getToken(t);
      break;

    case LEX_DOUBLE: //Term->FLOAT
      if(DEBUG)
      {
        printf("Term->FLOAT\n");
      }
      //We can only have variables as a function params in definiton
      if(d->defParams && !(d->callBeforeDef)){return SYNTAX_ERROR;}
      d->paramCount++;
      stackInsertLast(&funcParams, STACK_FLOAT, t->lexData.data);
      return getToken(t);
      break;

    case LEX_KEYWORD_NIL: //Term->NIL
      if(DEBUG)
      {
        printf("Term->NIL\n");
      }
      //We can only have variables as a function params in definiton
      if(d->defParams && !(d->callBeforeDef)){return SYNTAX_ERROR;}
      d->paramCount++;
      stackInsertLast(&funcParams, STACK_NIL, "");
      return getToken(t);
      break;

    default:
      if(DEBUG)
      {
        printf("ERROR: Term\n");
        printf("%d\n", t->type);
      }
      return SYNTAX_ERROR;
      break;
  }
  //unreachable
  return SYNTAX_ERROR;
}

/* Parameters until ender
 * ParametersUntilToken->ender
 * ParametersUntilToken->COMA Term ParametersUntilToken
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 * ender  type awaited in the end
 *
 * return 0 if everything is correct or error code
 */
int ParametersUntilToken(tToken *t, aData *d, lexType ender)
{
  int returnValue;
  switch (t->type)
  {
    case LEX_COMA:
      if(DEBUG)
      {
        printf("ParametersUntilToken->COMA Term ParametersUntilToken(ender)\n");
      }
      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

      //After coma there should be another term
      if((returnValue = Term(t, d)) == ANALYSIS_CORRECT)
      {
        return ParametersUntilToken(t, d, ender);
      }
      return returnValue;
      break;

    default:
      if(t->type == ender)
      {
        if(DEBUG)
        {
          printf("ParametersUntilToken->ender\n");
        }
        return getToken(t);
        break;
      }

      if(DEBUG)
      {
        printf("ERROR: ParametersUntilToken\n");
      }
      return SYNTAX_ERROR;
      break;
  }
  //unreachable
  return SYNTAX_ERROR;
}

/*
 * Zero or only one parameter
 * FirstParameter->ender
 * FirstParameter->Term FirstParameter
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 * ender  type awaited in the end
 *
 * return 0 if everything is correct or error code
 */
int FirstParameter(tToken *t, aData *d, lexType ender)
{
  int returnValue;

  //No parameters
  if(t->type == ender)
  {
    if(DEBUG)
    {
      printf("FirstParameter->ender\n");
    }
    return getToken(t);
  }
  //One or more parameters
  else
  {
    if((returnValue = Term(t, d)) == ANALYSIS_CORRECT)
    {
      if(DEBUG)
      {
        printf("FirstParameter->Term ParametersUntilToken(ender)\n");
      }
      return ParametersUntilToken(t, d, ender);
    }
    return returnValue;
  }
  //unreachable
  return SYNTAX_ERROR;
}

/* Call of function
 * FunctionCall->L_BRACKET ParametersUntilToken(R_BRACKET) EOL
 * FunctionCall->ParametersUntilToken(EOL)
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return 0 if everything is correct or error code
 */
int FunctionCall(tToken *t, aData *d)
{
  int returnValue;
  //Pointer to item with this function in function table
  symTabListItem *item = symTabFind(d->funcTable, d->tmp.data);
  switch (t->type)
  {
    //Function call with brackets
    case LEX_LEFT_BRACKET:
      if(DEBUG)
      {
        printf("FunctionCall->L_BRACKER ParametersUntilToken(R_BRACKET) EOL\n");
      }
      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

      if((returnValue = FirstParameter(t, d, LEX_RIGHT_BRACKET)) == ANALYSIS_CORRECT)
      {
        //Checking if function is called with correct amount of params
        if(!strcmp(item->key, "print"))
        {
          if(d->paramCount < 1){return PARAMS_ERROR;}
        }
        else if(item->sData.params != d->paramCount){return PARAMS_ERROR;}
        d->paramCount = 0;

        //Generating function call
        gen_CallFunc(item);

        //Function call must terminate with EOL sign
        if(t->type == LEX_EOL)
        {
          return getToken(t);
        }
        return SYNTAX_ERROR;
      }
      return returnValue;
      break;

    //Using function as variable leads to SEMANTIC error
    case LEX_ASSIGN:
      return SEMANTIC_ERROR;
      break;

    //Function call without brackets
    default:
      if(DEBUG)
      {
        printf("FunctionCall->ParametersUntilToken(EOL)\n");
      }
      if((returnValue = FirstParameter(t, d, LEX_EOL)) == ANALYSIS_CORRECT)
      {
        //Checking if function is called with correct amount of params
        if(!strcmp(item->key, "print"))
        {
          if(d->paramCount < 1){return PARAMS_ERROR;}
        }
        else if(item->sData.params != d->paramCount){return PARAMS_ERROR;}
        d->paramCount = 0;

        //Generating function call
        gen_CallFunc(item);

        return returnValue;
      }
      return returnValue;
      break;
  }
  //unreachable
  return SYNTAX_ERROR;
}

/*
 * Assigning variable ( ID= was already loaded )
 * VariableAssign->ID FunctionCall
 * VariableAssign->Expression EOL
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return 0 if everything is correct or error code
 */
int VariableAssign(tToken *t, aData *d)
{
  int returnValue;
  symTabListItem *item;

  if(t->type == LEX_ID || t->type == LEX_FUNCTION_ID) //VariableAssign->ID FunctionCall
  {
    //If ID is funtion we can go to FunctionCall
    if((item = symTabFind(d->funcTable, t->lexData.data)))
    {
      if(DEBUG)
      {
        printf("VariableAssign->ID FunctionCall\n");
      }
      //Function wasn't defined yet but it is called from "main"
      if(item->sData.firstCalled && !d->inDefinition)
      {
        return SEMANTIC_ERROR;
      }

      if(!saveId(&(t)->lexData, &(d)->tmp)){return INTERNAL_ERROR;}
      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

      //Flag for generator
      GEN_FLAG_PRINT_ASSIGN = 1;

      return FunctionCall(t, d);
    }
    else if(t->type == LEX_FUNCTION_ID && !d->inDefinition)
    {
      return SEMANTIC_ERROR;
    }
    //Function wasn't defined yet but it is called from function definition
    else if(d->inDefinition && !(item = symTabFind(d->localTable, t->lexData.data)))
    {
      if(!(item = symTabAdd(d->funcTable, t->lexData.data)))
      {
        return INTERNAL_ERROR;
      }

      //Enable flags for this case
      item->sData.firstCalled = true;
      d->defParams = true;
      d->callBeforeDef = true;

      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

      //Function call with brackets
      if(t->type == LEX_LEFT_BRACKET)
      {
        if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
        if((returnValue = FirstParameter(t, d, LEX_RIGHT_BRACKET)) != LEX_CORRECT){return returnValue;}
        if(t->type != LEX_EOL){return SYNTAX_ERROR;}
        if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
      }
      //Function call without brackets
      else
      {
        returnValue = FirstParameter(t, d, LEX_EOL);
      }

      //Disable flags for this case and save parameters amount
      d->defParams = false;
      d->callBeforeDef = false;
      item->sData.params = d->paramCount;
      d->paramCount = 0;

      //Generate function call
      gen_CallFunc(item);

      return returnValue;
    }
  }

  if(DEBUG)
  {
    printf("VariableAssign->Expression EOL\n");
  }
  if(t->type == LEX_EOL){return SYNTAX_ERROR;} //EMPTY EXPRESSION

  if((returnValue = Expression(t, t, d, LEX_EOL, false)) == ANALYSIS_CORRECT)
  {
    if(t->type == LEX_EOL)
    {
      gen_Expression();
      return getToken(t);
    }
    return SYNTAX_ERROR;
  }
  return returnValue;
}

/*
 * Item->DEF ID L_BRACKET ParametersUntilToken(R_BRACKET) EOL ListUntilToken(END) EOL
 * Item->IF Expression(THEN) THEN EOL ListUntilToken(ELSE) EOL ListUntilToken(END) EOL
 * Item->WHILE Expression(DO) DO EOL ListUntilToken(END) EOL
 * Item->IdSwitch
 * Item->Expression(EOL) EOL
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return 0 if everything is correct or error code
 */
int Item(tToken *t, aData *d)
{
  symTabListItem *item;
  int returnValue;

  switch (t->type)
  {
    case LEX_KEYWORD_DEF: //Item->DEF ID L_BRACKET ParametersUntilToken(R_BRACKET) EOL ListUntilToken(END) EOL

      //We cannot define another function in function definition
      if(d->inDefinition || d->scope){return SYNTAX_ERROR;}
      if(DEBUG)
      {
        printf("DEF ID L_BRACKET ParametersUntilToken(R_BRACKET) EOL ListUntilToken(END) EOL\n");
      }
      //In function definition flag
      d->inDefinition = true;

      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

      if(t->type == LEX_ID || t->type == LEX_FUNCTION_ID)
      {
        //There has already been variable with same ID as function we are about to define
        if((item = symTabFind(d->globalTable, t->lexData.data))){return SEMANTIC_ERROR;}

        //We cannot define two functions with same ID
        else if((item = symTabFind(d->funcTable, t->lexData.data)) && !item->sData.firstCalled){return SEMANTIC_ERROR;}

        //Adding funtion in function table
        else if(!(item = symTabAdd(d->funcTable, t->lexData.data))){return INTERNAL_ERROR;}

        if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
        if(t->type == LEX_LEFT_BRACKET)
        {
          if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

          //Indicates that terms will be in definiton
          d->defParams = true;

          if((returnValue = FirstParameter(t, d, LEX_RIGHT_BRACKET)) == ANALYSIS_CORRECT)
          {
            //Definition of funtion that has already been called
            if(item->sData.firstCalled)
            {
              if(d->paramCount != item->sData.params)
              {
                return PARAMS_ERROR;
              }
              item->sData.firstCalled = false;
            }

            d->defParams = false; //Indicates that terms won't be in definiton
            item->sData.params = d->paramCount; //Adding params count in function table
            d->paramCount = 0;

            if(t->type == LEX_EOL)
            {
              gen_DefFunc(item); //Function definiton generate
              if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

              if((returnValue = ListUntilToken(t, d, LEX_KEYWORD_END)) == ANALYSIS_CORRECT)
              {
                if(t->type == LEX_EOL)
                {
                  d->inDefinition = false; //We are no longer in funtion definition
                  symTabClear(d->localTable); //We can now clear local table
                  gen_EndFunc(); //Generate end of function definition
                  return getToken(t);
                }
                return SYNTAX_ERROR;
              }
              return returnValue;
            }
            return SYNTAX_ERROR;
          }
          return returnValue;
        }
      }
      return SYNTAX_ERROR;
      break;

    case LEX_KEYWORD_IF: //Item->IF Expression(THEN) THEN EOL ListUntilToken(ELSE) EOL ListUntilToken(END) EOL
      if(DEBUG)
      {
        printf("Item->IF Expression(THEN) THEN EOL ListUntilToken(ELSE) EOL ListUntilToken(END) EOL\n");
      }

      //Incrementing scope
      d->scope++;

      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
      if(t->type == LEX_KEYWORD_THEN){return SYNTAX_ERROR;} //EMPTY Expression

      if((returnValue = Expression(t, t, d, LEX_KEYWORD_THEN, false)) == ANALYSIS_CORRECT)
      {
        if(t->type == LEX_KEYWORD_THEN)
        {
          // TODOGEN add condition
          GEN_FLAG_BOOL = 1;
          gen_Expression();
          gen_If();
          if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
          if(t->type == LEX_EOL)
          {
            if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

            //If branch
            if((returnValue = ListUntilToken(t, d, LEX_KEYWORD_ELSE)) == ANALYSIS_CORRECT)
            {
              if(t->type == LEX_EOL)
              {
                gen_Else();

                if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

                //Else branch
                if((returnValue = ListUntilToken(t, d, LEX_KEYWORD_END)) == ANALYSIS_CORRECT)
                {
                  if(t->type == LEX_EOL)
                  {
                    //Decrementing scope
                    d->scope--;

                    //Generate end of if statement
                    gen_EndIf();
                    return getToken(t);
                  }
                  return SYNTAX_ERROR;
                }
                return returnValue;
              }
              return SYNTAX_ERROR;
            }
            return returnValue;
          }
        }
        return SYNTAX_ERROR;
      }
      return returnValue;
      break;

    case LEX_KEYWORD_WHILE: //Item->WHILE Expression(DO) DO EOL ListUntilToken(END) EOL
      if(DEBUG)
      {
        printf("Item->WHILE Expression(DO) DO EOL ListUntilToken(END) EOL\n");
      }
      //Incrementing scope
      d->scope++;

      //Generate while statement
      gen_While();

      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
      if(t->type == LEX_KEYWORD_DO){return SYNTAX_ERROR;} //EMPTY Expression

      if((returnValue = Expression(t, t, d, LEX_KEYWORD_DO, false)) == ANALYSIS_CORRECT)
      {
        GEN_FLAG_BOOL = 1;
        gen_Expression();
        gen_WhileCond();
        // TODOGEN add condition
        if(t->type == LEX_KEYWORD_DO)
        {
          if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
          if(t->type == LEX_EOL)
          {
            if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

            //While branch
            if((returnValue = ListUntilToken(t, d, LEX_KEYWORD_END)) == ANALYSIS_CORRECT)
            {
              if(t->type == LEX_EOL)
              {
                //Decrementing scope
                d->scope--;

                //Generete end of while statement
                gen_EndWhile();
                return getToken(t);
              }
              return SYNTAX_ERROR;
            }
          }
        }
      }
      return returnValue;
      break;

    case LEX_ID:
      if(DEBUG)
      {
        printf("Item->IdSwitch\n");
      }
      return IdSwitch(t, d);

    case LEX_FUNCTION_ID:
      if(DEBUG)
      {
        printf("Item->IdSwitch\n");
      }
      return IdSwitch(t, d);

    default: //Item->Expression(EOL) EOL
      if(DEBUG)
      {
        printf("Item->Expression(EOL) EOL\n");
      }
      //This expression cannot be empty because EOL gets filtered in ListUntilToken(EOL)
      returnValue = Expression(t, t, d, LEX_EOL, false);
      gen_Expression();

      //Generate return value
      if (IN_FUNC)
      {
        printLine(output(), "MOVE LF@%retval TF@%retval");
      }
      return returnValue;
      break;
  }
  //unreachable HELL
  return SYNTAX_ERROR;
}

/*
 * Switch for ID token in item
 * IdSwitch->ID(fun) FunctionCall
 * IdSwitch->ID(var) ASSIGN VariableAssign
 * IdSwitch->Expression(EOL) EOL
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return 0 if everything is correct or error code
 */
int IdSwitch(tToken *t, aData *d)
{
  int returnValue;
  symTabListItem *item;

  if((item = symTabFind(d->funcTable, t->lexData.data)))
  {
    //Calling undefined function in "main"
    if(item->sData.firstCalled && !d->inDefinition)
    {
      return SEMANTIC_ERROR;
    }

    if(!saveId(&(t)->lexData, &(d)->tmp)){return INTERNAL_ERROR;}
    if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

    //Flag for function call generate
    GEN_FLAG_EMPTY_CALL = 1;
    return FunctionCall(t, d);
  }
  //Function is not defined and we are not in function definition
  else if(t->type == LEX_FUNCTION_ID && !(d->inDefinition))
  {
    return SEMANTIC_ERROR;
  }
  //ID is variable or new
  else
  {
    tToken temp;

    //Saving token for proloaded expression
    dStringInit(&(temp.lexData));
    if(copyToken(t, &temp))
    {
      return INTERNAL_ERROR;
    }

    //Saving token data in parser struct
    if(!saveId(&(t)->lexData, &(d)->tmp)){return INTERNAL_ERROR;}
    if((returnValue = getToken(t)) != LEX_CORRECT){dStringFree(&(temp.lexData));return returnValue;}

    if(t->type == LEX_ASSIGN)
    {
      //Using function ID as variable
      if(temp.type == LEX_FUNCTION_ID)
      {
        dStringFree(&(temp.lexData));
        return SYNTAX_ERROR;
      }

      dStringFree(&(temp.lexData));
      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}

      //Adding ID in symtable
      if(d->inDefinition)
      {
        if(!(item = symTabAdd(d->localTable, d->tmp.data)))
        {
          return INTERNAL_ERROR;
        }
      }
      else
      {
        if(!(item = symTabAdd(d->globalTable, d->tmp.data)))
        {
          return INTERNAL_ERROR;
        }
      }

      returnValue = VariableAssign(t, d);

      //Generate variable assing
      //printf("%s is %d\n", item->key, item->sData.defined);
      gen_Assign(item);
      //printf("%s is %d\n", item->key, item->sData.defined);
      return returnValue;
    }
    //Function call in definition of non defined function
    else
    {
      if(d->inDefinition && !(item = symTabFind(d->localTable, d->tmp.data)))
      {
        if(!(item = symTabAdd(d->funcTable, d->tmp.data)))
        {
          return INTERNAL_ERROR;
        }
        dStringFree(&(temp.lexData));

        //Enable flags for this case
        item->sData.firstCalled = true;
        d->defParams = true;
        d->callBeforeDef = true;

        //Function call with brackets
        if(t->type == LEX_LEFT_BRACKET)
        {
          if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
          returnValue = FirstParameter(t, d, LEX_RIGHT_BRACKET);
          if(t->type != LEX_EOL){return SYNTAX_ERROR;}
          if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
        }
        //Function call without brackets
        else
        {
          returnValue = FirstParameter(t, d, LEX_EOL);
        }
        //Disable flags for this case and save parameters amount
        d->defParams = false;
        d->callBeforeDef = false;
        item->sData.params = d->paramCount;
        d->paramCount = 0;

        //Generate function call
        GEN_FLAG_EMPTY_CALL = 1;
        gen_CallFunc(item);
        return returnValue;
      }
      if(temp.type == LEX_FUNCTION_ID)
      {
        return SEMANTIC_ERROR;
        dStringFree(&(temp.lexData));
      }
      //Preloaded expression
      if((returnValue = Expression(t, &temp, d, LEX_EOL, true)) != ANALYSIS_CORRECT)
      {
        gen_Expression();
        printLine(output(), "## empty expression ");
        if (IN_FUNC)
        {
          printLine(output(), "MOVE LF@%retval TF@%retval");
        }
        dStringFree(&(temp.lexData));
        return returnValue;
      }
      dStringFree(&(temp.lexData));

      if(t->type == LEX_EOL)
      {
        return getToken(t);
      }
      return SYNTAX_ERROR;
    }

    dStringFree(&(temp.lexData));
    return SYNTAX_ERROR;
  }

  //unreachable
  return SYNTAX_ERROR;
}

/*
 * ListUntilToken->ender
 * ListUntilToken->EOL ListUntilToken
 * ListUntilToken->Item ListUntilToken
 *
 * t      tToken with lexical data
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return 0 if everything is correct or error code
 */
int ListUntilToken(tToken *t, aData *d, lexType ender) //List of items
{
  int returnValue;
  switch (t->type)
  {
    //Newline
    case LEX_EOL: //ListUntilToken->EOL ListUntilToken
      if(DEBUG)
      {
        printf("ListUntilToken->EOL ListUntilToken\n");
      }
      if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
      return ListUntilToken(t, d, ender);
      break;

    //Ender (EOL, bracket, EOF, etc.)
    default:
      if(t->type == ender) //ListUntilToken->ender
      {
        if(DEBUG)
        {
          printf("ListUntilToken->ender\n");
        }
        if(ender == LEX_EOF)
        {
          if(DEBUG)
          {
            printf("--------EOF-------\n");
          }
          return ANALYSIS_CORRECT;
        }
        else
        {
          return getToken(t);
        }
      }

      if(DEBUG)
      {
        printf("ListUntilToken->Item ListUntilToken\n");
      }
      // ListUntilToken->Item ListUntilToken
      if((returnValue = Item(t, d)) == ANALYSIS_CORRECT)
      {
        return ListUntilToken(t, d, ender);
      }
      return returnValue;
      break;
  }
  //unreachable
  return SYNTAX_ERROR;
}
/*
 * Initialize parser struct and executes syntax and semantic analysis
 *
 * return 0 if analysis was succesfully executed or error code
 */
int analysis()
{
  //Token with lexical data
  tToken token;
  dStringInit(&(token.lexData));

  //Initialize generator
  generateInit();

  //Get first token
  int returnValue;
  if((returnValue = getToken(&token)) != LEX_CORRECT){return returnValue;}

  //Parser data initilization
  aData tables;
  if(!parserInit(&tables))
  {
    errorMsg("Parser failed to init.\n");
    return INTERNAL_ERROR;
  }

  //Analysis
  returnValue = ListUntilToken(&token, &tables, LEX_EOF);

  //Checking if all called functions were defined
  symTabListItem *item;
  if(returnValue == ANALYSIS_CORRECT)
  {
    for(unsigned i = 0; i < SYM_TAB_SIZE; i++)
    {
      item = tables.funcTable->item[i];
      while(item)
      {
        if(item->sData.firstCalled)
        {
          returnValue = SEMANTIC_ERROR;
          break;
        }
        item = item->next;
      }
      if(returnValue == SEMANTIC_ERROR)
      {
        break;
      }
    }
  }

  //Free memory
  dStringFree(&(token.lexData));
  dStringFree(&(tables.tmp));

  //Dispose symtables
  parserDispose(&tables);

  //If analysis was succesfull, flush code to stdout
  if (returnValue == 0)
  {
    generatePrint();
  }
  generateClean();
  return returnValue;
}

/*
 * d      struct with parser data carrying symtables, flags, etc.
 *
 * return true if everything is correct or false if something failed
 */
bool parserInit(aData *d)
{
  //Temporary dString initilization
  if(!dStringInit(&(d)->tmp))
  {
    return false;
  }

  //Symtables initilization
  if(!(d->globalTable = symTabInit()))
  {
    return false;
  }
  if(!(d->localTable = symTabInit()))
  {
    symTabFree(d->globalTable);
    return false;
  }
  if(!(d->funcTable = symTabInit()))
  {
    symTabFree(d->localTable);
    symTabFree(d->globalTable);
    return false;
  }


  //Adding builtin functions into function table
  symTabListItem *item;
  if(!(item = symTabAdd(d->funcTable, "inputs")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 0;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "inputi")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 0;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "inputf")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 0;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "print")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 0;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "length")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 1;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "substr")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 3;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "ord")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 2;
  item->sData.firstCalled = false;
  if(!(item = symTabAdd(d->funcTable, "chr")))
  {
    parserDispose(d);
    return false;
  }
  item->sData.params = 1;
  item->sData.firstCalled = false;

  //Parser flags initilization
  d->inDefinition = false;
  d->defParams = false;
  d->callBeforeDef = false;
  d->scope = 0;
  d->paramCount = 0;
  return true;
}

/*
 * Disposes all symtables
 *
 * d      struct with parser data carrying symtables, flags, etc.
 */
void parserDispose(aData *d)
{
  symTabFree(d->localTable);
  symTabFree(d->globalTable);
  symTabFree(d->funcTable);
}

/*
 * Disposes all symtables
 *
 * src    source dString
 *
 * dest   destination dString
 * return true if saving was succesfull
 */
bool saveId(dString *src, dString *dest)
{
  if(!dStringCopy(src, dest))
  {
    return false;
  }
  return true;
}
