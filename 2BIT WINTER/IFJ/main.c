/**
 * Project: IFJ18 compiler implementation.
 *
 * Main program
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#include"main.h"

int main()
{
  //Syntax and semantic analysis
  int returnValue = analysis();

  if(returnValue == LEX_ERROR)
  {
    errorMsg("LEX ERROR\n");
    return returnValue;
  }
  else if(returnValue == SYNTAX_ERROR)
  {
    errorMsg("SYNTAX ERROR\n");
    return returnValue;
  }
  else if(returnValue == SEMANTIC_ERROR)
  {
    errorMsg("SEMANTIC ERROR\n");
    return returnValue;
  }
  else if(returnValue == PARAMS_ERROR)
  {
    errorMsg("PARAMS ERROR\n");
    return returnValue;
  }
  else if(returnValue == TYPE_ERROR)
  {
    errorMsg("TYPE ERROR\n");
    return returnValue;
  }
  else if(returnValue == ERROR)
  {
    errorMsg("OTHER SEMANTIC ERROR\n");
    return returnValue;
  }
  else if(returnValue == DIVISON_BY_ZERO)
  {
    errorMsg("DIVISON_BY_ZERO\n");
    return returnValue;
  }
  else if(returnValue == INTERNAL_ERROR)
  {
    errorMsg("INTERNAL ERROR\n");
    return returnValue;
  }

  return 0;
}
