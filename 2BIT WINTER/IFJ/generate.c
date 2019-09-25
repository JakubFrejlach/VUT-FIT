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

#include "generate.h"

void gen_StringComp()
{
    gen_DefFuncBuit("$sstring");
    printLine(output(), "DEFVAR LF@%tmp");
    printLine(output(), "DEFVAR LF@%tmp1");
    printLine(output(), "DEFVAR LF@%tmp2");
    printLine(output(), "DEFVAR LF@%l0");
    printLine(output(), "DEFVAR LF@%l1");
    printLine(output(), "DEFVAR LF@%c1");
    printLine(output(), "DEFVAR LF@%c2");
    printLine(output(), "DEFVAR LF@%x");
    printLine(output(), "MOVE LF@%x int@0");
    printLine(output(), "TYPE LF@%tmp LF@%0");
    printLine(output(), "JUMPIFEQ $$string$one LF@%tmp string@string");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $$string$one");
    printLine(output(), "TYPE LF@%tmp LF@%1");
    printLine(output(), "JUMPIFEQ $$string$two LF@%tmp string@string");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $$string$two");
    printLine(output(), "STRLEN LF@%l0 LF@%0");
    printLine(output(), "STRLEN LF@%l1 LF@%1");
    // both empty strings
    printLine(output(), "EQ LF@%tmp1 LF@%l0 int@0");
    printLine(output(), "EQ LF@%tmp2 LF@%l1 int@0");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@0");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@1");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@2");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@3");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp1 bool@true");
    // first string empty
    printLine(output(), "GT LF@%tmp1 LF@%l0 int@0");
    printLine(output(), "EQ LF@%tmp2 LF@%l1 int@0");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@0");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@1");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@2");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@3");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp1 bool@true");
    // second string empty
    printLine(output(), "EQ LF@%tmp1 LF@%l0 int@0");
    printLine(output(), "GT LF@%tmp2 LF@%l1 int@0");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@0");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@1");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@2");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp1 bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%2 int@3");
    printLine(output(), "AND LF@%tmp1 LF@%tmp LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp1 bool@true");

    printLine(output(), "LABEL $$string$start");
    printLine(output(), "GETCHAR LF@%tmp LF@%0 LF@%x");
    printLine(output(), "GETCHAR LF@%tmp1 LF@%1 LF@%x");
    printLine(output(), "GETCHAR LF@%c1 LF@%0 LF@%x");
    printLine(output(), "GETCHAR LF@%c2 LF@%1 LF@%x");
    printLine(output(), "JUMPIFEQ $$string$0 LF@%2 int@0");
    printLine(output(), "JUMPIFEQ $$string$1 LF@%2 int@1");
    printLine(output(), "JUMPIFEQ $$string$2 LF@%2 int@2");
    printLine(output(), "JUMPIFEQ $$string$3 LF@%2 int@3");
    printLine(output(), "LABEL $$string$0");
    printLine(output(), "LT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp2 bool@true");
    printLine(output(), "GT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp2 bool@true");
    printLine(output(), "ADD LF@%x LF@%x int@1");
    printLine(output(), "LT LF@%tmp1 LF@%x LF@%l0");
    printLine(output(), "LT LF@%tmp2 LF@%x LF@%l1");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$start LF@%tmp bool@true");
    printLine(output(), "SUB LF@%tmp1 LF@%l0 LF@%x");
    printLine(output(), "SUB LF@%tmp2 LF@%l1 LF@%x");
    printLine(output(), "LT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp bool@true");
    printLine(output(), "GT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp bool@true");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l0 LF@%x");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l1 LF@%x");
    printLine(output(), "LABEL $$string$1");
    printLine(output(), "LT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp2 bool@true");
    printLine(output(), "GT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp2 bool@true");
    printLine(output(), "ADD LF@%x LF@%x int@1");
    printLine(output(), "LT LF@%tmp1 LF@%x LF@%l0");
    printLine(output(), "LT LF@%tmp2 LF@%x LF@%l1");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$start LF@%tmp bool@true");
    printLine(output(), "SUB LF@%tmp1 LF@%l0 LF@%x");
    printLine(output(), "SUB LF@%tmp2 LF@%l1 LF@%x");
    printLine(output(), "LT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp bool@true");
    printLine(output(), "GT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp bool@true");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l0 LF@%x");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l1 LF@%x");
    printLine(output(), "LABEL $$string$2");
    printLine(output(), "LT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp2 bool@true");
    printLine(output(), "GT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp2 bool@true");
    printLine(output(), "ADD LF@%x LF@%x int@1");
    printLine(output(), "LT LF@%tmp1 LF@%x LF@%l0");
    printLine(output(), "LT LF@%tmp2 LF@%x LF@%l1");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$start LF@%tmp bool@true");
    printLine(output(), "SUB LF@%tmp1 LF@%l0 LF@%x");
    printLine(output(), "SUB LF@%tmp2 LF@%l1 LF@%x");
    printLine(output(), "LT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp bool@true");
    printLine(output(), "GT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%tmp1 LF@%tmp2");
    printLine(output(), "EQ LF@%tmp1 LF@%c1 LF@%c2");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp bool@true");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l0 LF@%x");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l1 LF@%x");
    printLine(output(), "LABEL $$string$3");
    printLine(output(), "LT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp2 bool@true");
    printLine(output(), "GT LF@%tmp2 LF@%tmp LF@%tmp1");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp2 bool@true");
    printLine(output(), "ADD LF@%x LF@%x int@1");
    printLine(output(), "LT LF@%tmp1 LF@%x LF@%l0");
    printLine(output(), "LT LF@%tmp2 LF@%x LF@%l1");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$start LF@%tmp bool@true");
    printLine(output(), "SUB LF@%tmp1 LF@%l0 LF@%x");
    printLine(output(), "SUB LF@%tmp2 LF@%l1 LF@%x");
    printLine(output(), "LT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$false LF@%tmp bool@true");
    printLine(output(), "GT LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp bool@true");
    printLine(output(), "EQ LF@%tmp2 LF@%tmp1 LF@%tmp2");
    printLine(output(), "EQ LF@%tmp1 LF@%c1 LF@%c2");
    printLine(output(), "AND LF@%tmp LF@%tmp1 LF@%tmp2");
    printLine(output(), "JUMPIFEQ $$string$true LF@%tmp bool@true");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l0 LF@%x");
    printLine(output(), "JUMPIFEQ $$string$false LF@%l1 LF@%x");
    printLine(output(), "LABEL $$string$true");
    printLine(output(), "MOVE LF@%retval bool@true");
    printLine(output(), "JUMP $$string$end");
    printLine(output(), "LABEL $$string$false");
    printLine(output(), "MOVE LF@%retval bool@false");
    printLine(output(), "LABEL $$string$end");
    gen_EndFunc();
}

void gen_Inputs()
{
    gen_DefFuncBuit("inputs");
    printLine(output(), "READ LF@%retval string");
    gen_EndFunc();
}

void gen_Inputi()
{
    gen_DefFuncBuit("inputi");
    printLine(output(), "READ LF@%retval int");
    gen_EndFunc();
}

void gen_Inputf()
{
    gen_DefFuncBuit("inputf");
    printLine(output(), "READ LF@%retval float");
    gen_EndFunc();
}

void gen_Print()
{
    stackItemPtr param = stackFirst(&funcParams);

    while (param)
    {
        printLine(output(), "WRITE ");

        switch (param->type)
        {
            case STACK_ID:
                printOnly(output(), "LF@");
                printOnly(output(), param->value.data);
                break;
            case STACK_INT:
                printOnly(output(), "int@");
                printOnly(output(), param->value.data);
                break;
            case STACK_FLOAT:
                printOnly(output(), "float@");
                printFloat(output(), param->value.data);
                break;
            case STACK_STRING:
                printOnly(output(), "string@");
                printString(output(), param->value.data);
                break;
            case STACK_NIL:
                printOnly(output(), "nil@nil");
                break;
            default:
                break;
        }

        stackDeleteFirst(&funcParams);
        param = stackFirst(&funcParams);
    }

    if (IN_FUNC)
    {
        if (GEN_FLAG_PRINT_ASSIGN)
        {
            GEN_FLAG_EMPTY_CALL = 0;
            printLine(output(), "CREATEFRAME");
            printLine(output(), "PUSHFRAME");
            printLine(output(), "DEFVAR LF@%retval");
            printLine(output(), "MOVE LF@%retval nil@nil");
            printLine(output(), "POPFRAME");
        }
        else 
        {
            printLine(output(), "MOVE LF@%retval nil@nil");
        }
    }
    else {
        if (GEN_FLAG_PRINT_ASSIGN)
        {
            GEN_FLAG_EMPTY_CALL = 0;
            printLine(output(), "CREATEFRAME");
            printLine(output(), "PUSHFRAME");
            printLine(output(), "DEFVAR LF@%retval");
            printLine(output(), "MOVE LF@%retval nil@nil");
            printLine(output(), "POPFRAME");
        }
    }
}

void gen_Length()
{
    gen_DefFuncBuit("length");
    printLine(output(), "DEFVAR LF@%type");
    printLine(output(), "TYPE LF@%type LF@%0");
    printLine(output(), "DEFVAR LF@%cond");
    printLine(output(), "EQ LF@%cond LF@%type string@string");
    printLine(output(), "JUMPIFEQ $length$if$true LF@%cond bool@true");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $length$if$true");
    printLine(output(), "STRLEN LF@%retval LF@%0");
    gen_EndFunc();
}

void gen_Substr()
{
    gen_DefFuncBuit("substr");
    printLine(output(), "DEFVAR LF@%type");
    printLine(output(), "DEFVAR LF@%cond");
    printLine(output(), "TYPE LF@%type LF@%0");
    printLine(output(), "EQ LF@%cond LF@%type string@string");
    printLine(output(), "JUMPIFEQ $substr$if$true LF@%cond bool@true");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $substr$if$true");
    printLine(output(), "TYPE LF@%type LF@%1");
    printLine(output(), "EQ LF@%cond LF@%type string@int");
    printLine(output(), "JUMPIFEQ $substr$if1$true LF@%cond bool@true");
    printLine(output(), "JUMPIFEQ $substr$if1$float LF@%type string@float");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $substr$if1$float");
    printLine(output(), "FLOAT2INT LF@%1 LF@%1");
    printLine(output(), "LABEL $substr$if1$true");
    printLine(output(), "TYPE LF@%type LF@%2");
    printLine(output(), "EQ LF@%cond LF@%type string@int");
    printLine(output(), "JUMPIFEQ $substr$if2$true LF@%cond bool@true");
    printLine(output(), "JUMPIFEQ $substr$if2$float LF@%type string@float");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $substr$if2$float");
    printLine(output(), "FLOAT2INT LF@%2 LF@%2");
    printLine(output(), "LABEL $substr$if2$true");
    printLine(output(), "DEFVAR LF@%count");
    printLine(output(), "MOVE LF@%count int@1");
    printLine(output(), "DEFVAR LF@%length");
    printLine(output(), "STRLEN LF@%length LF@%0");
    printLine(output(), "LT LF@%cond LF@%1 int@0");
    printLine(output(), "JUMPIFEQ $substr$return LF@%cond bool@true");
    printLine(output(), "GT LF@%cond LF@%1 LF@%length");
    printLine(output(), "JUMPIFEQ $substr$return LF@%cond bool@true");
    printLine(output(), "JUMPIFEQ $substr$return LF@%1 LF@%length");
    printLine(output(), "LT LF@%cond LF@%2 int@1");
    printLine(output(), "JUMPIFEQ $substr$return LF@%cond bool@true");
    printLine(output(), "MOVE LF@%retval string@");
    printLine(output(), "DEFVAR LF@%str");
    printLine(output(), "LABEL $substr$concat");
    printLine(output(), "GETCHAR LF@%str LF@%0 LF@%1");
    printLine(output(), "CONCAT LF@%retval LF@%retval LF@%str");
    printLine(output(), "ADD LF@%1 LF@%1 int@1");
    printLine(output(), "JUMPIFEQ $substr$return LF@%count LF@%2");
    printLine(output(), "ADD LF@%count LF@%count int@1");
    printLine(output(), "JUMPIFEQ $substr$return LF@%1 LF@%length");
    printLine(output(), "JUMP $substr$concat");
    printLine(output(), "LABEL $substr$return");
    gen_EndFunc();
}

void gen_Ord()
{
    gen_DefFuncBuit("ord");
    printLine(output(), "DEFVAR LF@%cond");
    printLine(output(), "DEFVAR LF@%type");
    printLine(output(), "TYPE LF@%type LF@%0");
    printLine(output(), "JUMPIFEQ $ord$if$true LF@%type string@string");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $ord$if$true");
    printLine(output(), "TYPE LF@%type LF@%1");
    printLine(output(), "JUMPIFEQ $ord$if1$true LF@%type string@int");
    printLine(output(), "JUMPIFEQ $ord$if1$float LF@%type string@float");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $ord$if1$float");
    printLine(output(), "FLOAT2INT LF@%1 LF@%1");
    printLine(output(), "LABEL $ord$if1$true");
    printLine(output(), "DEFVAR LF@%length");
    printLine(output(), "STRLEN LF@%length LF@%0");
    printLine(output(), "JUMPIFEQ $ord$return LF@%1 LF@%length");
    printLine(output(), "LT LF@%cond LF@%1 int@0");
    printLine(output(), "JUMPIFEQ $ord$return LF@%cond bool@true");
    printLine(output(), "GT LF@%cond LF@%1 LF@%length");
    printLine(output(), "JUMPIFEQ $ord$return LF@%1 LF@%length");
    printLine(output(), "STRI2INT LF@%retval LF@%0 LF@%1");
    printLine(output(), "LABEL $ord$return");
    gen_EndFunc();
}

void gen_Chr()
{
    gen_DefFuncBuit("chr");
    printLine(output(), "DEFVAR LF@%cond");
    printLine(output(), "DEFVAR LF@%type");
    printLine(output(), "TYPE LF@%type LF@%0");
    printLine(output(), "JUMPIFEQ $chr$if$true LF@%type string@int");
    printLine(output(), "JUMPIFEQ $chr$if$float LF@%type string@float");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $chr$if$float");
    printLine(output(), "FLOAT2INT LF@%0 LF@%0");
    printLine(output(), "LABEL $chr$if$true");
    printLine(output(), "GT LF@%cond LF@%0 int@-1");
    printLine(output(), "JUMPIFEQ $chr$if1$true LF@%cond bool@true");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $chr$if1$true");
    printLine(output(), "LT LF@%cond LF@%0 int@256");
    printLine(output(), "JUMPIFEQ $chr$if2$true LF@%cond bool@true");
    printLine(output(), "EXIT int@4");
    printLine(output(), "LABEL $chr$if2$true");
    printLine(output(), "INT2CHAR LF@%retval LF@%0");
    gen_EndFunc();
}

void gen_Assign(symTabListItem *var) 
{
    if (!var->sData.defined)
    {
        var->sData.defined = 1;
        if (IN_WHILE)
        {
            printLine(&whileDefs, "DEFVAR LF@");
            printOnly(&whileDefs, var->sData.ID);
        }
        else
        {
            printLine(output(), "DEFVAR LF@");
            printOnly(output(), var->sData.ID);
        }
        printLine(output(), "MOVE LF@");
        printOnly(output(), var->sData.ID);
        printOnly(output(), " nil@nil");
    }
    printLine(output(), "MOVE LF@");
    printOnly(output(), var->sData.ID);
    printOnly(output(), " TF@%retval");
    
    if (IN_FUNC)
    {
        printLine(output(), "MOVE LF@%retval LF@");
        printOnly(output(), var->sData.ID);
    }
}

void gen_DefFuncBuit(char* label)
{
    printLine(output(), "LABEL $");
    printOnly(output(), label);
    printLine(output(), "PUSHFRAME");
    printLine(output(), "DEFVAR LF@%retval");
    printLine(output(), "MOVE LF@%retval nil@nil");

    printOnly(&funcName, label);
}

void gen_CallFuncParams()
{
    stackItemPtr param = stackFirst(&funcParams);
    int x = 0;
    while (param)
    {
        char str[50];
        sprintf(str, "%d", x);
        printLine(output(), "DEFVAR TF@%");
        printOnly(output(), str);

        printLine(output(), "MOVE TF@%");
        printOnly(output(), str);

        switch(param->type)
        {
            case STACK_ID:
                printOnly(output(), " LF@");
                printOnly(output(), param->value.data);
                break;
            case STACK_INT:
                printOnly(output(), " int@");
                printOnly(output(), param->value.data);
                break;
            case STACK_FLOAT:
                printOnly(output(), " float@");
                printFloat(output(), param->value.data);
                break;
            case STACK_STRING:
                printOnly(output(), " string@");
                printString(output(), param->value.data);
                break;
            case STACK_NIL:
                printOnly(output(), " nil@nil");
                break;
            default:
                break;
        }
        
        stackDeleteFirst(&funcParams);
        param = stackFirst(&funcParams);
        x++;
    }
}

void gen_DefFuncParams()
{
    stackItemPtr param = stackFirst(&funcParams);
    int x = 0;
    while (param) {
        printLine(output(), "DEFVAR LF@");
        printOnly(output(), param->value.data);
        printLine(output(), "MOVE LF@");
        printOnly(output(), param->value.data);
        printOnly(output(), " LF@%");
        char str[50];
        sprintf(str, "%d", x);
        printOnly(output(), str);
        stackDeleteFirst(&funcParams);
        param = stackFirst(&funcParams);
        x++;
    }
}

void gen_DefFunc(symTabListItem *input)
{
    IN_FUNC = 1;
    printLine(output(), "LABEL $");
    printOnly(output(), input->sData.ID);
    printLine(output(), "PUSHFRAME");
    printLine(output(), "DEFVAR LF@%retval");
    printLine(output(), "MOVE LF@%retval nil@nil");
    if (stackFirst(&funcParams))
    {
        gen_DefFuncParams();
    }

    printOnly(&funcName, input->sData.ID);
}

void gen_EndFunc()
{
    printLine(output(), "POPFRAME");
    printLine(output(), "RETURN\n");

    dStringClear(&funcName);
    IN_FUNC = 0;
    ifLocalCounter = 0;
    varLocalCounter = 0;
}

void gen_CallFunc(symTabListItem *label)
{
    if (!strcmp(label->sData.ID, "print"))
    {
        gen_Print();
        return;
    }

    // flag setter
    if (!strcmp(label->sData.ID, "inputs"))
        GEN_FLAG_INPUTS = 1;
    if (!strcmp(label->sData.ID, "inputi"))
        GEN_FLAG_INPUTI = 1;
    if (!strcmp(label->sData.ID, "inputf"))
        GEN_FLAG_INPUTF = 1;
    if (!strcmp(label->sData.ID, "length"))
        GEN_FLAG_LENGTH = 1;
    if (!strcmp(label->sData.ID, "substr"))
        GEN_FLAG_SUBSTR = 1;
    if (!strcmp(label->sData.ID, "ord"))
        GEN_FLAG_ORD = 1;
    if (!strcmp(label->sData.ID, "chr"))
        GEN_FLAG_CHR = 1;
    

    // params 
    printLine(output(), "CREATEFRAME");
    if (stackFirst(&funcParams))
    {
        gen_CallFuncParams();
    }
    printLine(output(), "CALL $");
    printOnly(output(), label->sData.ID);

    if (GEN_FLAG_EMPTY_CALL) {
        GEN_FLAG_EMPTY_CALL = 0;
        if (IN_FUNC)
        {
            printLine(output(), "MOVE LF@%retval TF@%retval");
        }
    }
}

void gen_Eof()
{
    printLine(output(), "POPFRAME");
    printLine(output(), "CLEARS");
    printLine(output(), "EXIT int@0");
}

void printEscape(dString *s, int c)
{
    char escape[ESCAPE_BUFFER_SIZE];
    // check for overflow
    if (c < 0)
    {
        c += HEX_TO_INT;
        sprintf(escape, "\\%d", c);
    }
    else
    {
        sprintf(escape, "\\0%0d", c);
    }
    
    for (int x = 0; x < ESCAPE_BUFFER_SIZE; x++)
    {
        dStringAppend(&(*s), escape[x]);
    }
}

void printString(dString *s, char *input)
{
    if (!s || !input)
    {
        return;
    }

    int length = strlen(input);
    for (int x = 0; x < length; x++)
    {
        if (input[x] <= 32 || input[x] == 35 || input[x] == 92)
        {
            printEscape(&(*s), input[x]);
        }
        else
        {
            dStringAppend(&(*s), input[x]);
        }
    }
}

void printLine(dString *s, char *input)
{
    if (!s || !input)
    {
        return;
    }

    dStringAppend(&(*s), '\n');
    int length = strlen(input);
    for (int x = 0; x < length; x++)
    {
        dStringAppend(&(*s), input[x]);
    }
}

void printOnly(dString *s, char *input)
{
    if (!s || !input)
    {
        return;
    }

    int length = strlen(input);
    for (int x = 0; x < length; x++)
    {
        dStringAppend(&(*s), input[x]);
    }
}

void printFloat(dString *s, char *input)
{
    if (!s || !input)
    {
        return;
    }
    
    char str[50];
    sprintf(str, "%a", atof(input));

    int length = strlen(str);
    for (int x = 0; x < length; x++)
    {
        dStringAppend(&(*s), str[x]);
    }
}

dString *output()
{
    if (IN_EXP_EVAL)
    {
        return &expOutput;
    }
    else if (IN_WHILE)
    {
        return &whileOutput;
    }
    else if (IN_FUNC)
    {
        return &outputFuncs;
    }
    else
    {
        return &outputMain;
    }
}


void generateInit()
{
    // dString items init
    dStringInit(&outputHeader);
    dStringInit(&outputMain);
    dStringInit(&outputFuncs); 
    dStringInit(&funcName);
    dStringInit(&expOutput);
    dStringInit(&whileDefs);
    dStringInit(&whileOutput);

    //  Header file fillin
    printOnly(&outputHeader, ".IFJcode18\nJUMP $$main");

    //  Main output init filling
    printOnly(&outputMain, "LABEL $$main");
    printLine(&outputMain, "CREATEFRAME");
    printLine(&outputMain, "PUSHFRAME");

    // Helper variables setup
    IN_FUNC = 0;
    IN_EXP_EVAL = 0;
    varCounter = 0;
    varLocalCounter = 0;
    ifCounter = 0;
    ifLocalCounter = 0;

    // Initial flag setup
    GEN_FLAG_INPUTS = 0;
    GEN_FLAG_INPUTI = 0;
    GEN_FLAG_INPUTF = 0;
    GEN_FLAG_PRINT= 0;
    GEN_FLAG_LENGTH = 0;
    GEN_FLAG_SUBSTR = 0;
    GEN_FLAG_ORD = 0;
    GEN_FLAG_CHR = 0;
    GEN_FLAG_EMPTY_CALL = 0;
    GEN_FLAG_PRINT_ASSIGN = 0;
    GEN_FLAG_NIL = 0;
    GEN_FLAG_BOOL = 0;
    GEN_FLAG_STRINGCOMP = 0;

    // Initial stacks setup
    stackInit(&funcParams);
    stackInit(&jumpLabels);
    stackInit(&expVals);
}

void generatePrint()
{
    IN_FUNC = 1;
    if (GEN_FLAG_INPUTS)
        gen_Inputs();
    IN_FUNC = 1;
    if (GEN_FLAG_INPUTI)
        gen_Inputi();
    IN_FUNC = 1;
    if (GEN_FLAG_INPUTF)
        gen_Inputf();
    IN_FUNC = 1;
    if (GEN_FLAG_LENGTH)
        gen_Length();
    IN_FUNC = 1;
    if (GEN_FLAG_SUBSTR)
        gen_Substr();
    IN_FUNC = 1;
    if (GEN_FLAG_ORD)
        gen_Ord();
    IN_FUNC = 1;
    if (GEN_FLAG_CHR)
        gen_Chr();
    IN_FUNC = 1;
    if (GEN_FLAG_STRINGCOMP)
        gen_StringComp();
    IN_FUNC = 0;

    // Cleaning frames, exit 0 
    gen_Eof();

    // Output code print
    printf("%s\n", outputHeader.data);
    printf("%s\n", outputFuncs.data);
    printf("%s", outputMain.data);
}

void generateClean()
{
    // Strings clean
    dStringFree(&outputHeader);
    dStringFree(&outputMain);
    dStringFree(&outputFuncs);
    dStringFree(&funcName);
    dStringFree(&expOutput);
    dStringFree(&whileDefs);
    dStringFree(&whileOutput);
    // Stacks clean
    stackDispose(&funcParams);
    stackDispose(&jumpLabels);
    stackDispose(&expVals);
}

void gen_If()
{
    // jump label setup
    char label[50];
    if (IN_FUNC)
    {
        sprintf(label, "$%s$if%d", funcName.data, ifLocalCounter++);
    }
    else
    {
        sprintf(label, "$main$if%d", ifCounter++);
    }
    // if - start template
    stackInsertLast(&jumpLabels, STACK_JUMPLABEL, label);
    printLine(output(), "JUMPIFNEQ ");
    printOnly(output(), label);
    printOnly(output(), "$else TF@%retval bool@true");
}

void gen_Else()
{
    // else template
    printLine(output(), "JUMP ");
    printOnly(output(), stackLast(&jumpLabels)->value.data);
    printOnly(output(), "$end");

    printLine(output(), "LABEL ");
    printOnly(output(), stackLast(&jumpLabels)->value.data);
    printOnly(output(), "$else");
}

void gen_EndIf()
{
    // if - end template
    printLine(output(), "LABEL ");
    printOnly(output(), stackLast(&jumpLabels)->value.data);
    printOnly(output(), "$end");
    // cleaning jump labels
    stackDeleteLast(&jumpLabels);
    printOnly(output(), "\n");
}

void gen_While()
{
    // jump label setup
    char label[50];
    if (IN_FUNC)
    {
        sprintf(label, "$%s$if%d", funcName.data, ifLocalCounter++);
    }
    else
    {
        sprintf(label, "$main$if%d", ifCounter++);
    }
    stackInsertLast(&jumpLabels, STACK_JUMPLABEL, label);

    // for embedded whiles
    IN_WHILE++;
    printLine(output(), "LABEL ");
    printOnly(output(), label);

    
}

void gen_WhileCond()
{
    // while condition template
    printLine(output(), "JUMPIFNEQ ");
    printOnly(output(), stackLast(&jumpLabels)->value.data);
    printOnly(output(), "$end TF@%retval bool@true");
}

void gen_EndWhile()
{
    IN_WHILE--;
    // if hit end of the initial while cycle, print the definitions firtst, then the cycle itself
    if (IN_WHILE == 0)
    {
        printOnly(output(), whileDefs.data);

        printOnly(output(), whileOutput.data);

        dStringClear(&whileDefs);
        dStringClear(&whileOutput);
    }

    // while - end template
    printLine(output(), "JUMP ");
    printOnly(output(), stackLast(&jumpLabels)->value.data);
    printLine(output(), "LABEL ");
    printOnly(output(), stackLast(&jumpLabels)->value.data);
    printOnly(output(), "$end");
    printOnly(output(), "\n");

    // jumplabels cleaning
    stackDeleteLast(&jumpLabels);
}

void gen_Expression()
{
    char tmp[50];
    stackItemPtr first;

    // expression string is empty, it's a single item
    if ( expOutput.stringLenght == 0 )
    {
        first = stackFirst(&expVals);
        if (!first)
        {
            return;
        }

        // get tmp variable label
        sprintf(tmp, "%%tmp%d", varCounter);

        // define tmp variable
        if (IN_WHILE)
        {
            printLine(&whileDefs, "DEFVAR LF@");
            printOnly(&whileDefs, tmp);
        }
        else
        {
            printLine(output(), "DEFVAR LF@");
            printOnly(output(), tmp);
        }

        // move the item to tmp - start
        printLine(output(), "MOVE LF@");
        printOnly(output(), tmp);

        // if ID is not defined, this flag is set up in parser.c, move nil
        if (GEN_FLAG_NIL)
        {
            printOnly(output(), " nil@nil");
            GEN_FLAG_NIL = 0;
        }
        else
        {
            switch (first->type)
            {
            case STACK_ID:
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                break;
            case STACK_INT:
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                break;
            case STACK_FLOAT:
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                break;
            case STACK_STRING:
                printOnly(output(), " string@");
                printString(output(), first->value.data);
                break;
            case STACK_NIL:
                printOnly(output(), " nil@nil");
                break;
            default:
                break;
            }
        }
        

        stackDeleteFirst(&expVals);
        // move tmp to %retval for commands later to use
        printLine(output(), "CREATEFRAME");
        printLine(output(), "PUSHFRAME");
        printLine(output(), "DEFVAR LF@%retval");
        printLine(output(), "POPFRAME");
        printLine(output(), "MOVE TF@%retval LF@");
        printOnly(output(), tmp);

        // increase tmp variable
        varCounter++;
    }
    // expression string is not empty, print it
    else
    {
        printOnly(output(), expOutput.data);
        stackDeleteFirst(&expVals);
        dStringClear(&expOutput);

        sprintf(tmp, "%%tmp%d", varCounter - 1);
    }

    // expression is supposted to be bool type, if it's not, make it :)
    if (GEN_FLAG_BOOL)
    {
        GEN_FLAG_BOOL = 0;
        char tmp2[50];
        sprintf(tmp2, "%%tmp%d", varCounter);

        if (IN_WHILE)
        {
            printLine(&whileDefs, "DEFVAR LF@");
            printOnly(&whileDefs, tmp2);
        }
        else
        {
            printLine(output(), "DEFVAR LF@");
            printOnly(output(), tmp2);
        }
        printLine(output(), "TYPE LF@");
        printOnly(output(), tmp2);
        printOnly(output(), " LF@");
        printOnly(output(), tmp);
        printLine(output(), "JUMPIFEQ $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$false LF@");
        printOnly(output(), tmp2);
        printOnly(output(), " string@nil");

        printLine(output(), "JUMPIFEQ $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$bool LF@");
        printOnly(output(), tmp2);
        printOnly(output(), " string@bool");

        printLine(output(), "MOVE LF@");
        printOnly(output(), tmp2);
        printOnly(output(), " bool@true");
        printLine(output(), "JUMP $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$end");

        printLine(output(), "LABEL $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$bool");
        printLine(output(), "JUMPIFEQ $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$false bool@false LF@");
        printOnly(output(), tmp);
        printLine(output(), "MOVE LF@");
        printOnly(output(), tmp2);
        printOnly(output(), " bool@true");
        printLine(output(), "JUMP $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$end");

        printLine(output(), "LABEL $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$false");
        printLine(output(), "MOVE LF@");
        printOnly(output(), tmp2);
        printOnly(output(), " bool@false");
        printLine(output(), "LABEL $$");
        printOnly(output(), tmp2);
        printOnly(output(), "$end");
        printLine(output(), "CREATEFRAME");
        printLine(output(), "PUSHFRAME");
        printLine(output(), "DEFVAR LF@%retval");
        printLine(output(), "POPFRAME");
        printLine(output(), "MOVE TF@%retval LF@");
        printOnly(output(), tmp2);
        varCounter++;
    }
}

void gen_ExpEval(stackType type)
{
    IN_EXP_EVAL = 1;
    char tmp[100];
    sprintf(tmp, "%%tmp%d", varCounter);

    if (IN_WHILE)
    {
        printLine(&whileDefs, "DEFVAR LF@");
        printOnly(&whileDefs, tmp);
    }
    else
    {
        printLine(output(), "DEFVAR LF@");
        printOnly(output(), tmp);
    }

    stackItemPtr second = stackFirst(&expVals);
    stackItemPtr first = stackSucc(&expVals);

    if (GEN_FLAG_NIL)
    {
        printLine(output(), "EXIT int@4");
        GEN_FLAG_NIL = 0;
    }
    else { 
    switch (type)
    {
    /*  ==  *******************************************************************************/
    case STACK_OP_EQ:
        // nil == nil
        if (second->type == STACK_NIL && first->type == STACK_NIL)
        {
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
        }
        // nil == ID
        else if (second->type == STACK_NIL && first->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }
        // ID == nil
        else if (first->type == STACK_NIL && second->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }
        // nil == all ..
        else if (second->type == STACK_NIL || first->type == STACK_NIL)
        {
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
        }

        // strings
        else if (second->type == STACK_STRING || first->type == STACK_STRING)
        {
            if ((second->type == STACK_STRING && first->type != STACK_STRING && first->type != STACK_ID) ||
                (first->type == STACK_STRING && second->type != STACK_STRING && second->type != STACK_ID))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
            else if (second->type == STACK_STRING && first->type == STACK_STRING)
            {
                // string == string
                if (!strcmp(second->value.data, first->value.data))
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (first->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " string@");
                printString(output(), second->value.data);

                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " string@");
                printString(output(), first->value.data);

                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        // int == int
        else if (first->type == STACK_INT && second->type == STACK_INT)
        {
            if (atoi(first->value.data) == atoi(second->value.data))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
            else
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
        }

        // float == float
        else if (first->type == STACK_FLOAT && second->type == STACK_FLOAT)
        {
            if (atof(first->value.data) == atof(second->value.data))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
            else
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
        }

        // int == float || float == int
        else if ((first->type == STACK_INT && second->type == STACK_FLOAT) ||
                 (first->type == STACK_FLOAT && second->type == STACK_INT))
        {
            if (atof(first->value.data) == atof(second->value.data))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
            else
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
        }

        //  int == id
        else if (first->type == STACK_INT && second->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), second->value.data);
            printOnly(output(), " int@");
            printOnly(output(), first->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), second->value.data);
            printOnly(output(), " float@");
            printFloat(output(), first->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        //  id == int
        else if (second->type == STACK_INT && first->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " int@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " float@");
            printFloat(output(), second->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        //  float == id
        else if (first->type == STACK_FLOAT && second->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, tmp);
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
            }
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);

            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " float@");
            printFloat(output(), first->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), second->value.data);
            printOnly(output(), " float@");
            printFloat(output(), first->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        //  float == id
        else if (second->type == STACK_FLOAT && first->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, tmp);
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
            }
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);

            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " float@");
            printFloat(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " float@");
            printFloat(output(), second->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        else if (first->type == STACK_ID && second->type == STACK_ID)
        {
            // tmp = type(first)
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);

            // tmp2 = type(second)
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, "%2");
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
            }
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // $INT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // $FLOAT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // $STRING
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string$string LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // $NIL
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil$nil LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // INT == INT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$int");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // FLOAT == FLOAT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // STRING == STRING
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string$string");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // nil == nil
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil$nil");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // INT == FLOAT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$float");
            // defvar new
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, "%3");
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
            }
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // FLOAT == INT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$int");
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // false and end ..
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }
        break;

    /* !=     *******************************************************************************/
    case STACK_OP_NEQ:
        // nil != nil
        if (second->type == STACK_NIL && first->type == STACK_NIL)
        {
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
        }
        // nil != ID
        else if (second->type == STACK_NIL && first->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }
        // ID != nil
        else if (first->type == STACK_NIL && second->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }
        // nil != all ..
        else if (second->type == STACK_NIL || first->type == STACK_NIL)
        {
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
        }

        // strings
        else if (second->type == STACK_STRING || first->type == STACK_STRING)
        {
            if ((second->type == STACK_STRING && first->type != STACK_STRING && first->type != STACK_ID) ||
                (first->type == STACK_STRING && second->type != STACK_STRING && second->type != STACK_ID))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
            else if (second->type == STACK_STRING && first->type == STACK_STRING)
            {
                // string == string
                if (!strcmp(second->value.data, first->value.data))
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
            }
            else if (first->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " string@");
                printString(output(), second->value.data);

                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " string@");
                printString(output(), first->value.data);

                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        // int != int
        else if (first->type == STACK_INT && second->type == STACK_INT)
        {
            if (atoi(first->value.data) == atoi(second->value.data))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
            else
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
        }

        // float == float
        else if (first->type == STACK_FLOAT && second->type == STACK_FLOAT)
        {
            if (atof(first->value.data) == atof(second->value.data))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
            else
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
        }

        // int == float || float == int
        else if ((first->type == STACK_INT && second->type == STACK_FLOAT) ||
                 (first->type == STACK_FLOAT && second->type == STACK_INT))
        {
            if (atof(first->value.data) == atof(second->value.data))
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
            }
            else
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
            }
        }

        //  int != id
        else if (first->type == STACK_INT && second->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), second->value.data);
            printOnly(output(), " int@");
            printOnly(output(), first->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), second->value.data);
            printOnly(output(), " float@");
            printFloat(output(), first->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        //  id != int
        else if (second->type == STACK_INT && first->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " int@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " float@");
            printFloat(output(), second->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        //  float == id
        else if (first->type == STACK_FLOAT && second->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, tmp);
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
            }
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);

            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " float@");
            printFloat(output(), first->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), second->value.data);
            printOnly(output(), " float@");
            printFloat(output(), first->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        //  float == id
        else if (second->type == STACK_FLOAT && first->type == STACK_ID)
        {
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data); //LF@tmp has a type

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // id is int
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, tmp);
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
            }
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);

            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), tmp);
            printOnly(output(), tmp);
            printOnly(output(), " float@");
            printFloat(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // id is float
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), "  LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " float@");
            printFloat(output(), second->value.data); // ! float
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");

            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");

            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }

        else if (first->type == STACK_ID && second->type == STACK_ID)
        {
            // tmp = type(first)
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);

            // tmp2 = type(second)
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, "%2");
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
            }
            printLine(output(), "TYPE LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);

            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil LF@");
            printOnly(output(), tmp);
            printOnly(output(), " string@nil");

            // $INT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // $FLOAT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$int LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$float LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // $STRING
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string$string LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // $NIL
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil");
            // jump if int
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@int");
            // jump if float
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@float");
            // jump if string
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@string");
            // jump if nil
            printLine(output(), "JUMPIFEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil$nil LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%2");
            printOnly(output(), " string@nil");

            // INT != INT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$int");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // FLOAT != FLOAT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$float");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // STRING != STRING
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$string$string");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // nil != nil
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$nil$nil");
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // INT != FLOAT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$int$float");
            // defvar new
            if (IN_WHILE)
            {
                printLine(&whileDefs, "DEFVAR LF@");
                printOnly(&whileDefs, tmp);
                printOnly(&whileDefs, "%3");
            }
            else
            {
                printLine(output(), "DEFVAR LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
            }
            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // FLOAT != INT
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$float$int");

            printLine(output(), "INT2FLOAT LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), second->value.data);
            printLine(output(), "JUMPIFNEQ $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printOnly(output(), " LF@");
            printOnly(output(), tmp);
            printOnly(output(), "%3");
            printOnly(output(), " LF@");
            printOnly(output(), first->value.data);
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@false");
            printLine(output(), "JUMP $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");

            // false and end ..
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$false");
            printLine(output(), "MOVE LF@");
            printOnly(output(), tmp);
            printOnly(output(), " bool@true");
            printLine(output(), "LABEL $$");
            printOnly(output(), tmp);
            printOnly(output(), "$end");
        }
        break;

    /* <     *******************************************************************************/
    case STACK_OP_LT: 
        // nil
        if (second->type == STACK_NIL || first->type == STACK_NIL)
        {
            printLine(output(), "EXIT int@4");
        }

        // strings
        else if (second->type == STACK_STRING || first->type == STACK_STRING)
        {
            if ((second->type == STACK_STRING && first->type != STACK_STRING && first->type != STACK_ID) ||
                (first->type == STACK_STRING && second->type != STACK_STRING && second->type != STACK_ID))
            {
                printLine(output(), "EXIT int@4");
            }
            else if (second->type == STACK_STRING && first->type == STACK_STRING)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@0");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
            else if (first->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@0");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }

            else if (second->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@0");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                int one = atoi( first->value.data );
                int two = atoi( second->value.data );
                
                if (one < two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_FLOAT)
            {
                double one = atof(first->value.data);
                double two = atof(second->value.data);

                if (one < two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT || second->type == STACK_FLOAT)
            {
                int one = atof(first->value.data);
                int two = atof(second->value.data);

                if (one < two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, tmp);
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), tmp);
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else
            {
                GEN_FLAG_STRINGCOMP = 1;
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $STRING
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");

                // $INT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);                
                printOnly(output(), "$end");

                // $INT$FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string");
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@0");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        break;

    /* <=     *******************************************************************************/
    case STACK_OP_LTE:
        // nil
        if (second->type == STACK_NIL || first->type == STACK_NIL)
        {
            printLine(output(), "EXIT int@4");
        }

        // strings
        else if (second->type == STACK_STRING || first->type == STACK_STRING)
        {
            if ((second->type == STACK_STRING && first->type != STACK_STRING && first->type != STACK_ID) ||
                (first->type == STACK_STRING && second->type != STACK_STRING && second->type != STACK_ID))
            {
                printLine(output(), "EXIT int@4");
            }
            else if (second->type == STACK_STRING && first->type == STACK_STRING)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@2");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
            else if (first->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@2");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }

            else if (second->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@2");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                int one = atoi(first->value.data);
                int two = atoi(second->value.data);

                if (one <= two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_FLOAT)
            {
                double one = atof(first->value.data);
                double two = atof(second->value.data);

                if (one <= two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT || second->type == STACK_FLOAT)
            {
                int one = atof(first->value.data);
                int two = atof(second->value.data);

                if (one <= two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, tmp);
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), tmp);
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else if (second->type == STACK_FLOAT)
            {
                GEN_FLAG_STRINGCOMP = 1;
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%4");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%4");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else
            {
                GEN_FLAG_STRINGCOMP = 1;
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $STRING
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");

                // $INT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $INT$FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%4");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%4");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "LT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string");
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@2");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        break;

    /* >     *******************************************************************************/
    case STACK_OP_GT:
        // nil
        if (second->type == STACK_NIL || first->type == STACK_NIL)
        {
            printLine(output(), "EXIT int@4");
        }

        // strings
        else if (second->type == STACK_STRING || first->type == STACK_STRING)
        {
            if ((second->type == STACK_STRING && first->type != STACK_STRING && first->type != STACK_ID) ||
                (first->type == STACK_STRING && second->type != STACK_STRING && second->type != STACK_ID))
            {
                printLine(output(), "EXIT int@4");
            }
            else if (second->type == STACK_STRING && first->type == STACK_STRING)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@1");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
            else if (first->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@1");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }

            else if (second->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@1");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                int one = atoi(first->value.data);
                int two = atoi(second->value.data);

                if (one > two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_FLOAT)
            {
                double one = atof(first->value.data);
                double two = atof(second->value.data);

                if (one > two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT || second->type == STACK_FLOAT)
            {
                int one = atof(first->value.data);
                int two = atof(second->value.data);

                if (one > two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, tmp);
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), tmp);
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else
            {
                GEN_FLAG_STRINGCOMP = 1;
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $STRING
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");

                // $INT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $INT$FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string");
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@1");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        break;

    /* >=       *****************************************************************************/
    case STACK_OP_GTE:
        // nil
        if (second->type == STACK_NIL || first->type == STACK_NIL)
        {
            printLine(output(), "EXIT int@4");
        }

        // strings
        else if (second->type == STACK_STRING || first->type == STACK_STRING)
        {
            if ((second->type == STACK_STRING && first->type != STACK_STRING && first->type != STACK_ID) ||
                (first->type == STACK_STRING && second->type != STACK_STRING && second->type != STACK_ID))
            {
                printLine(output(), "EXIT int@4");
            }
            else if (second->type == STACK_STRING && first->type == STACK_STRING)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@3");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
            else if (first->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 string@");
                printString(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@3");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }

            else if (second->type == STACK_ID)
            {
                GEN_FLAG_STRINGCOMP = 1;
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 string@");
                printString(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@3");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
            }
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                int one = atoi(first->value.data);
                int two = atoi(second->value.data);

                if (one >= two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_FLOAT)
            {
                double one = atof(first->value.data);
                double two = atof(second->value.data);

                if (one >= two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");

                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT || second->type == STACK_FLOAT)
            {
                int one = atof(first->value.data);
                int two = atof(second->value.data);

                if (one >= two)
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@true");
                }
                else
                {
                    printLine(output(), "MOVE LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), " bool@false");
                }
            }

            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, tmp);
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), tmp);
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), tmp);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%4");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%4");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                // if (IN_WHILE)
                // {
                //     printLine(&whileDefs, "DEFVAR LF@");
                //     printOnly(&whileDefs, tmp);
                //     printOnly(&whileDefs, "%3");
                // }
                // else
                // {
                //     printLine(output(), "DEFVAR LF@");
                //     printOnly(output(), tmp);
                //     printOnly(output(), "%3");
                // }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }

            else
            {
                GEN_FLAG_STRINGCOMP = 1;
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $STRING
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");

                // $INT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%3");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%3");
                }
                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $INT$FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%4");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%4");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // $FLOAT$INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");

                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "GT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");

                printLine(output(), "EQ LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%4");
                printLine(output(), "OR LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%3");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@true");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string");
                printLine(output(), "CREATEFRAME");
                printLine(output(), "DEFVAR TF@%0");
                printLine(output(), "DEFVAR TF@%1");
                printLine(output(), "DEFVAR TF@%2");
                printLine(output(), "MOVE TF@%0 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MOVE TF@%1 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MOVE TF@%2 int@3");
                printLine(output(), "CALL $$sstring");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " TF@%retval");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$false");
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " bool@false");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
        }

        break;

    /* +    ************************************************************************************/
    case STACK_OP_ADD:
        //nil
        if (first->type == STACK_NIL || second->type == STACK_NIL)
        {
            printLine(output(), "EXIT int@4");
        }

        // 1. INT
        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                char result[50];
                sprintf(result, "%d", atoi(first->value.data) + atoi(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) + atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) + atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) + atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_STRING)
        {
            if (second->type == STACK_INT || second->type == STACK_FLOAT)
            {
                printLine(output(), "EXIT int@4");
            }
            else if (second->type == STACK_STRING)
            {
                char str[150];
                sprintf(str, "%s%s", first->value.data, second->value.data);
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@");
                printString(output(), str);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                // int, float, nit
                printLine(output(), "EXIT int@4");

                // id is string
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                printLine(output(), "CONCAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@");
                printString(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }

            if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }

            else if (second->type == STACK_STRING)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // jump if float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                printLine(output(), "CONCAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " string@");
                printString(output(), second->value.data);
            }

            else if (second->type == STACK_ID)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // jump if string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $STRING
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string");
                // not string
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@string");
                printLine(output(), "EXIT int@4");

                // jump if float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$string$string");
                printLine(output(), "CONCAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $INT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $INT $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "ADD LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
        }

        break;

    /* -   ***************************************************************************************/
    case STACK_OP_SUB:
        //nil
        if (first->type == STACK_NIL || second->type == STACK_NIL || first->type == STACK_STRING || second->type == STACK_STRING)
        {
            printLine(output(), "EXIT int@4");
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                char result[50];
                sprintf(result, "%d", atoi(first->value.data) - atoi(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) - atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) - atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) - atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }

            else if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
            else
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $INT $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "SUB LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
        }
        break;

    /* *   ***************************************************************************************/
    case STACK_OP_MUL:
        //nil
        if (first->type == STACK_NIL || second->type == STACK_NIL || first->type == STACK_STRING || second->type == STACK_STRING)
        {
            printLine(output(), "EXIT int@4");
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                char result[50];
                sprintf(result, "%d", atoi(first->value.data) * atoi(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) * atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) * atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) * atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }

            else if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
            else
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $INT $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "MUL LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
        }
        break;

    /* /   ***************************************************************************************/
    case STACK_OP_DIV:
        //nil
        if (first->type == STACK_NIL || second->type == STACK_NIL || first->type == STACK_STRING || second->type == STACK_STRING)
        {
            printLine(output(), "EXIT int@4");
        }

        else if ((second->type == STACK_INT && atoi(second->value.data) == 0 ) ||
                (second->type == STACK_FLOAT && atof(second->value.data) == 0.0))
        {
            printLine(output(), "EXIT int@9");
        }

        else if (first->type == STACK_INT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                char result[50];
                sprintf(result, "%d", atoi(first->value.data) / atoi(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) / atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%9");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%9");
                }
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9");
                printLine(output(), "IDIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " int@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9 float@");
                printFloat(output(), "0");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9");
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_FLOAT)
        {
            if (second->type == STACK_INT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) / atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_FLOAT)
            {
                printLine(output(), "MOVE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                char result[50];
                sprintf(result, "%a", atof(first->value.data) / atof(second->value.data));
                printOnly(output(), result);
            }
            else if (second->type == STACK_ID)
            {

                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data); // tmp = type(second)

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                // string, nil
                printLine(output(), "EXIT int@4");

                // id is int
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");

                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");

                // id is float
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " float@0x0p+0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9");
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " float@");
                printFloat(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$end");
            }
            else
            {
                printLine(output(), "EXIT int@4");
            }
        }

        else if (first->type == STACK_ID)
        {
            if (second->type == STACK_INT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%9");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%9");
                }
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9 LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9");
                printLine(output(), "IDIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9 LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@0x0p+0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9");
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }

            else if (second->type == STACK_FLOAT)
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%9");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%9");
                }
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9 LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float ");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " int@0x0p+0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9");
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@");
                printFloat(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
            else
            {
                // tmp = type(first)
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);

                // tmp2 = type(second)
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%2");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%2");
                }
                printLine(output(), "TYPE LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);

                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int");
                if (IN_WHILE)
                {
                    printLine(&whileDefs, "DEFVAR LF@");
                    printOnly(&whileDefs, tmp);
                    printOnly(&whileDefs, "%9");
                }
                else
                {
                    printLine(output(), "DEFVAR LF@");
                    printOnly(output(), tmp);
                    printOnly(output(), "%9");
                }
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9 LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9 LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " float@0x0p+0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$9");
                // jump if int
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@int");
                // jump if float
                printLine(output(), "JUMPIFEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printOnly(output(), " string@float");
                printLine(output(), "EXIT int@4");

                // $INT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$int$9");
                printLine(output(), "IDIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $INT $FLOAT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT float@0x0p+0");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$float$9");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), first->value.data);
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                // $FLOAT $INT
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$float$int");
                printLine(output(), "JUMPIFNEQ $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9 LF@");
                printOnly(output(), second->value.data);
                printOnly(output(), " int@0");
                printLine(output(), "EXIT int@9");
                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
                printOnly(output(), "$int$9");
                printLine(output(), "INT2FLOAT LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2 LF@");
                printOnly(output(), second->value.data);
                printLine(output(), "DIV LF@");
                printOnly(output(), tmp);
                printOnly(output(), " LF@");
                printOnly(output(), first->value.data);
                printOnly(output(), " LF@");
                printOnly(output(), tmp);
                printOnly(output(), "%2");
                printLine(output(), "JUMP $$");
                printOnly(output(), tmp);

                printLine(output(), "LABEL $$");
                printOnly(output(), tmp);
            }
        }
        break;

    default:
        break;
    }
    }

    stackDeleteFirst(&expVals);
    stackDeleteFirst(&expVals);


    stackInsertFirst(&expVals, STACK_ID, tmp);

    printLine(output(), "CREATEFRAME");
    printLine(output(), "PUSHFRAME");
    printLine(output(), "DEFVAR LF@%retval");
    printLine(output(), "POPFRAME");
    printLine(output(), "MOVE TF@%retval LF@");
    printOnly(output(), tmp);

    varCounter++;
    IN_EXP_EVAL = 0;
}