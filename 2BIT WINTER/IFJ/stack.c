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

#include "stack.h"

void stackInit(stack *L)
{
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
}

void stackDispose(stack *L)
{
    // empty check
    if (!L->First)
        return;

    stackItemPtr item = L->First;

    while (item)
    {
        stackItemPtr next = item->rptr;
        dStringFree(&(item->value));
        free(item);
        item = next;
    }

    // delete pointers
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
}

void stackInsertFirst(stack *L, stackType type, char *value)
{
    // memory alloc, check
    stackItemPtr newItem = malloc(sizeof(struct stackItem));
    if (!newItem)
    {
        return;
    }
    else
    {
        // save values and pointers
        newItem->type = type;
        dStringInit(&(newItem->value));
        printOnly(&(newItem->value), value);
        newItem->rptr = L->First;
        newItem->lptr = NULL;

        // if stack is not empty
        if (L->First)
        {
            L->First->lptr = newItem;
        }
        // if stack is empty, it's also the last item
        else
        {
            L->Last = newItem;
        }

        L->First = newItem;
    }
}

void stackInsertLast(stack *L, stackType type, char *value)
{
    // alloc memory, checl
    stackItemPtr newItem = malloc(sizeof(struct stackItem));
    if (!newItem)
    {
        return;
    }
    else
    {
        // save values and pointers
        newItem->type = type;
        dStringInit(&(newItem->value));
        printOnly(&(newItem->value), value);
        newItem->rptr = NULL;
        newItem->lptr = L->Last;
        // if stack is not empty
        if (L->First)
        {
            L->Last->rptr = newItem;
        }
        // if stack is empty, it's also the first item
        else
        {
            L->First = newItem;
        }

        L->Last = newItem;
    }
}

void stackDeleteFirst(stack *L)
{
    // stack empty, return
    if (!L->First)
        return;

    // Active check
    if (L->First == L->Act)
        L->Act = NULL;
    // position check
    if (L->First == L->Last)
        L->Last = NULL;

    // save pointer and free
    stackItemPtr second = L->First->rptr;

    dStringFree(&(L->First->value));
    free(L->First);

    // save to first
    L->First = second;
}

void stackDeleteLast(stack *L)
{
    //  empty stack, returns
    if (!L->First)
        return;

    // Active check
    if (L->Last == L->Act)
        L->Act = NULL;

    // position check
    if (L->Last == L->First)
        L->First = NULL;

    // save the left pointer and free current one
    stackItemPtr preLast = L->Last->lptr;

    dStringFree(&(L->Last->value));
    free(L->Last);

    L->Last = preLast;
    // deletes right pointer
    if (L->First)
    {
        L->Last->rptr = NULL;
    }
}

stackItemPtr stackFirst(stack *L)
{
    L->Act = L->First;
    return L->Act;
}

stackItemPtr stackLast(stack *L)
{
    L->Act = L->Last;
    return L->Act;
}

stackItemPtr stackSucc(stack *L)
{
    // active check
    if (L->Act)
    {
        L->Act = L->Act->rptr;
        return L->Act;
    }
    return NULL;
}