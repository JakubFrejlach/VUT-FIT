/*
 *  Soubor: tail.c
 *  Reseni IJC-DU2, priklad 1a), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

//TODO - .h souboru + doxygen?

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>

/*
 * Makra pro program tail
 */
#define MAX_LENGTH 1024 // Maximalni delka radku
#define MAX_FILENAME 255 // Maximalni delka nazvu souboru (dle UNIX)


/*
 * Struktura nesouci data ze zpracovanych argumentu
 */
typedef struct
{
  long lines; // Pocet radku, ktery ma byt vypsat
  char print_case; // Udava, jestli ma byt cteno ze souboru nebo z stdin
  char filename[MAX_FILENAME]; // Jmeno souboru, ze ktereho ma byt cteno
}params_t;


/*
 * Hodnoty pro print_case
 */
enum {
  from_file, // Cteni ze souboru
  from_stdin, // Cteni z stdin
  error // Chyba v zadanych argumentech
};


/*
 * Funkce pro zpracovani argumentu souboru.
 *
 * @param arg_count     pocet argumentu
 * @param arg           zadane argumenty
 * @return              vraci strukturu nesouci data ze zpracovanych argumentu
 */
params_t get_params(int arg_count, char **arg)
{
  params_t data; // Struktura nesouci data ze zpracovanych souboru (pocet radku, zdroj tisku, nazev souboru)
  data.lines = 10; // Implicitni pocet radku pro tisk

  switch (arg_count)
  {
    case 1: // Tisk z stdin
      data.print_case = from_stdin;
      break;

    case 2: // Tisk ze souboru
      data.print_case = from_file;
      strcpy(data.filename,arg[1]);
      break;

    case 3: // Tisk z stdin se zadanym poctem radku
      if(!strcmp(arg[1],"-n"))
      {
        char *end;
        data.lines = strtol(arg[2], &end, 10);
        if(*end != '\0' || data.lines < 0 || errno == ERANGE) // Kontrola jestli byl zadan validni pocet radku
        {
          data.print_case = error;
          break;
        }
        data.print_case = from_stdin;
      }
      else
        data.print_case = error;
      break;

    case 4: // Tisk ze souboru se zadanym poctem radku
      if(!strcmp(arg[1],"-n")) // Format ./tail -n cislo soubor
      {
        char *end;
        data.lines = strtol(arg[2], &end, 10);
        if(*end != '\0' || data.lines < 0 || errno == ERANGE) // Kontrola jestli byl zadan validni pocet radku
        {
          data.print_case = error;
          break;
        }
        data.print_case = from_file;
        strcpy(data.filename,arg[3]);
      }
      else if(!strcmp(arg[2],"-n")) // Format ./tail soubor -n cislo
      {
        char *end;
        data.lines = strtol(arg[3], &end, 10);
        if(*end != '\0' || data.lines < 0 || errno == ERANGE) // Kontrola jestli byl zadan validni pocet radku
        {
          data.print_case = error;
          break;
        }
        data.print_case = from_file;
        strcpy(data.filename,arg[1]);
      }
      else
        data.print_case = error;
      break;

    default: // Neplatny pocet argumentu
      data.print_case = error;
      break;
  }
  return data;
}


/*
 * Funkce, ktera na stdout vytiskne jeden radek z kruhoveho bufferu
 *
 * @param buffer        kruhovy buffer s nactenymi radky
 * @param index         index v kruhovem bufferu
 */
void print_line(char buffer[][MAX_LENGTH], int index)
{
  int length = strlen(buffer[index]);

  if(buffer[index][length-1] == '\n') // Kontrola, jestli se ma na konec radku vlozit '\n'
    printf("%s", buffer[index]);
  else
    printf("%s\n", buffer[index]);
}


/*
 *  Funkce, ktera vytiskne vsechny radky nactene v kruhovem bufferu
 *
 * @param buffer_exceed       indikuje, jestli kruhovy buffer alespon jednou dosel az na posledni index
 * @param buffer              kruhovy buffer s nactenymi radky
 * @param lines               udava, v jakem poradi se maji radky v kruhovem bufferu tisknout
 * @param data                struktura nesouci data ze zpracovanych argumentu
 */
void print(bool buffer_exceed, char buffer[][MAX_LENGTH], int line, params_t data)
{
  if(!buffer_exceed) // Buffer neprekrocil ani jednou svuj konec -> tiskne se od indexu "0"
  {
    for(int i = 0; i < line; i++)
      print_line(buffer, i);
  }
  else // Buffer prekrocil alespon jednou svuj konec -> tiskne se od indexu "line"
  {
    for(int i = line; i < data.lines; i++)
      print_line(buffer, i);
    for(int i = 0; i < line; i++)
      print_line(buffer, i);
  }
}


/*
 *  Funkce pro nacteni zadaneho poctu radku do kruhoveho bufferu
 *
 * @param buffer        kruhovy buffer, do ktereho budou nacteny radky
 * @param line          index posledne nacteneho radku
 * @param data          struktura nesouci data ze zpracovanych argumentu
 * @param fp            zdroj pro nacitani radku
 * @return              vraci true <-> buffer prekrocil alespon jednou svuj konec
 */
bool read(char buffer[][MAX_LENGTH], long *line, params_t data, FILE *fp)
{
  bool buffer_exceed = false; // Indikator prakroceni konce bufferu
  bool length_exceed = false; // Pri delsim radku nez MAX_LENGTH urcuje vypis warning_msg
  int len = 0;
  char c;

  while(fgets(buffer[*line], MAX_LENGTH, fp))
  {
    len = strlen(buffer[*line]);
    if(buffer[*line][len-1] != '\n') // Kontrola delky radku
    {
      if(!length_exceed) // Vypis warning_msg pri prvnim delsim radku nez MAX_LENGTH
      {
        fprintf(stderr, "ERROR: Max line length %d has been exceeded, cutting.\n", MAX_LENGTH);
        length_exceed = true;
      }

      c = getc(fp);
      while(c != '\n' && c != EOF) // Preskoceni zbytku radku
        c = getc(fp);
    }

    (*line)++;

    if((*line) == data.lines) // Dosahnut konec kruhoveho bufferu
    {
      *line = 0;
      buffer_exceed = true;
    }
  }
  len = strlen(buffer[(*line)-1]);
  if(buffer[(*line)-1][len] != '\n')
    buffer[(*line)-1][len] = '\n';
  return buffer_exceed;
}

int main(int argc, char *argv[])
{

  params_t data = get_params(argc, argv); // Zpracovani argumentu

  if(data.print_case == error) // Chyba v zadanych argumentech -> konec programu
  {
    fprintf(stderr, "ERROR: Wrong params.\n");
    return EXIT_FAILURE;
  }

  if(data.lines == 0) // Pocet radku pro nacteni je "0" -> zadny vypis
    return EXIT_SUCCESS;

  char buffer[data.lines][MAX_LENGTH]; // Kruhovy buffer
  memset(buffer, 0, data.lines*MAX_LENGTH*sizeof(char)); // Vynulovani kruhoveho bufferu

  FILE *fp;

  long line = 0;
  bool buffer_exceed;

  switch(data.print_case)
  {
    case from_stdin: // Cteni z stdin
      fp = stdin;
      buffer_exceed = read(buffer, &line, data, fp);
      break;

    case from_file: // Cteni ze souboru
      fp = fopen(data.filename, "r"); // Otevreni souboru pro cteni
      if(!fp) // Kontrola otevreni souboru
      {
        fprintf(stderr, "ERROR: File \"%s\" cannot be opened.\n", data.filename);
        return EXIT_FAILURE;
      }

      buffer_exceed = read(buffer, &line, data, fp);

      if(fclose(fp)) // Kontrola zavreni souboru
      {
        fprintf(stderr, "ERROR: Closing file \"%s\" failed.\n", data.filename);
        return EXIT_FAILURE;
      }
    }

  print(buffer_exceed, buffer, line, data); // Vypsani pozadovanych radku

  return EXIT_SUCCESS;
  }
