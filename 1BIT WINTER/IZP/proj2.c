/*
 * VUT FIT
 * IZP 2017/2018
 * Projekt 2 - Iteracni vypocty
 * Soubor: proj1.c
 * Autor: Jakub Frejlach, xfrejl00 (1BIT)
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>

#define PI 3.14159265358979323846 //Ludolfovo cislo PI

enum processType {DISTANCE = 1, HEIGHT, TAN}; //vycet, jehoz hodnoty slouzi pro indikovani cinnosti, kterou ma program vykonavat

/**
 * Deklarace funkci
 */
double taylor_tan(double x, unsigned int n);
double cfrac_tan(double x, unsigned int n);
double isArgNumber(char *str, int* failed);
void iterAmount(char *argv[], int *failed);
void countTan(double firstIter, double lastIter, double x);
void measureObject(double height, double x, double angleBeta);
void help();
int iterCheck(char *str, int* failed);
bool checkArg(int argc, char* argv[], double *x, double *firstIter, double *lastIter, double *angleBeta, double *height, int failed, int *measure, int *cmpTan);
bool angleCheck(double *x);
bool measureCheck1(double x, double height);
bool measureCheck2(double x, double height, double angleBeta);

//////////////////////////////////////////////////////////////////////////

/**
 * Hlavni program
 * @height je implicitne nastavena na 1.5
 */

int main(int argc, char *argv[])
{
	int failed = 0, cmpTan = 0, measure = 0;
	double x, angleBeta = 0., firstIter, lastIter, height = 1.5;

	if (!checkArg(argc, argv, &x, &firstIter, &lastIter, &angleBeta, &height, failed, &measure, &cmpTan)) //pri prevodu a kontrole argumentu nasatala chyba
	{
		fprintf(stderr, "ERROR:Chyba v zadani argumentu. Viz. ./proj2 --help\n");
		return EXIT_FAILURE;
	}
	else if (cmpTan == TAN) //cmpTan = TAN indikuje, ze ma byt spocitan tangens
	{
		if(!angleCheck(&x))
			return EXIT_FAILURE;
		countTan(firstIter, lastIter, x);
	}
	else if (measure == DISTANCE) //measure = DISTANCE indikuje, ze ma byt spocitana vzdalenost
	{
		if(!measureCheck1(x, height))
			return EXIT_FAILURE;
		measureObject(height, x, angleBeta);
	}
	else if (measure == HEIGHT) //measure = HEIGHT indikuje, ze ma byt spocitana vzdalenost a k tomu jeste vyska objektu
	{
		if(!measureCheck2(x, height, angleBeta))
			return EXIT_FAILURE;
		measureObject(height, x, angleBeta);
	}
	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

/**
 * Definice funkci
 */

/**
 * funkce provadi vypocet tangens pomocÄÂ­ Taylorova polynomu
 * @x uhel v radianech, ze ktereho se ma pocitat tangens
 * @n pocet iteraci (max. 13)
 * @return vraci hodnotu tangens
 */
double taylor_tan(double x, unsigned int n)
{
	double tanT = 0.;
	double y = x;
	double numerator[] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604}; //jednotlive citatele Taylorova polynomu, jejich vypocet je prilis slozity, proto jsou pevne dane
	double denominator[] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375}; //jednotlive jmenovatele Taylorova polynomu, jejich vypocet je prilis slozity, proto jsou pevne dane
	for (unsigned int i = 0; i < n; i++)
	{
		tanT = tanT + (numerator[i] * y) / denominator[i];
		y = y * x * x;

	}
	return tanT;
}
/**
 * funkce provadi vypocet tangens pomocÄÂ­ zretezenych zlomku
 * @x uhel v radianech, ze ktereho se ma pocitat tangens
 * @n pocet iteraci (max. 13)
 * @return vraci hodnotu tangens
 */
double cfrac_tan(double x, unsigned int n)
{
	double num = 0.;
	double old_num = 0.;
	double tanC = 0.;
	for(unsigned int i = n; i > 0; i--)
	{
			num = 1 / (((2*i - 1) / x) - old_num);
			old_num = num;
	}
	tanC = num;
	return tanC;
}
/**
 * funkce pro prevod argumentu na double a kontrolu, jestli opravdu jde o cislo
 * @str "string", ktery ma byt preveden na double
 * @failed indikator chyby, zvysuje se v pripade, ze prevod probehne neuspesne
 * @return vraci argument prevedeny na double
 */
double isArgNumber(char *str, int* failed)
{
	if(isnan(atof(str)))
	{
		(*failed)++;
		return EXIT_FAILURE;
	}
	char *end; //ukazatel na char, pracuje s funkci strtod
	double num = strtod(str, &end);
	if((int) strlen(str) != (end - str))
		(*failed)++;
	return num;
}
/**
 * funkce osetruje pocty iteraci (maximalne je pripustne 13 iteraci)
 * @failed indikator chyby
 */
void iterAmount(char *argv[], int *failed)
{
	char *end; //ukazatel na char, pracuje s nim funkce strtod
	if (strtod(argv[3], &end) < 1 || strtod(argv[4], &end) > 13 || strtod(argv[3], &end) > strtod(argv[4], &end))
		(*failed)++;
}
/**
 * funkce, ktera vola funkce na vypocet tangensu pomoci jednotlivy metod, vypocet odchylek a vypis vsech hodnot
 * @firstIter urcuje od kolikate iterace ma vypis probihat
 * @lastIter urcuje do kolikate iterace ma vypis probihat
 * @x uhel v radianech, ze ktereho se ma pocitat tangens
 */
void countTan(double firstIter, double lastIter, double x)
{
	for(int n = firstIter; n <= lastIter; n++)
	{
		double taylorOutput = taylor_tan(x, n);
		double cfracOutput = cfrac_tan(x, n);
		double taylorError = fabs(tan(x) - taylorOutput); //vypocet odchylky Taylorova polynomu od funkce tangens z math.h
		double cfracError = fabs(tan(x) - cfracOutput); //vypocet odchylky zretezenych zlomku od funkce tangens z math.h
		printf("%d %e %e %e %e %e\n", n, tan(x), taylorOutput, taylorError, cfracOutput, cfracError);
	}
}
/**
 * funkce, ktera vypocte vzdalenost od mereneho objektu a pripadne i jeho vysku
 * @height vyska, ve ktere je umisten merici pristroj (implicitne je nastavena na 1.5, ale lze ji menit)
 * @x uhel v radianech, pomoci ktereho spocitame vzdalenost pristoje od objektu
 * @angleBeta uhel v radianech, pomoci ktereho spocitame vysku objektu (pouze, pokud je uhel zadany)
 */
void measureObject(double height, double x, double angleBeta)
{
	int n = 9; //pri iteracnim vypoctu tangens pro uhel 1.4 (krajni hodnota) bylo zjisteno, ze staci 10 iteraci
	double objectDistance = height / cfrac_tan(x, n); //vypocet odvozeny ze znalosti funkce tangens v pravouhlem trojuhelniku (tan(uhel) = protilehla strana / prilehla strana)
	if(angleBeta)
	{
		double objectHeight = cfrac_tan(angleBeta, n) * objectDistance + height; //vypocet odvozeny ze znalosti funkce tangens v pravouhlem trojuhelniku (tan(uhel) = protilehla strana / prilehla strana)
		printf("%.10e\n%.10e\n", objectDistance, objectHeight);
	}
	else
		printf("%.10e\n", objectDistance);
}
/**
 * funkce, ktera vytiskne napovedu
 */
void help()
{
 printf("Program se spousti v nasledujici podobe:\n./proj2 --help\nnebo\n./proj2 --tan A N M\nnebo\n./proj2 [-c X] -m A [B]\nArgumenty programu:\n--help zpusobi, ze program vytiskne napovedu pouzivani programu a skonci.\n--tan porovna presnosti vypoctu tangens uhlu A (v radianech) mezi volanim tan z matematicke knihovny, a vypoctu tangens pomoci Taylorova polynomu a zretezeneho zlomku. Argumenty N a M udavaji, ve kterych iteracich iteracniho vypoctu ma porovnani probihat. 0 < N <= M < 14\n-m vypocita a zmeri vzdalenosti.\nUhel Alfa je dan argumentem A v radianech. Program vypocita a vypise vzdalenost mereneho objektu. 0 < A <= 1.4 < PI/2.\nPokud je zadan, uhel Beta; udava argument B v radianech. Program vypocita a vypise i vysku mereneho objektu. 0 < B <= 1.4 < PI/2\nArgument -c nastavuje vysku mericiho pristroje c pro vypocet. Vyska c je dana argumentem X (0 < X <= 100). Argument je volitelny - implicitni vyska je 1.5 metru.\n");
}
/**
 * funkce pro prevod argumentu na int a kontrolu, jestli opravdu jde o cele cislo
 * @str "string", ktery ma byt preveden na double
 * @failed indikator chyby, zvysuje se v pripade, ze prevod probehne neuspesne
 * @return vraci argument prevedeny na int
 */
int iterCheck(char *str, int* failed)
{
	if(isnan(atof(str)))
	{
		(*failed)++;
		return EXIT_FAILURE;
	}
	char *end; //ukazatel na char, pracuje s funkci strtod
	double num = strtol(str, &end, 10);
	if((int) strlen(str) != (end - str))
		(*failed)++;
	return num;
}
/**
 * funkce, ktera rozhoduje podle zadanych argumentu, jakou ma program vykonat cinnost a pomoci dalsich funkci prevadi argumenty na typ double a kontroluje, jestli vyhovuji podminkam zadani
 * @x uhel v radianech, pomoci ktereho spocitame vzdalenost pristoje od objektu nebo od ktereho spocitame tangnes
 * @firstIter urcuje od kolikate iterace ma vypis probihat
 * @lastIter urcuje do kolikate iterace ma vypis probihat
 * @height vyska, ve ktere je umisten merici pristroj (implicitne je nastavena na 1.5, ale lze ji menit)
 * @angleBeta uhel v radianech, pomoci ktereho spocitame vysku objektu (pouze, pokud je uhel zadany)
 * @failed indikator chyby
 * @measure indikuje, jestli ma byt provedeno pocitani vzdalenosti a pripadne vysky objektu
 * @cmpTan indikuje, jestli ma byt proveden vypocet tangens pomoci Taylorova polynomu a zretezenych zlomku
 * @return vraci false, pokud nastala chyba a true pokud vsechno probehlo v poradku
 */
bool checkArg(int argc, char* argv[], double *x, double *firstIter, double *lastIter, double *angleBeta, double *height, int failed, int *measure, int *cmpTan)
{
	if (argc == 2 && strcmp(argv[1], "--help") == 0) //provede vypis napovedy
		help();
	else if (argc == 5 && strcmp(argv[1], "--tan") == 0) //provede vypocet tangens
	{
		*x = isArgNumber (argv[2], &failed);
		*firstIter = iterCheck (argv[3], &failed);
		*lastIter = iterCheck (argv[4], &failed);
		iterAmount (argv, &failed);
		*cmpTan = TAN;
	}
	else if (argc == 3 && strcmp(argv[1], "-m") == 0) //provede vypocet vzdalenosti objektu (vyska pristroje je implicitni)
	{
		*x = isArgNumber (argv[2], &failed);
		*measure = DISTANCE;
	}
	else if (argc == 4 && strcmp(argv[1], "-m") == 0) //provede vypocet vzdalenosti a vysky objektu (vyska pristoje je implicitni)
	{
		*x = isArgNumber (argv[2], &failed);
		*angleBeta = isArgNumber (argv[3], &failed);
		*measure = HEIGHT;
	}
	else if (argc == 5 && strcmp(argv[1], "-c") == 0 && strcmp(argv[3], "-m") == 0) //provede vypocet vzdalenosti objektu
	{
		*height = isArgNumber (argv[2], &failed);
		*x = isArgNumber (argv[4], &failed);
		*measure = DISTANCE;
	}
	else if (argc == 6 && strcmp(argv[1], "-c") == 0 && strcmp(argv[3], "-m") == 0) //provede vypocet vzdalenosti a vysky objektu
	{
		*height = isArgNumber (argv[2], &failed);
		*x = isArgNumber (argv[4], &failed);
		*angleBeta = isArgNumber (argv[5], &failed);
		*measure = HEIGHT;
	}
	else
		return false;
	if (failed > 0)
		return false;
	return true;
}
/**
 * funkce, ktera zkontroluje, jestli zadany uhel vyhovuje a pripadne ho prevede do intervalu (-PI/2 ; PI/2)
 * @x uhel v radianech, ze ktereho se ma pocitat tangens
 * @return vraci false, pokud nastala chyba a true pokud vsechno probehlo v poradku
 */
bool angleCheck(double *x)
{
	if(isnan(*x))
	{
		fprintf(stderr, "ERROR:Chyba v zadani uhlu alfa. Viz. ./proj2 --help\n");
		return false;
	}
	else if(*x == PI / 2 || *x == PI / -2)
	{
		fprintf(stderr, "ERROR:Chyba v zadani uhlu alfa. Viz. ./proj2 --help\n");
		return false;
	}
	while(*x > PI / 2)
		*x = *x - PI;
	while(*x < PI / -2)
		*x = *x + PI;
	return true;
}
/**
 * funkce, ktera zjisti, jestli zadane hodnoty pro mereni vyhovuji podminkam (uhel Beta nenÄÂ­ zadÄÄn)
 * @x uhel v radianech, pomoci ktereho spocitame vzdalenost pristoje od objektu
 * @height vyska, ve ktere je umisten merici pristroj (implicitne je nastavena na 1.5, ale lze ji menit)
 * @return vraci false, pokud nastala chyba a true pokud vsechno probehlo v poradku
 */
bool measureCheck1(double x, double height)
{
	if (x <= 0 || x > 1.4 || height <= 0 || height > 100)
	{
		fprintf(stderr, "ERROR:Chyba v zadanych hodnotach. Viz. ./proj2 --help\n");
		return false;
	}
	return true;
}
/**
 * funkce, ktera zjisti, jestli zadane hodnoty pro mereni vyhovuji podminkam
 * @x uhel v radianech, pomoci ktereho spocitame vzdalenost pristoje od objektu
 * @height vyska, ve ktere je umisten merici pristroj (implicitne je nastavena na 1.5, ale lze ji menit)
 * @angleBeta uhel v radianech, pomoci ktereho spocitame vysku objektu (pouze, pokud je uhel zadany)
 * @return vraci false, pokud nastala chyba a true pokud vsechno probehlo v poradku
 */
bool measureCheck2(double x, double height, double angleBeta)
{
	if (x <= 0 || x > 1.4 || angleBeta <= 0 || angleBeta > 1.4 || height <= 0 || height > 100 )
	{
		fprintf(stderr, "ERROR:Chyba v zadanych hodnotach. Viz. ./proj2 --help\n");
		return false;
	}
	return true;
}
