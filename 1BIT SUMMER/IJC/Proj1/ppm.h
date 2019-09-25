/*
 *  Soubor: ppm.h
 *  Reseni IJC-DU1, priklad a), 11.3.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

struct ppm {
  unsigned xsize;
  unsigned ysize;
  char data[];
};

struct ppm * ppm_read(const char * filename);
int ppm_write(struct ppm *p, const char * filename);
