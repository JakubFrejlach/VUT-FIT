/**
 * @mainpage Projekt 3
 * @link
 * proj3.h
 * @endlink
 *
 * @file proj3.h
 * @brief Projekt 3 - Jednoducha shlukova analyza
 * @author Jakub Frejlach - xfrejl00
 * @date prosinec 2017
 */

/**
 @brief struktura, ktera predstavuje objekt s identifikatorem a souradnicemi
 */
struct obj_t {
	/** identifikator */
    int id;
	/** souradnice x */
    float x;
	/** souradnice y */
    float y;
};

/**
 @brief struktura, ktera predstavuje shluk objektu
 */
struct cluster_t {
	/** velikost shluku */
    int size;
	/** kapacita shluku */
    int capacity;
	/** pole objektu */
    struct obj_t *obj;
};
/**
 * @defgroup clusters Prace se shluky
 * @{
 */

/**
 * Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 * Ukazatel NULL u pole objektu znamena kapacitu 0.
 *
 * @pre
 * c != NULL
 * cap >= 0
 * @post
 * shluku c bude alokovana pamet o velikost cap
 * @param *c je ukazatel na shluk, ktery ma byt inicializovan
 * @param cap je kapacita, na kterou ma byt shluk inicializovan
 */
void init_cluster(struct cluster_t *c, int cap);

/**
 * Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 *
 * @pre
 * c != NULL
 * @post
 * bude uvolnena pamet alokovana shluku c a shluk c bude inicializovan na prazdny shluk
 * @param *c je ukazatel na shluk, ktery ma byt uvolnen
 */
void clear_cluster(struct cluster_t *c);

///Hodnota slouzici pro realokaci shluku
extern const int CLUSTER_CHUNK;

/**
 * Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 *
 * @pre
 * c != 0
 * @pre
 * c->capacity >= 0
 * @pre
 * new_cap >= 0
 * @post
 * pamet shluku c bude rozsirena na velikost new_cap
 * @param *c je ukazatel na shluk, ktery ma byt rozsiren
 * @param new_cap je kapacita, na kterou ma byt shluk c rozsiren
 * @return vraci ukazatel na shluk, rozsireny na danou kapacitu
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 * nevejde.
 *
 * @pre
 * c != NULL
 * @post
 * objekt obj bude pridan na konec shluku c a pripadne bude shluk c rozsiren
 * @param *c je ukazatel na shluk, do ktereho ma byt pridan objekt obj
 * @param obj je objekt, ktery ma byt pridan do shluku c
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 * Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 *
 * @pre
 * c1 != NULL
 * @pre
 * c2 != NULL
 * @post
 * objekty shluku c2 budou pridany do shluku c1 a shluk c1 bude pripadne rozsiren,
 * shluk c2 zustava nezmenen.
 * @param *c1 je ukazatel na shluk, do ktereho se budou pridavat objekty
 * @param *c2 je ukazatel na shluk, ze ktereho se budou pridavat objekty
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
 *
 * @post
 * Objekty shluhu c budou serazeny vzestupne podle jejich identifikatoru
 * @param *c je ukazatel na shluk, ktery ma byt serazen
 */
void sort_cluster(struct cluster_t *c);

/**
 * Tisk shluku 'c' na stdout.
 *
 * @post
 * Objekty shluhu c budou vypsany na stdout
 * @param *c je ukazatel na shluk, jehoz objekty maji byt vypsany na stdout
 */
void print_cluster(struct cluster_t *c);

/**
 * @}
 */

/**
 * @defgroup array_of_clusters Prace s polem shluku
 * @{
 */

/**
 * Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 * (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 * pocet shluku v poli.
 *
 * @pre
 * idx > narr
 * @pre
 * narr > 0
 * @post
 * shluk s indexem idx je odstranen z pole shluku carr
 * @param *carr je ukazatel na pole shluku
 * @param narr je pocet shluku v poli carr
 * @param idx je index shluku, ktery ma byt z pole carr odstranen
 * @return vraci novy pocet shluku v poli carr
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/**
 * Pocita Euklidovskou vzdalenost mezi dvema objekty.
 *
 * @pre
 * o1 != NULL
 * @pre
 * o2 != NULL
 * @param *o1 je ukazatel na prvni objekt
 * @param *o2 je ukazatel na druhy objekt
 * @return vraci vzdalenost mezi objekty o1 a o2
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * Pocita vzdalenost dvou shluku.
 *
 * @pre
 * c1 != NULL
 * @pre
 * c1->size > 0
 * @pre
 * c2 != NULL
 * @pre
 * c2->size > 0
 * @param *c1 je ukazatel na prvni shluk
 * @param *c2 je ukazatel na druhy shluk
 * @return vraci vzdalenost mezi shluky c1 a c2
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 * hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 * 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 * adresu 'c1' resp. 'c2'.
 *
 * @pre
 * narr > 0
 * @post
 * do c1 a c2 budou ulozeny indexy dvou nejblizsich shluku
 * @param *carr je ukazatal na pole shluku
 * @param narr je velikost pole shluku
 * @param *c1 je ukazatel na index prvniho shluku
 * @param *c2 je ukazatel na index druheho shluku
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);
/**
/**
 * Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 * jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 * polozku pole (ukazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 * kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 * pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
 *
 * @pre
 * arr != NULL
 * @post
 * Ze vstupniho souboru budou nacteny shluku do pole shluku arr,
 * kde bude pro kazdy objekt vytvoren shluk.
 * Pole arr bude mit alkovanou pamet pro pocet shluku,
 * ktery je uvedeny ve vstupni souboru
 * @param *filename je ukazatal na nazev vstupniho souboru
 * @param **arr je ukazatel na pole shluku
 * @return vraci pocet nactenych objektu
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
 * Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 * Tiskne se prvnich 'narr' shluku.
 *
 * @post
 * Objekty vsech shluku budou vypsany na stdout
 * @param *carr je ukazatel na pole shluku
 * @param narr je pocet shluku v poli
 */
void print_clusters(struct cluster_t *carr, int narr);

/**
 * Uvolni alokovanou pamet.
 * @post
 * budou uvolneny a smazany vsechny nactene shluky
 * @param **arr je ukazatel na pole shluku
 * @param size urcuje pocet shluku v poli
 */
void free_memory(struct cluster_t **arr, int size);

/**
 * Posune shluky v poli shluku tak,
 * aby po slouceni shluku nebylo v polu prazdne misto
 *
 * @pre
 * byl uvolnen a smazan shluk
 * @post
 * shluky budou opet serazeny za sebou, vzestupne podle identifikaru
 * a nebude mezi nimi prazdne misto po smazanem shluku
 * @param **arr je ukazatel na pole shluku
 * @param narr urcuje pocet shluku, ktere se maji posunout
 * @param *c2 je ukazatel na shluk, od ktereho se ma zacit posouvat
 */
void move_clusters(struct cluster_t **arr, int narr, int c2);

/**
 * @}
 */
