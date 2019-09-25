/*
 *  Soubor: eratosthenes.c
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */
#include<stdio.h>
#include<math.h>
#include<limits.h>
#include"bit_array.h"

void eratosthenes(bit_array_t array)
{
  int array_size = bit_array_size(array);

  /*
   * Nulovani indexu 1 -> neni prvocislo
   */
  if(array_size >= 1)
  {
    bit_array_setbit(array, 1, 1);
  }

  int array_size_sqrt = sqrt(array_size);
  int index = 2;

  /*
   * Cyklus pro oznacovani neprvocisel
   * ZLepseni efektivity -> neprochazime znova sude indexy
   */
  while(index <= array_size_sqrt)
  {
    if(bit_array_getbit(array, index) == 0)
    {
      if(index == 2)
      {
        for(int i = index * 2; i <= array_size; i += index)
          bit_array_setbit(array, i, 1);
        index++;
      }
      else
      {
        for(int i = index*3 ; i <= array_size; i += index + index)
          bit_array_setbit(array, i, 1);
        index += 2;
      }
    }
    else
      index += 2;
  }


}
