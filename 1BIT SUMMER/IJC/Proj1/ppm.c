/*
 *  Soubor: ppm.c
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */
#include<stdio.h>
#include<stdlib.h>
#include"ppm.h"

struct ppm * ppm_read(const char * filename)
{
  FILE *fp;
  unsigned int x_size, y_size;

  /*
   * Velikostni limit obrazku z duvodu inicializace bitoveho pole
   */
  unsigned int size_limit = 3000000;

  fp = fopen(filename, "rb");
  if(!fp)
  {
    warning_msg("Soubor %s nelze otevrit.\n", filename);
    return NULL;
  }
  else
  {
   if(fscanf(fp, "P6\n%u %u\n255\n", &x_size, &y_size) != 2)
   {
     warning_msg("Soubor %s neodpovida pozadovanemu formatu\n", filename);
     fclose(fp);
     return NULL;
   }
   if(x_size * y_size * 3 > size_limit)
   {
     warning_msg("Velikost souboru %s je nad povoleny limit %u\n", filename, size_limit);
     fclose(fp);
     return NULL;
   }

   /*
    * Alokace pameti pro datovou strukturu ppm
    */
   struct ppm* img = malloc(sizeof(struct ppm) + sizeof(char) * x_size * y_size * 3);

   if(!img)
   {
     warning_msg("Nelze alokovat pamet");
     fclose(fp);
   }

   img->xsize = x_size;
   img->ysize = y_size;

   /*
    * Cteni z souboru .ppm pomoci funkce fgetc
    */
   for(unsigned int i = 0; i < (sizeof(char) * x_size * y_size * 3); i++)
   {
     img->data[i] = fgetc(fp);
     if(feof(fp))
     {
       warning_msg("Soubor %s neodpovida222 pozadovanemu format\n", filename);
       fclose(fp);
       free(img);
       return NULL;
     }
   }

   getc(fp);
   if(!feof(fp) || ferror(fp))
   {
     warning_msg("Soubor %s neodpovida pozadovanemu formatu\n", filename);
     fclose(fp);
     free(img);
     return NULL;
   }

   fclose(fp);
   return img;
 }
}
int ppm_write(struct ppm *p, const char * filename)
{
  FILE *fp;

  fp = fopen(filename, "wb");
  if(!fp)
  {
    warning_msg("Soubor %s nelze otevrit.\n", filename);
    return -1;
  }
  /*
   * Zapis funkci fprintf do noveho souboru -> napred udaje podle .ppm konvence
   * nasledovne jednotlive chary
   */
  if(fprintf(fp, "P6\n%u %u\n255\n", p->xsize, p->ysize) < 0)
  {
    warning_msg("Do souboru %s nelze zapsat data.\n", filename);
    fclose(fp);
    return -1;
  }
  for(unsigned int i = 0; i < (sizeof(char) * p->xsize * p->ysize * 3); i++)
  {
    if(fprintf(fp, "%c", p->data[i]) < 0)
    {
      warning_msg("Do souboru %s nelze zapsat data.\n", filename);
      fclose(fp);
      return -1;
    }
  }
  free(p);
  fclose(fp);
  return 0;
}
