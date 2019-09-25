/*
 *  Soubor: io.c
 *  Reseni IJC-DU2, priklad b), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include"io.h"

/*
 * Funkce cte jedno slovo ze souboru do zadaneho pole znaku
 *
 * @param s         pole znaku pro uchovani nacteneho slova
 * @param max       maximalni delka slova
 * @param f         soubor ke cteni
 * @return          delka nacteneho slova
 */
int get_word(char *s, int max, FILE *f)
{
  int end = 0;
  int len = 0;
  char c;

  if(f == NULL)
    return len;

  while((c = fgetc(f)) != EOF && isspace(c)) // Preskoceni prazdnych znaku
    continue;

  while(c != EOF && !isspace(c))
  {
    if(len < max -1) // Pokud nebyla prekrocena maximalni delka slova, ulozime znak
    {
      s[len++] = c;
      end++;
    }
    else
      len++;

    c = fgetc(f); // Nacteni dalsiho znaku
  }

  if(c == EOF && !len) // Prazdny soubor
    return EOF;
  else // Za konec nacteneho slova vlozime '\0'
    s[end] = '\0';

  return len;
}
