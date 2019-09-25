
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

#include"expressions.h"

#define tableLength 8
/*
Precedential table
Used for precedency analysis
Tokens are being simplified to reduce comlexity
*/
int precedentTable[8][8] = {
   {G, L, G, G, L, G, L, G} ,   // + -
   {G, G, G, G, L, G, L, G} ,   // * /
   {L, L, N, G, L, G, L, G} ,   // < > <= >=
   {L, L, L, N, L, G, L, G} ,   // == !=
   {L, L, L, L, L, E, L, N} ,   // (
   {G, G, G, G, N, G, N, G} ,   // )
   {G, G, G, G, N, G, N, G} ,   // i
   {L, L, L, L, L, N, L, N}     // $
};

/**************************** EXPRESSION START ****************************/

//Bottom-up precedency analysis, which implememnts general algorythm (from lecture no. 8)
int Expression(tToken *t, tToken *preloaded, aData *d, int ender, bool isPreloaded)
{
  /**************************** SEMANTIC ****************************/
  int returnValue;
  if(t->type == LEX_ID) //Semantic control of token
  {
    symTabListItem *item;
    if(d->inDefinition)
    {
      if(!(item = symTabFind(d->localTable, t->lexData.data)))
      {
        return SEMANTIC_ERROR;
      }
      //SEMANTIC-END
    }
    else
    {
      if(!(item = symTabFind(d->globalTable, t->lexData.data)))
      {
        return SEMANTIC_ERROR;
      }
    }
    if (!strcmp(d->tmp.data, item->sData.ID) && !item->sData.defined)
    {
        GEN_FLAG_NIL = 1;
    }
  }
  //If analysis is preloaded, check also the second token
  if(isPreloaded)
  {
    if(preloaded->type == LEX_ID)
    {
      if(d->inDefinition)
      {
        if(!(symTabFind(d->localTable, preloaded->lexData.data)))
        {
          return SEMANTIC_ERROR;
        }
        //SEMANTIC-END
      }
      else
      {
        if(!(symTabFind(d->globalTable, preloaded->lexData.data)))
        {
          return SEMANTIC_ERROR;
        }
      }
    }
  }


  /**************************** SEMANTIC-END ****************************/
  tList tempList; //temporary stack for precedency analysis
  InitList(&tempList);

  tToken lastValue; //token to save last loaded value
  dStringInit(&(lastValue.lexData));

  int a;
  int b = TokenTypeToPrecedency(preloaded->type, ender);

  bool oneCompareOp = false; //Did one comparison operator already occured? (< > <= >= == !=)
  bool firstLoop = isPreloaded; //If analysis is preloaded, first loop is different

  do{
    a = tempList.Top->data;
    int foundRuleID = 0;
    //printf("Top:%d\n", a);
    //printf("Input:%d\n", b);

    //Get indexes in precedentTable
    int indexA = PlaceInPrecTable(a);
    int indexB = PlaceInPrecTable(b);
    if(indexA < 0 || indexA >= tableLength || indexB < 0 || indexB >= tableLength)
    { //ERROR, token is not in the table range
      //printf("Token out of bounds.\n");
      DisposeList(&tempList);
      return SYNTAX_ERROR;
    }

    //Switch based on precedency relation of a and b
    switch (precedentTable[indexA][indexB])
    {
    case E: // =
      //printf("= \n");
      if(firstLoop)
      {
        firstLoop = false;
        PushList(&tempList, b, preloaded->type); //Push b to stack
        b = TokenTypeToPrecedency(t->type, ender); //b = next token
      }
      else
      {
        PushList(&tempList, b, t->type); //Push b to stack
        if((returnValue = LoadToken(t, &b, ender, d, &oneCompareOp)) != 0){dStringFree(&(lastValue.lexData));return returnValue;} //b=next token + error handling
      }

      break; //endcase E

    case L: // <
      //printf("< \n");
      PostList(&tempList, L); //Push "<" precedency sign to stack (after the Top pointer)
      if(firstLoop)
      {
        firstLoop = false;
        PushList(&tempList, b, preloaded->type); //Push b to stack
        b = TokenTypeToPrecedency(t->type, ender); //b=next token
      }
      else
      {
        PushList(&tempList, b, t->type); //Push b to stack
        if((returnValue = LoadToken(t, &b, ender, d, &oneCompareOp)) != 0){dStringFree(&(lastValue.lexData));return returnValue;} //b=next token + error handling
      }

      break; //endcase L

    case G: // >
      //printf("> \n");
      ; //empty statement to bypass "label can only be part of a statement and a declaration is not a statement" ERROR
      int ruleLenght = 0;
      if(RuleFound(&tempList, &foundRuleID, &ruleLenght) != 0) //Try to find rule on top of stack
      {
        //printf("RULE:%d\n", foundRuleID);

        if(firstLoop)
        {
          firstLoop = false;
          //Clear the found rule
          if((returnValue =  ClearRule(&tempList, ruleLenght, preloaded)) != 0){dStringFree(&(lastValue.lexData));return returnValue;}
        }
        else
        {
          //Clear the found rule
          if((returnValue =  ClearRule(&tempList, ruleLenght, t)) != 0){dStringFree(&(lastValue.lexData));return returnValue;}
        }

      }
      else
      {
        //printf("no rule err\n");
        DisposeList(&tempList);
        dStringFree(&(lastValue.lexData));
        return SYNTAX_ERROR;
      }
      break; //endcase G

    case N: // Error: top of stack and input dont have any precedency
      DisposeList(&tempList);
      dStringFree(&(lastValue.lexData));
      return SYNTAX_ERROR;
      break;

    default: // Error: this token should not be in Expression
      DisposeList(&tempList);
      dStringFree(&(lastValue.lexData));
      return SYNTAX_ERROR;
      break;
    }

    TopList(&tempList); //Actualize stack top pointer

  } while( !(tempList.Top->data == DOLLAR && b == DOLLAR)); //Repeat until expression has not been analysed
  DisposeList(&tempList);

  //printf("\n---------------------EXPRESSION END---------------------\n");
  dStringFree(&(lastValue.lexData));
  return 0; //ANALYSIS_CORRECT
}
/****************************  EXPRESSION END  ****************************/








/*
0: no rule
1: E->E+E
2: E->E*E
3: E->(E)
4: E->i
5: E->E<E
6: E->E==E
7: E->() ... not imlemented in the end
*/
//Tries to find any rule on top of the stack
bool RuleFound(tList *L, int *ruleID, int *rLenght)
{
  //Rules declaration:
  precedency r1_3[3] = {EXPRESSION, ADD, EXPRESSION};
  precedency r2_3[3] = {EXPRESSION, MULT, EXPRESSION};
  precedency r3_3[3] = {L_BRACKET, EXPRESSION, R_BRACKET};
  precedency r4_1[1] = {INTEGER};
  precedency r5_3[3] = {EXPRESSION, COMP, EXPRESSION};
  precedency r6_3[3] = {EXPRESSION, EQUAL, EXPRESSION};
  //precedency r7_2[2] = {L_BRACKET, R_BRACKET};

  //Rules finding
  //1: E->E+E
  if(FindInList(L, r1_3, 3))
  {
    *ruleID = 1;
    *rLenght = 3;
    return true;
  }
  //2: E->E*E
  if(FindInList(L, r2_3, 3))
  {
    *ruleID = 2;
    *rLenght = 3;
    return true;
  }
  //3: E->(E)
  if(FindInList(L, r3_3, 3))
  {
    *ruleID = 3;
    *rLenght = 3;
    return true;
  }
  //4: E->i
  if(FindInList(L, r4_1, 1))
  {
    *ruleID = 4;
    *rLenght = 1;
    return true;
  }
  //5: E->E<E
  if(FindInList(L, r5_3, 3))
  {
    *ruleID = 5;
    *rLenght = 3;
    return true;
  }
  //6: E->E==E
  if(FindInList(L, r6_3, 3))
  {
    *ruleID = 6;
    *rLenght = 3;
    return true;
  }

  *ruleID = 0;
  return false; //No rule was found
}

//Find the sequence of precedencies on the top of the stack
bool FindInList(tList *L, precedency rule[], int length)
{
  tElemPtr temp = L->Last;
  int i = length-1;

  while(temp != NULL)
  {
    if(temp->data == rule[i])
    {
      i--;
      if(i < 0)
      {
        if(temp->lptr != NULL && temp->lptr->data == 2) // 2 -> precedency sign "<" , which must be BEFORE the rule
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    }
    else
    {
      return false;
    }

    if(temp->lptr != NULL)
    {
      temp = temp->lptr;
    }
    else
    {
      temp = NULL;
    }
  }
  return false;
}

//Replaces (length) amount of precedencies from top of the stack with E (Expression is left side of every rule)
int ClearRule(tList *L, int length, tToken *t)
{
  int counter = length;
  while(counter > 0)
  {
    tElemPtr temp = L->Last;

    int returnValue;
    if((returnValue =  CodeGen(temp->data, temp->token, t)) != 0){return returnValue;}

    L->Last = L->Last->lptr;
    L->Last->rptr = NULL;

    free(temp);
    counter--;
  }

  //Change the last precedency symbol to the E (Expression is left side of rule)
  L->Last->rptr = NULL;
  L->Last->data = EXPRESSION;
  L->Last->token = 0;

  return 0;
}

//Load next token and convert it to precedency
int LoadToken(tToken *t, int *input, int ender, aData *d, bool *oneCompareOp)
{
  int returnValue;
  if((returnValue = getToken(t)) != LEX_CORRECT){return returnValue;}
  int conversion = TokenTypeToPrecedency(t->type, ender);

  //Two comparison tokens error
  if(conversion == COMP || conversion == EQUAL)
  {
    if(*oneCompareOp == false)
    {
      *oneCompareOp = true;
    }
    else
    {
      return TYPE_ERROR;
    }
  }

  /**************************** SEMANTIC ****************************/
  if(t->type == LEX_ID)
  {
    symTabListItem *item;
    if(d->inDefinition)
    {
      if(!(item = symTabFind(d->localTable, t->lexData.data)))
      {
        return SEMANTIC_ERROR;
      }
    }
    else
    {
      if(!(item = symTabFind(d->globalTable, t->lexData.data)))
      {
        return SEMANTIC_ERROR;
      }
    }
    if (!strcmp(d->tmp.data, item->sData.ID) && !item->sData.defined)
    {
      GEN_FLAG_NIL = 1;
    }
  }
  /**************************** SEMANTIC-END ****************************/
  *input = conversion; //Return the loaded precedency through a pointer

  return 0;
}

//Returns index in precedencyTable
int PlaceInPrecTable(precedency key)
{
  return (key-10);  //Precedency symbols are indexed with added values of ten (see precendency in expressions.h)
}

//Converts token to precedency symbol
int TokenTypeToPrecedency(int type, int ender)
{
  switch (type)
  {
    case LEX_ADD: // +
    case LEX_SUB: // -
    return ADD;
    break;

    case LEX_MUL: // *
    case LEX_DIV: // /
    return MULT;
    break;

    case LEX_GREATER_EQUAL: // >=
    case LEX_GREATER:       // >
    case LEX_LESS_EQUAL:    // <=
    case LEX_LESS:          // <
    return COMP;
    break;

    case LEX_EQUAL:     // ==
    case LEX_NOT_EQUAL: // !=
    return EQUAL;
    break;

    case LEX_LEFT_BRACKET:  // (
    return L_BRACKET;
    break;

    case LEX_RIGHT_BRACKET: // )
    return R_BRACKET;
    break;

    case LEX_INT:         // 42
    case LEX_DOUBLE:      // 4.2
    case LEX_STRING:      // "string"
    case LEX_ID:          // id
    case LEX_KEYWORD_NIL: // nil
    return INTEGER;
    break;

    default:
      if(type == ender) //Token is ender of this expression
      {
        return DOLLAR;
      }
      else //token has not been recognised
      {
        //printf("Error, not recognised case of token type %d\n", type);
        return EXPRESSION+1;
      }
    break;
  }
  //unreachable HELL leads to error
  return 1;
}



//Generation of code
//int detail is needed to go back from simplified precedencyTable
///tToken *tokenValue is needed for IDs
int CodeGen(int operation, int detail, tToken *tokenValue)
{
  switch (operation)
  {
    case ADD:
      switch (detail)
      {
        case LEX_ADD:
          gen_ExpEval(STACK_OP_ADD);
          // printf("+");
          break;
        case LEX_SUB:
          gen_ExpEval(STACK_OP_SUB);
          // printf("-");
          break;
        default:
          //  printf("%d\n", detail);
           return SYNTAX_ERROR;
          break;
      }
      break;

    case MULT:
      switch (detail)
      {
        case LEX_MUL:
          gen_ExpEval(STACK_OP_MUL);
          // printf("*");
          break;
        case LEX_DIV:
          gen_ExpEval(STACK_OP_DIV);
          // printf("/");
          break;
        default:
          //  printf("%d\n", detail);
           return SYNTAX_ERROR;
          break;
      }
      break;

    case COMP:
      switch (detail)
      {
        case LEX_LESS:
          gen_ExpEval(STACK_OP_LT);
          // printf("<");
          break;
        case LEX_LESS_EQUAL:
          gen_ExpEval(STACK_OP_LTE);
          // printf("<=");
          break;
        case LEX_GREATER:
          gen_ExpEval(STACK_OP_GT);
          // printf(">");
          break;
        case LEX_GREATER_EQUAL:
          gen_ExpEval(STACK_OP_GTE);
          // printf(">=");
          break;
        default:
          //  printf("%d\n", detail);
           return SYNTAX_ERROR;
          break;
      }
      break;

    case EQUAL:
      switch (detail)
      {
        case LEX_EQUAL:
          gen_ExpEval(STACK_OP_EQ);
          // printf("==");
          break;
        case LEX_NOT_EQUAL:
          gen_ExpEval(STACK_OP_NEQ);
          // printf("!=");
          break;
        default:
          break;
      }
      break;

    case INTEGER:
      switch (detail)
      {
        case LEX_ID:
          stackInsertFirst(&expVals, STACK_ID, tokenValue->lexData.data);
          // printf("id %s", tokenValue->lexData.data);
          break;
        case LEX_INT:
          stackInsertFirst(&expVals, STACK_INT, tokenValue->lexData.data);
          // printf("int %s", tokenValue->lexData.data);
          break;
        case LEX_DOUBLE:
          stackInsertFirst(&expVals, STACK_FLOAT, tokenValue->lexData.data);
          // printf("double %s", tokenValue->lexData.data);
          break;
        case LEX_STRING:
          stackInsertFirst(&expVals, STACK_STRING, tokenValue->lexData.data);
          // printf("string %s", tokenValue->lexData.data);
          break;
        case LEX_KEYWORD_NIL:
          stackInsertFirst(&expVals, STACK_NIL, " ");
          // printf("nil");
          break;
        default:
          //  printf("%d\n", detail);
           return SYNTAX_ERROR;
          break;
      }
      break;

    case EXPRESSION:
      // printf("E");
      break;

    default:
      //NOT IN CASES -> dont to anything
      //printf("%d");
      return 0;
      break;
  }
  // printf("\n");
  return 0;
}



//---------------------------LIST---------------------------

//Initialise list and make its first value to be DOLLAR
void InitList (tList *L) {
  tElemPtr newElemPointer = malloc(sizeof(struct tElem));
  if(newElemPointer == NULL)
  {
    L->Last = NULL;
    L->Top = NULL;
    L->First = NULL;
    //Error();
  }
  else
  {
    newElemPointer->data = DOLLAR;
    newElemPointer->rptr = NULL;
    newElemPointer->lptr = NULL;

    L->Last = newElemPointer;
    L->Top = newElemPointer;
    L->First = newElemPointer;
  }
}

//Delete list and free the allocated memory
void DisposeList (tList *L) {
  while(L->First != NULL)
  {
    tElemPtr current = L->Last;

    if(current->lptr != NULL)
    {
      L->Last = current->lptr;
      L->Last->rptr = NULL;

      current->lptr = NULL;
      free(current);
    }
    else
    {
      free(current);

      L->Last = NULL;
      L->Top = NULL;
      L->First = NULL;
    }
  }
}

//Push new element to the top of the list
void PushList (tList *L, precedency element, int tokenData/*, tToken *t*/)
{
  if(L->Last != NULL){
    tElemPtr newElemPointer = malloc(sizeof(struct tElem));
    if(newElemPointer == NULL){
      //Error();
    }
    else{
      newElemPointer->data = element;
      newElemPointer->token = tokenData;

      newElemPointer->rptr = NULL;
      newElemPointer->lptr = L->Last;
      L->Last->rptr = newElemPointer;
      L->Last = newElemPointer;
    }
  }	//endif
}

//Push new element after the "top" (topmost ,not Expression element) of the list
void PostList (tList *L, precedency element)
{
  if(L->Top != NULL){
    tElemPtr newElemPointer = malloc(sizeof(struct tElem));
    if(newElemPointer == NULL){
      //Error();
    }
    else{
      //Insert new
      newElemPointer->data = element;
      newElemPointer->rptr = L->Top->rptr;
      newElemPointer->lptr = L->Top;
      //Tie in following
      if(L->Top->rptr != NULL){
        L->Top->rptr->lptr = newElemPointer;
      }
      else
      {
        L->Last = newElemPointer;
      }
      //Tie in previous
      L->Top->rptr = newElemPointer;
    }
  }	//endif
}

//Move Top pointer to the topmost element of the list, which is not Expression
void TopList(tList *L)
{
  L->Top = L->First;
  tElemPtr temp = L->Last;
  while(temp != NULL)
  {
    if(temp->data > G && temp->data < EXPRESSION) //element is term
    {
      L->Top = temp;
      return;
    }

    if(temp->lptr != NULL)
    {
      temp = temp->lptr;
    }
    else
    {
      temp = NULL;
    }
  }
}
