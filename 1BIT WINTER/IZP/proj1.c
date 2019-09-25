/*
 * VUT FIT
 * IZP 2017/2018
 * Projekt 1 - Prace s textem
 * Soubor: proj1.c
 * Autor: Jakub Frejlach, xfrejl00 (1BIT)
*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define ASCII_SIZE 128 //pocet ASCII znaku
#define MAX_SIZE 101 //maximalni velikost pole
int search(int c, char *str, int counter, int *found, char *e, int *enabled, int *e_found)
{
while((c = toupper(getchar())) != EOF) //nacitani s case insensitive
	{
		if((c < 32 || c > 126) && (c != '\n' && c != '\0')) //kontrola povolenych znaku v externim souboru
		{
			fprintf(stderr, "ERROR: V externim souboru jsou adresy obsahujici nepovolene znaky. Povolene jsou pouze ASCII 		tisknutelne znaky. (32 az 126)\n");
			return EXIT_FAILURE;
		}
		if(str[counter]	== '\0') //parametr konci
		{
			if(c == '\n') //perametr konci a adresa je na konci radku
			{
				if(counter == 0) //counter je 0 => nenalezena shoda
					continue;
				(*found)++;
				counter = 0;
			}
			else if(counter) //bylo nalezeno prvni Enable, u ktereho je nutno ulozit celou adresu (v pripade, ze bude jedine, tak vypise Found)
			{
				e[counter++] = c;
			 	enabled[c]++;
				(*e_found)++;

				while((c = toupper(getchar())) != EOF && c != '\n' && counter < MAX_SIZE - 1) //donacteni adresy po nalezeni Enable (cela adresa se ulozit)
					e[counter++] = c;
				counter = 0;
			}
			else //bylo nalezeno Enable, adresa se donacte az do konce radku
			{
				enabled[c]++;
				while((c = getchar()) != EOF && c != '\n');
				counter = 0;
			}
		}
		else //parametr pokracuje
		{
			if(c == '\n') //adresa je na konci radku a parametr pokracuje => Enable nenalezeno
				counter = 0;
			else //char adresy a parametru se shoduji, zvysi se counter a adresa se cela postupne nacita kvuli prvnimu Enable
			{
				if(c == str[counter])
				{
					e[counter] = c;
					counter++;
					continue;
				}
				while((c = getchar()) != EOF && c != '\n');
				counter = 0;
			}
		}

	}
	return EXIT_SUCCESS;
}
void output(int *found, char *e, int counter, int *enabled, int was_enabled, char *str, int *e_found)
{
	if(*e_found == 1 && !*found) //bylo nalezeno pouze jedno Enable a nebylo nalezena zadna prima shoda
    	{
		printf("Found: %s\n", e);
	}
	else //vypisovani Enable znaku pomoci ASCII tabulky
	{
		for(counter = 0; counter < ASCII_SIZE; counter++)
		{

			if(enabled[counter])
			{
				if(!was_enabled++)
					printf("Enable: ");
				putchar(counter);
			}
		}
	}
	if(was_enabled) //vypisani konce radku v pripade, ze existuje alespon jedno Enable
		putchar('\n');
	if(*found) //vypsani Found v pripade, ze byla nalazena presna shoda, nebo byla nalezena presna shoda a zaroven Enable
		printf("Found: %s\n", str);
	else if(!was_enabled && *e_found != 1) //Nebylo nalezeno nic
		puts("Not found");
}
int main(int argc, char *argv[])
{
	char* str = ""; //pole charu, do ktereho se pripadne ulozi parametr

	if(argc > 2)  //zjistuje, jestli byl zadan parametr nebo jestli nebylo zadano vice nez jeden parametr
	{
		 	fprintf(stderr, "Je povoleno zadavat maximalne jeden parametr.\n");
			return EXIT_FAILURE;
	}
	if(argc > 1)
		str = argv[1];

	for(int i = 0; str[i] != '\0'; i++) //case insensitive v parametru a osetreni povolenych znaku v parametru
	{
		str[i] = toupper(str[i]);
		if(str[i] < 32 || str[i] > 126)
		{
			fprintf(stderr, "ERROR: Argument obsahuje nepovolene znaky. Povolene jsou pouze ASCII tisknutelne znaky. (32 az 126)\n");
			return EXIT_FAILURE;
		}
	}

	int enabled[ASCII_SIZE]  = {0}; //pole pro identifikaci Enable hodnot
	int c = 0; //promenna pro getchar
	int counter = 0; //promenna pro pole "str" a "e"
	int found = 0; //promenna, ktera udava, jestli byla nalezena prima shoda
	int e_found = 0; //promenna, ktera udava, kolik enable znaku bylo nalazeno
	char e[MAX_SIZE] = ""; //pole, do ktereho se po prvnim enable znaku ulozi cela aktualni adresa

	//cast programu pro nacitani znaku
	search(c, str, counter, &found, e, enabled, &e_found);

	//cast programu pro vypis vysledku
	int was_enabled = 0;
	output (&found, e, counter, enabled, was_enabled, str, &e_found);
	return EXIT_SUCCESS;
}
