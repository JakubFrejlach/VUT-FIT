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
#include <stdio.h>
#include <stdlib.h>
#include "dstring.h"

#ifndef GENERATE_H
    void printOnly(dString *s, char *input);
#endif

/**
 * Type of item saved in stack
 */
typedef enum stackType
{
    STACK_ID,
    STACK_INT,
    STACK_FLOAT,
    STACK_STRING,
    STACK_NIL,

    STACK_JUMPLABEL,
    STACK_OP_LT,
    STACK_OP_GT,
    STACK_OP_EQ,
    STACK_OP_NEQ,
    STACK_OP_LTE,
    STACK_OP_GTE,

    STACK_OP_ADD,
    STACK_OP_SUB,
    STACK_OP_MUL,
    STACK_OP_DIV,
} stackType;

/**
 * Type of item saved in stack
 */
typedef struct stackItem
{
    stackType type;
    dString value;
    struct stackItem *lptr;
    struct stackItem *rptr;
} *stackItemPtr;

/**
 * Struct of a stack
 */
typedef struct
{
    stackItemPtr First;
    stackItemPtr Act;
    stackItemPtr Last;
} stack;

/**
 * Get the first item, if empty NULL
 */
stackItemPtr stackFirst(stack *);

/**
 * Get the last item, if empty NULL
 */
stackItemPtr stackLast(stack *);

/**
 * Get the second item, if empty or only one item in stack -> NULL
 */
stackItemPtr stackSucc(stack *);

/**
 * Stack init
 */
void stackInit(stack *);

/**
 * Disposal of stack, freeing memory
 */
void stackDispose(stack *);

/**
 * Insert into stack on the first position
 */
void stackInsertFirst(stack *, stackType, char *);

/**
 * Insert into stack on the last position
 */
void stackInsertLast(stack *, stackType, char *);

/**
 * Deletes the first item
 */
void stackDeleteFirst(stack *);

/**
 * Deletes the last item
 */
void stackDeleteLast(stack *);