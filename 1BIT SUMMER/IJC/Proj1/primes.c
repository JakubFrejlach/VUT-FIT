/*
 *  Soubor: primes.c
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include<stdio.h>
#include"error.c"
#include"eratosthenes.c"

int main()
{
  bit_array_create(primes, 222000000);

  eratosthenes(primes);

  int i = 0;
  int index = bit_array_size(primes);

  /*
   * Zjisteni az poslednich 10 prvocisel
   */
  while(i < 10 && index > 1)
  {
    if(bit_array_getbit(primes, index) == 0)
    {
      i++;
      index--;
    }
    else
      index--;
  }

  /*
   * Vzestupne vypsani az poslednich 10 prvocisel
   */
  while((unsigned)index <= bit_array_size(primes))
  {
    if(bit_array_getbit(primes, index) == 0)
    {
      printf("%d\n", index);
      index++;
    }
    else
      index++;
  }
}
