/*
 *  Soubor: htab.h
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#ifndef HTAB_H
#define HTAB_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct htab_listitem
{
  char *key;
  unsigned data;
  struct htab_listitem *next;
}htab_listitem;

typedef struct htab_t htab_t;

/*
 * Vytvori a inicializuje hash tabulku
 *
 * @param size        velikost tabulky
 * @return            ukazatel na vytvorenou tabulku (NULL v pripade neuspechu alokace)
 */
htab_t *htab_init(int size);

/*
 * Rozptylovaci funkce pro retezce
 *
 * @param str         klic pro vygenerovani indexu
 * @param htab_size   velikost flexible array tabulky
 * @return            vraci index ve flexible array
 */
unsigned htab_hash_function(const char *str);

/*
 * @param t       ukazatel na tabulku
 * @return        vraci pocet itemu tabulky
 */
unsigned htab_size(htab_t *t);

/*
 * @param t       ukazatel na tabulku
 * @return        vraci delku flexible array
 */
unsigned htab_bucket_count(htab_t *t);

/*
 * Funkce hleda/vytvari zaznam o polozce v tabulce
 *
 * @param t       ukazatel na tabulku
 * @param key     polozka k nalezeni/pridani
 * @return        vraci ukazatel na zaznam o polozce
 */
htab_listitem *htab_lookup_add(htab_t *table, const char *key);

/*
 * Funkce, ktera hleda zaznam o polozce v seznamu
 *
 * @param t       ukazatel na tabulku
 * @param key     polozka k nalezeni
 * @return        vraci ukazatel na zaznam o polozce
 */
htab_listitem *htab_find(htab_t *t, const char *key);

/*
 * Funkce najde a odstrani zaznam o polozce ze seznamu
 *
 * @param t       ukazatel na tabulku
 * @param key     polozka k odebrani
 * @return        vraci false, pokud polozka nebyla nalezena
 */
bool htab_remove(htab_t *t, const char *key);

/*
 * Vyprazdni tabulku -> zrusi vsechny polozky tabulky
 *
 * @param t       ukazatel na tabulku
 */
void htab_clear(htab_t *t);

/*
 * Zrusi tabulku
 *
 * @param t       ukazatel na tabulku
 */
void htab_free(htab_t *t);

/*
 * Vola zadanou funkci pro kazdy prvek tabulky
 *
 * @param t       ukazatel na tabulku
 * @param fnc     ukazatel na funkci
 */
void htab_foreach(htab_t *t, void(*fnc)(const char *key, unsigned data));

/*
 * Vytvori novou tabulku s daty puvodni tabulky -> stara tabulka zustane prazdna a alokovana
 *
 * @param newsize   velikost nove tabulky
 * @param t2        ukazatel na puvodni tabulku
 * @return          vraci ukazatel na vytvorenou tabulku
 */
htab_t *htab_move(int newsize, htab_t *t2);

#endif
