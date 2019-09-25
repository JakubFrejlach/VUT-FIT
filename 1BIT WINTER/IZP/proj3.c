/**
 * Kostra programu pro 3. projekt IZP 2017/18
 *
 * Jednoducha shlukova analyza
 * Unweighted pair-group average
 * https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX
#include <string.h>
#include <errno.h>

int premium_case = 1; //globalni promenna, ktera definuje, ktera z metod shlukove analyzy ma byt provedena

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};
/*********************** DEKLARACE FUNKCI ***********************/
/**
 * MOJE FUNKCE
 */
void free_memory(struct cluster_t **arr, int size);
void move_clusters();
/**
 * OSTATNI FUNKCE
 */
void init_cluster(struct cluster_t *c, int cap);
void init_cluster(struct cluster_t *c, int cap);
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);
void append_cluster(struct cluster_t *c, struct obj_t obj);
void sort_cluster(struct cluster_t *c);
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);
int remove_cluster(struct cluster_t *carr, int narr, int idx);
float obj_distance(struct obj_t *o1, struct obj_t *o2);
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);
static int obj_sort_compar(const void *a, const void *b);
void sort_cluster(struct cluster_t *c);
void print_cluster(struct cluster_t *c);
int load_clusters(char *filename, struct cluster_t **arr);
void print_clusters(struct cluster_t *carr, int narr);


/*********************** DEFINICE FUNKCI ***********************/

/**
 * Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 * Ukazatel NULL u pole objektu znamena kapacitu 0.
 * @param c je ukazatel na shluk, ktery ma byt inicializovan
 * @param cap je kapacita, na kterou ma byt shluk c inicializovan
 */
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);
	c->size = 0;
	c->obj = malloc(cap * sizeof(struct obj_t));
	c->capacity = cap;
}

/**
 * Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 * @param c je ukazatel na cluster, ze ktereho maji byt odstraneny objekty a ktery ma byt inicializovan na prazdny
 */
void clear_cluster(struct cluster_t *c)
{
    free(c->obj);
	c->size = 0;
	c->capacity = 0;
	c->obj = NULL;
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/**
 * Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 * @param c je ukazatel na shluk, ktery ma byt rozsiren
 * @param new_cap urcuje, na kolik bude kapacita shluku rozsirena
 * @return vraci shluk, rozsireny na danou kapacitu
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t*)arr;
    c->capacity = new_cap;
    return c;
}

/**
 * Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 * nevejde.
 * @param c je ukazatel na shluk
 * @param obj je objekt, ktery se ma pridat do shluku c
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
	if(c->capacity <= c->size)
	{
		resize_cluster(c, c->capacity + CLUSTER_CHUNK);
	}
    c->obj[c->size++] = obj;
}
/**
 * Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 * Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 * Shluk 'c2' bude nezmenen.
 * @param c1 je ukazatel na prvni shluk
 * @param c2 je ukazatel na druhy shluk
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);

    if(c1->capacity <= (c1->size + c2->size))
		resize_cluster(c1, c1->capacity + CLUSTER_CHUNK);
	for(int i = 0; i < c2->size;i++)
		c1->obj[c1->size++] = c2->obj[i];
	sort_cluster(c1);
}

/*********************** PRACE S POLEM SHLUKU ***********************/

/**
 * Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 * (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 * pocet shluku v poli.
 * @param carr je ukazatel na pole shluku
 * @param narr je pocet shluku v poli
 * @param idx je index shluku, ktery ma byt odstranen
 * @return vraci novy pocet shluku v poli
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);
    clear_cluster(&carr[idx]);
	narr--;
	return narr;
}

/**
 * Pocita Euklidovskou vzdalenost mezi dvema objekty.
 * @param o1 je ukazatel na prvni objekt
 * @param o2 je ukazatel na druhy objekt
 * @return vraci vzdalenost mezi objekty
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    float obj_distance = sqrtf((o2->x - o1->x)*(o2->x - o1->x)+(o2->y - o1->y)*(o2->y - o1->y));
	return obj_distance;
}

/**
 * Pocita vzdalenost dvou shluku.
 * @param c1 je ukazatel na prvni shluk
 * @param c2 je ukazatel na druhy shluk
 * @return vraci vzdalenost dvou shluku
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);
    float cluster_distance = 0;
	if(premium_case == 1) //vypocet vzdalenosti shluku metodou avg
	{
		for(int i = 0; i < c1->size;i++)
		{
			for(int k = 0; k < c2->size;k++)
			{
				cluster_distance += obj_distance(&c1->obj[i], &c2->obj[k]);
			}
		}

		cluster_distance = cluster_distance / (c1->size * c2->size);
	}
	else if(premium_case == 2) //vypocet vzdalenosti shluku metodou nejblizsiho souseda
	{
		float min_cluster_distance = 0;
		cluster_distance = obj_distance(&c1->obj[0], &c2->obj[0]);
		for(int i = 0; i < c1->size;i++)
		{
			for(int k = 0; k < c2->size;k++)
			{
				min_cluster_distance = obj_distance(&c1->obj[i], &c2->obj[k]);
				if(cluster_distance > min_cluster_distance)
					cluster_distance = min_cluster_distance;
			}
		}

	}
	else if(premium_case == 3) //vypocet vzdalenosti shluku metodou nejvzdalenejsiho souseda
	{
		float max_cluster_distance = 0;
		cluster_distance = 0;
		for(int i = 0; i < c1->size;i++)
		{
			for(int k = 0; k < c2->size;k++)
			{
				max_cluster_distance = obj_distance(&c1->obj[i], &c2->obj[k]);
				if(cluster_distance < max_cluster_distance)
					cluster_distance = max_cluster_distance;
			}
		}

	}
	return cluster_distance;
}

/**
 * Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 * hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 * 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 * adresu 'c1' resp. 'c2'.
 * @param carr je ukazatel na pole shluku
 * @param narr je veliksot pole shluhu
 * @param c1 je index prvniho shluku
 * @param c2 je index druheho shluku
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);
    *c1 = 0;
	*c2 = 1;
	float min_distance = 0; //aktualni minimalni vzdalenost
	float min_distance_tmp = 0; //prave spocitana vzdalenost
    for(int i = 0; i < narr - 1; i++)
	{
		for(int k = i + 1; k < narr; k++)
		{
			min_distance_tmp = cluster_distance(&carr[i], &carr[k]);
			if(!min_distance)
				min_distance = min_distance_tmp;
			else if(min_distance_tmp < min_distance)
			{
				min_distance = min_distance_tmp;
				*c1 = i;
				*c2 = k;
			}
		}
	}
}
/**
 * Pomocna funkce pro razeni shluku
 */
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/**
 * Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
 * @param c ukazatel na shluk
 */
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/**
 * Tisk shluku 'c' na stdout.
 * @param c ukazatel na pole shluku
 */
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/**
 * Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 * jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 * polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 * kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 * pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
 * @param filename urcuje jmeno souboru, ktery se ma otevrit a ze ktereho se maji objekty nacitat
 * @param arr je ukazatel na pole shluku
 * @return vraci pocet nactenych objektu
 */
#define OUT(x) ((x < 0 || x > 1000) ? 1:0) //makro pro rozsah souradnic x a y
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);

    FILE *fp;
	fp = fopen(filename, "r");

	if(!fp) //nastane, pokud se nepodarilo otevrit soubor
		return 0;

	int object_amount = 0;
	char load[100];
	char *endpt;
	fgets(load, 100, fp);
	if(sscanf(load, "count=%d%s[!-}]", &object_amount, load) == 2 || object_amount <= 0)//cteni a kontrola prvniho radku
	{
		*arr = NULL;
		fclose(fp);
		return 0;
	}
	*arr = malloc((sizeof(struct cluster_t)) * (object_amount + 1)); //alokuje pamet pro pole slhluku
	struct obj_t object;
	for(int i = 0; i < object_amount; i++) //cyklus pro nacitani ze souboru s objekty
	{
		init_cluster(&(*arr)[i], 1);
		if((fscanf(fp, "%s %g %g", load, &object.x, &object.y) != 3) || OUT(object.x) || OUT(object.y) || ceilf(object.x) != object.x || ceilf(object.y) != object.y || object.id > INT_MAX)//nastane pokud data nejsou ve spravnem formatu
		{
			free_memory(arr, i+1);
			fclose(fp);
			return 0;
		}
		object.id = strtol(load, &endpt, 10);
		if(errno == ERANGE || (int) strlen(load) != (endpt - load)) // nastava pokud dojde k OVERFLOW int
		{
			free_memory(arr, i+1);
			fclose(fp);
			return 0;
		}
		append_cluster(&(*arr)[i], object); //pridani objektu do shluku
	}
	if(object_amount != 1) //zjistuje, jestli nejsou id objektu duplicitni
	{
		for(int i = 0;i < object_amount - 1;i++)
		{
			for(int k = i + 1; k < object_amount;k++)
			{
				if((*arr)[i].obj->id == (*arr)[k].obj->id)
				{
					free_memory(arr, object_amount);
					fclose(fp);
					return 0;
				}
			}
		}
	}
	fclose(fp);
	return object_amount;
}

/**
 * Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 * Tiskne se prvnich 'narr' shluku.
 * @param carr je ukazatel na prvni polozku
 * @param narr je pocet, kolik shluku se ma tisknout
 */
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}
/*********************** VLASTNI FUNKCE ***********************/
/**
 * Uvolni alokovanou pamet.
 * @param arr je ukazatel na pole shluku
 * @param size urcuje, kolik se toho ma uvolnit
 */
void free_memory(struct cluster_t **arr, int size)
{
	for(int i = 0;i < size;i++)
	{
		clear_cluster(&(*arr)[i]);
	}
	free(*arr);
}
/**
 * Uvolni alokovanou pamet.
 * @param arr je ukazatel na pole shluku
 * @param narr urcuje, kolik shluhu se ma posunout
 * @param c2 urcuje, odkud se maji shluky zacit posouvat
 */
void move_clusters(struct cluster_t **arr, int narr, int c2)
{
	for(int i = c2; i < narr + 1; i++)
	{
		(*arr)[i] = (*arr)[i+1];
	}
}
/*********************** HLAVNI PROGRAM ***********************/
int main(int argc, char *argv[])
{
    struct cluster_t *clusters;
	if(argc > 1)
	{
		int cluster_amount = load_clusters(argv[1], &clusters); //pocet clusteru/objektu
		int c1, c2; //indexy clusteru, ktere maji byt spojeny
		int cluster_amount_final = 1; //finalni pocet clusteru, implicitne je nastaven na 1
		char *end; //ukazatel na char, pomocna promenna pro funkci strtol

		if(!cluster_amount) //nastava v pripade, ze funkce load_clusters byla neuspena
		{
			fprintf(stderr, "ERROR:Chyba pri nacitani. Soubor s daty nelze otevrit a nebo jsou data v nespravnem formatu.\n");
			return EXIT_FAILURE;
		}
		if(argc > 2) //nastava v pripade, ze je zadan argv[2]
		{
			cluster_amount_final = strtol(argv[2], &end, 10); //novy finalni pocet clusteru
			if(cluster_amount_final > cluster_amount)
				cluster_amount_final = cluster_amount;
			if((int) strlen(argv[2]) != (end - argv[2])) //kontrola, jestli byl argv[2] cele cislo
			{
				fprintf(stderr, "ERROR:Argumenty zadany ve spatnem formatu.\n");
				free_memory(&clusters, cluster_amount);
				return EXIT_FAILURE;
			}
			if(argc == 4)
			{
				if(strcmp(argv[3],"--avg") == 0)
				premium_case = 1;
				else if(strcmp(argv[3],"--min") == 0)
				premium_case = 2;
				else if(strcmp(argv[3],"--max") == 0)
				premium_case = 3;
				else
				{
					fprintf(stderr, "ERROR:Argumenty zadany ve spatnem formatu.\n");
					free_memory(&clusters, cluster_amount);
					return EXIT_FAILURE;
				}
			}
		}

		if(cluster_amount_final < 1 || argc > 4) //nastava v pripade, ze finalni pocet clusteru je zaporny nebo je vetsi pocet argumentu
		{
			fprintf(stderr, "ERROR:Argumenty zadany ve spatnem formatu.\n");
			free_memory(&clusters, cluster_amount);
			return EXIT_FAILURE;
		}

		while(cluster_amount != cluster_amount_final) //cyklus, ktery vola funkci pro nalezeni a posleze spojeni nejblizsich clusteru, probiha dokud neni aktualni pocet clusteru shodny s finalnim poctem clusteru
		{
			find_neighbours(clusters, cluster_amount, &c1, &c2);
			merge_clusters(&clusters[c1], &clusters[c2]);
			cluster_amount = remove_cluster(clusters, cluster_amount, c2);
			move_clusters(&clusters, cluster_amount, c2);
		}
		print_clusters(clusters, cluster_amount); //funkce na vypis clusteru

		free_memory(&clusters, cluster_amount); //funkce na uvolneni pameti
	}
	else //nastava, pokud nejsou zadany zadne argumenty
	{
		fprintf(stderr, "ERROR:Nejsou zadane zadne argumenty.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
