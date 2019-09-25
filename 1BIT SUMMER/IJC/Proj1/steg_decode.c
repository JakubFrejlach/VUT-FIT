/*
 *  Soubor: steg_decode.c
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */
 #include<stdio.h>
 #include<stdlib.h>
#include<ctype.h>
#include<limits.h>
#include"error.c"
#include"ppm.c"
#include"eratosthenes.c"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    error_exit("Program je nutne spustit ve formatu ./steg_decode filename\n");
  }

  /*
   * Nacteni obrazku do datove struktury
   */
  struct ppm *p = ppm_read(argv[1]);
  if(p == NULL)
  {
    error_exit("Funkce pro cteni ze souboru selhala.\n");
  }

  /*
   * Zjisteni prvocislenych indexu, na kterych je ulozena "tajna" zprava
   */
  bit_array_create(decode, 3000000);
  eratosthenes(decode);

  char msg = 0;
  int print = 0;
  int end_found = 0;

  /*
   * Rozlusteni "tajne" zpravy -> zprava musi byt korektne zakoncena znakem '\n'
   */
  for(unsigned i = 11; i < p->xsize * p->ysize * 3; i++)
  {
    if(bit_array_getbit(decode, i) == 0)
    {
      msg += ((p->data[i] & 1) << print);
      print++;

      if(print == sizeof(char) * CHAR_BIT)
      {
        if(msg == '\0')
        {
          printf("\n");
          end_found++;
          break;
        }
        else if(isprint(msg))
        {
          printf("%c", msg);
          msg = 0;
          print = 0;
        }
        else
        {
          msg = 0;
          print = 0;
        }
      }
    }
  }
  if(!end_found)
  {
    free(p);
    error_exit("Zprava nebyla korektne ukoncena\n");
  }
  free(p);
  return 0;
}
