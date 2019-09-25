/**
 * Project: IFJ18 compiler implementation.
 *
 * Stack implementation -> taken from IAL lessons.
 *
 * Jakub Frejlach - xfrejl00
 * Katerina Fortova - xforto00
 * Tibor Skvrnda - xskvrn00
 * Lukas Licek - xlicek01
 */

#ifndef GENERATE_H
#define GENERATE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dstring.h"
#include "symtable.h"
#include "stack.h"

/**
 * Escape sequence buffer size
 */
#define ESCAPE_BUFFER_SIZE 4
#define HEX_TO_INT 256

/**
 * Flags indicating, where we are -> deciding the output 
 */
int IN_FUNC;
int IN_EXP_EVAL;
int IN_WHILE;

/**
 * Helper counter variables
 */ 
int varCounter;
int varLocalCounter;
int ifCounter;
int ifLocalCounter;

/**
 * Flags indicating, if any of following built-in functions was used
 */ 
int GEN_FLAG_INPUTS;
int GEN_FLAG_INPUTI;
int GEN_FLAG_INPUTF;
int GEN_FLAG_PRINT;
int GEN_FLAG_LENGTH;
int GEN_FLAG_SUBSTR;
int GEN_FLAG_ORD;
int GEN_FLAG_CHR;
int GEN_FLAG_STRINGCOMP;

/**
 * Used when function is called without assigning, the %retval is callback will be
 * also %retval of current function, if it's not the main body
 */ 
int GEN_FLAG_EMPTY_CALL;

/**
 * Indicates that nil is supposed to be assigned to variable that print was assigned to
 */
int GEN_FLAG_PRINT_ASSIGN;

/**
 * Indicates that nil is supposed to be assigned to variable
 */
int GEN_FLAG_NIL;

/**
 * Indicates that current expression should result as a value of bool, if it's not alredy,
 * it'll be converted
 */
int GEN_FLAG_BOOL;

/**
 * Main output string holder
 */
dString outputHeader;
dString outputMain;
dString outputFuncs;

/**
 * Name of function, we're currently in
 */
dString funcName;

/**
 * Evaluated expression holder
 */
dString expOutput;

/**
 * If we're in a while cycle, definitions are being saved to a different string,
 * then are being printed after the body of while
 */
dString whileDefs;
dString whileOutput;

/**
 * Storing parameters, whether it's a function call or definition
 */
stack funcParams;

/**
 * Storing labels for jump in 'if' and 'while'
 */
stack jumpLabels;

/**
 * Storing evalueted expression, later to be printed
 */
stack expVals;


/**
 * 
 *  STRING STORING FUNCTIONS
 * 
 */

/**
 * Print escaped char
 */
void printEscape(dString *s, int c);

/**
 * Print string, if find char to be printed as escaped, call printEscape()
 */
void printString(dString *s, char *input);

/**
 * Print the input with \n at the beggining
 */
void printLine(dString *s, char *input);

/**
 * Print the input
 */
void printOnly(dString *s, char *input);

/**
 * Print float as %a
 */
void printFloat(dString *s, char *input);

/**
 * Returns dString variable, according to flags
 */
dString *output();

/**
 * 
 *  BULT-IN FUNCTIONS TEMPLATES
 * 
 */

/**
 * Template of built in function for string comparison
 */
void gen_StringComp();

/**
 * Template of built in function 'inputs'
 */
void gen_Inputs();

/**
 * Template of built in function 'inputi'
 */
void gen_Inputi();

/**
 * Template of built in function 'inputf'
 */
void gen_Inputf();

/**
 * Template of built in function 'print'
 */
void gen_Print();

/**
 * Template of built in function 'length'
 */
void gen_Length();

/**
 * Template of built in function 'substr'
 */
void gen_Substr();

/**
 * Template of built in function 'ord'
 */
void gen_Ord();

/**
 * Template of built in function 'chr'
 */
void gen_Chr();


/**
 * 
 *  CONTROL FLOW TEMPLATES
 * 
 */

/**
 * IF - start
 */
void gen_If();

/**
 * IF - else
 */
void gen_Else();

/**
 * IF - end
 */
void gen_EndIf();

/**
 * WHILE - label
 */
void gen_While();

/**
 * WHILE - condition
 */
void gen_WhileCond();

/**
 * WHILE - end
 */
void gen_EndWhile();

/**
 * Expression template
 */
void gen_Expression();

/**
 * Evaluate first two items from the varStack according to the stackType called from expresssion.c
 */
void gen_ExpEval(stackType);

/**
 * Variable assign template
 */
void gen_Assign(symTabListItem *var);

/**
 * Function definition template
 */
void gen_DefFunc(symTabListItem *input);

/**
 * Built-in function definition template
 */
void gen_DefFuncBuit(char *);

/**
 * End of function template (POPFRAME, RETURN)
 */
void gen_EndFunc();

/**
 * Function call template
 */
void gen_CallFunc(symTabListItem* label);

/**
 * End of file template
 */
void gen_Eof();


/**
 * 
 *  FUNCTIONS CALLED FROM ANALYSIS()
 * 
 */

/**
 * Initialization of all flags, global variables, stacks and dStrings
 */
void generateInit();

/**
 * Outputting the main dStrings
 */
void generatePrint();

/**
 * Cleaning and freeing all memory
 */
void generateClean();

#endif