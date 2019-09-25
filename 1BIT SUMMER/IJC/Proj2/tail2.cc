/*
 *  Soubor: tail2.cc
 *  Reseni IJC-DU2, priklad 2b), 18.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

//TODO - struktura a komentare
#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<fstream>

using namespace std;


/*
 * Struktura nesouci data ze zpracovanych argumentu
 */
typedef struct
{
  long lines; // Pocet radku, ktery ma byt vypsat
  char print_case; // Udava, jestli ma byt cteno ze souboru nebo z stdin
  string filename; // Jmeno souboru, ze ktereho ma byt cteno
}params_t;


/*
 * Hodnoty pro print_case
 */
enum {
  from_file, // Cteni ze souboru
  from_cin, // Cteni z stdin
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
      data.print_case = from_cin;
      break;

    case 2: // Tisk ze souboru
      data.print_case = from_file;
      data.filename = arg[1];
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
        data.print_case = from_cin;
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
        data.filename = arg[3];
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
        data.filename = arg[1];
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


int main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);

  params_t data = get_params(argc, argv); // Zpracovani argumentu

  if(data.print_case == error) // Chyba v zadanych argumentech -> konec programu
  {
    cout << "ERROR: Wrong params." << endl;
    return EXIT_FAILURE;
  }

  string line;
  queue<string> buffer; // Kontejner

  if(data.print_case == from_cin) // Nacitani z cin
  {
    while(getline(cin, line))
    {
      buffer.push (line);
      if(buffer.size() > (unsigned)data.lines) // Pri nacteni vice radku, nez je zadano -> prebytecny radek odstranen
        buffer.pop();
      if(!cin)
        break;
    }
  }
  else if(data.print_case == from_file) // Nacitani ze souboru
  {
    ifstream fp (data.filename);
    if(!fp.is_open()) // Kontrola otevreni souboru
    {
      cout << "ERROR: File cannot be open." << endl;
      return EXIT_FAILURE;
    }

    while(getline(fp, line))
    {
      buffer.push (line);
      if(buffer.size() > (unsigned)data.lines) // Pri nacteni vice radku, nez je zadano -> prebytecny radek odstranen
        buffer.pop();

      if(!fp) // Pokud stream skoncil, je nutno ho zavrit
      {
        fp.close();
        break;
      }
    }
  }

  while(buffer.size() != 0) // Vypsani pozadovanych radku
  {
    cout << buffer.front() << endl;
    buffer.pop();
  }
  return EXIT_SUCCESS;
}
