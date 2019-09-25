#!/bin/bash

RED='\e[31m'
GREEN='\033[0;32m'
RESET='\033[0m'

c=1

echo -e "\n----   Basic tests   ----"

echo -e "\nTEST0$c: Empty file \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Basic expressions without assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expressions without assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Basic expressions with assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expressions with assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expressions with variables \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Assignment to constant \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

echo -e "\n----   if/else statement tests   ----"

c=$((c+1))
echo -e "\nTEST0$c: Basic if/else \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: if/else with missing expression \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: if/else with missing \"then\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Empty if/else \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: if/else with missing \"else\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: if/else with missing \"end\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Multiple if/else nested \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: if/else with additional \"then\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using semicolon after \"then\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 1 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: if/else with additional \"else\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Multiple if/else and while nested \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

echo -e "\n----   while statement tests   ----"

c=$((c+1))
echo -e "\nTEST0$c: Basic while \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: while with missing expression \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: while with missing \"do\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Empty while \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: while with missing \"end\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Multiple while nested \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: while with additional \"do\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using semicolon after \"do\" \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 1 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Multiple while and if/else nested \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

echo -e "\n----   Function tests   ----"

c=$((c+1))
echo -e "\nTEST0$c: Function definition without parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with missing ID \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with missing brackets \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Empty function definition \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call with parameters without brackets \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call without parameters without brackets \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call with parameters with brackets \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call without parameters with brackets \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call with assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with if/else and while statement \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition in scope \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

#TODO maybe ERROR 3
c=$((c+1))
echo -e "TEST0$c: Assignment to function call \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Calling undefined funtion \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function redefinition \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Calling function in function definition before it is defined \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Calling function with wrong number of parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 5 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with parameters without comas \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with recursive call of itself \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition in function definition \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call with all data types as parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Builtin functions calls \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Builtin functions calls with assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Calling undefined function in function definition \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Calling function before it is defined but with wrong number of parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 5 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Calling function before it is defined but with wrong number of parameters using function ID \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 5 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using function ID in expressions \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using function ID in expressions in function definition \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using function as parametr in another function \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with constant as parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with long ID \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using already defined function as variable \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

echo -e "\n----   Variable tests   ----"

c=$((c+1))
echo -e "\nTEST0$c: Undefined variable without assignment \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using undefined variable in expression \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function call with undefined variables as parameters \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Function definition with ID of already existing variable \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Defining variable with same ID as itself \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using undefined local variable with same ID as itself, but global variable with same ID is already defined \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Long file with only variable assignments \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using function ID as variable \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using undefined local variable, same global variable is already defined \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 3 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

echo -e "\n----   Expressions tests   ----"

c=$((c+1))
echo -e "\nTEST0$c: Long expression with all types of classic operators \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Long expression with all types of classic operators and only with variables \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expressions with multiple types \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expression with many brackets \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expression with compare operators \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expression with multiple compare operators \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 4 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Second expression with multiple compare operators \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 4 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expression with missing operand between operators \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expression with missing operator between operands \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expression with assignment inside \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Using expressions in function call \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 2 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi

c=$((c+1))
echo -e "TEST0$c: Expressions with both variables and constants \c"
./compiler <tests/parser-tests/test$c &>/dev/null
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET}"
else
    echo -e "${RED}[ERROR]${RESET}"
fi
