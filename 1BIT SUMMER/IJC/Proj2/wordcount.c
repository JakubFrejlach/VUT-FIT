/*
 *  Soubor: wordcount.c
 *  Reseni IJC-DU2, priklad 2), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"io.h"
#include"htab.h"

#define MAX_WORD_LENGTH 128 // Maximalni delka slova
#define HTAB_SIZE 12289 // Vhodna velikost hash tabulky zvolena podle -> http://planetmath.org/goodhashtableprimes

/*
 * Vytiskne zadane slovo a bezznamenkove cislo
 *
 * @param key          slovo pro tisk
 * @param data         pocet vyskytu slova
 */
void print(const char *key, unsigned data)
{
  printf("%s\t%u\n", key, data);
}

int main()
{
  htab_t *table = htab_init(HTAB_SIZE); // Inicializace hash tabulky
  if(table == NULL)
  {
    fprintf(stderr, "ERROR: Hash table init failed.\n");
    return EXIT_FAILURE;
  }

  char word[128]; // Docasne ukladani slova
  htab_listitem *item; // Item v hash tabulce

  while(get_word(word, MAX_WORD_LENGTH, stdin) != EOF) // Nacitani slov z stdin
  {
    item = htab_lookup_add(table, word); // Nalezeni/vytvoreni zaznamu v tabulce
    if(item == NULL) // Kontrola selhani alkocace pameti
    {
      htab_free(table);
      fprintf(stderr, "ERROR: Allocating memory failed.\n");
      return EXIT_FAILURE;
    }
    item->data++;
  }

  #ifdef MOVE // Test funkce htab_move

  htab_t *table2 = htab_move(HTAB_SIZE*2, table);
  if(table2 == NULL)
  {
    htab_free(table);
    fprintf(stderr, "ERROR: Hash table init failed.\n");
    return EXIT_FAILURE;
  }
  htab_foreach(table2, &print);
  htab_free(table2);

  #else

  htab_foreach(table, &print); // Pro vsechny itemy v hash tabulce vola funkci "print"
  
  #endif

  htab_free(table); // Zruseni tabulky

  return EXIT_SUCCESS;
}
