/*
 *  Soubor: proj2.c
 *  Reseni IOS - projekt 2 - The Senate Bus Problem 29.4.2018
 *  Autor: Jakub Frejlach (xfrejl00), FIT
 *  Prelozeno: gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<time.h>
#include<errno.h>

/********** Makra pro jmena semaforu **********/
#define SEMAPHORE1_NAME "/semaphore_xfrejl00_1"
#define SEMAPHORE2_NAME "/semaphore_xfrejl00_2"
#define SEMAPHORE3_NAME "/semaphore_xfrejl00_3"
#define SEMAPHORE4_NAME "/semaphore_xfrejl00_4"
#define SEMAPHORE5_NAME "/semaphore_xfrejl00_5"
#define SEMAPHORE6_NAME "/semaphore_xfrejl00_6"

/********** Makra pro pocatectni stavy semaforu **********/
#define UNLOCKED 1
#define LOCKED 0

/********** Struktura nesouci zpracovane vstupni argumenty **********/
typedef struct params
{
  long riders; // Pocet procesu riders
  long capacity; // Kapacita autobusu
  long art; // Cas uspani generatoru rideru
  long abt; // Cas simaluce jizdy

}params_t;

/********** ID pro vytvoreni sdilenych promennych **********/
int action_counter_id = 0;
int passenger_counter_id = 0;
int finished_riders_id = 0;

/********** Sdilene promenne **********/
int *action_counter = NULL;
int *passenger_counter = NULL;
int *finished_riders = NULL;

/********** Semafory **********/
sem_t *bus_in_stop = NULL; // Semafor kontrulujici, zdali je autobus v zastavce
sem_t *writing = NULL; // Semafor pro pristup k zapisu a inkrementace sdilenych prommenych
sem_t *boarding = NULL; // Semafor kontrolujici nastupovani
sem_t *wait_for_board = NULL; // Semafor kontrolujici nastupovani
sem_t *wait_for_unboard = NULL; // Semafor kontrolujici vystupovani
sem_t *unboarding = NULL; // Semafor kontrolujici vystupovani

/********** Ostatni **********/
FILE *fp; // Soubor pro zapis dat

/*
 * Funkce pro zpracovani vstupnich argumentu programu
 *
 * @param arg_count       pocet vstupnich argumentu
 * @param arg             vstupni argumenty
 * @param params          struktura pro uchovani dat ze vstupnich parametru
 * @return                vraci true, pokud byly vsechny argumenty zadany spravne
 */
bool get_params(int arg_count, char *arg[], params_t *params)
{
  char *end;
  if(arg_count != 5)
    return false;

  params->riders = strtol(arg[1], &end, 10);
  if(*end != '\0' || errno == ERANGE || params->riders <= 0)
    return false;

  params->capacity = strtol(arg[2], &end, 10);
  if(*end != '\0' || errno == ERANGE || params->capacity <= 0)
    return false;

  params->art = strtol(arg[3], &end, 10);
  if(*end != '\0' || errno == ERANGE || params->art < 0 || params->art > 1000)
    return false;

  params->abt = strtol(arg[4], &end, 10);
  if(*end != '\0' || errno == ERANGE || params->abt < 0 || params->abt > 1000)
    return false;

  return true;
}

/*
 * Funkce pro inicializaci sdilenych promennych a semaforu
 *
 * @return        vraci true, pokud vsechny inicializace probehly spravne
 */
bool init()
{
  /****************************** Sdilene promenne ******************************/
  if ((action_counter_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
  {
    return false;
  }
  if ((action_counter = shmat(action_counter_id, NULL, 0)) == NULL)
  {
    return false;
  }
  if ((passenger_counter_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
  {
    return false;
  }
  if ((passenger_counter = shmat(passenger_counter_id, NULL, 0)) == NULL)
  {
    return false;
  }
  if ((finished_riders_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
  {
    return false;
  }
  if ((finished_riders = shmat(finished_riders_id, NULL, 0)) == NULL)
  {
    return false;
  }

  /****************************** Semafory ******************************/
  if ((bus_in_stop = sem_open(SEMAPHORE1_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
  {
    return false;
  }
  if ((writing = sem_open(SEMAPHORE2_NAME, O_CREAT | O_EXCL, 0666, UNLOCKED)) == SEM_FAILED)
  {
    return false;
  }
  if ((boarding = sem_open(SEMAPHORE3_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
  {
    return false;
  }
  if ((wait_for_board = sem_open(SEMAPHORE4_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
  {
    return false;
  }
  if ((wait_for_unboard = sem_open(SEMAPHORE5_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
  {
    return false;
  }
  if ((unboarding = sem_open(SEMAPHORE6_NAME, O_CREAT | O_EXCL, 0666, LOCKED)) == SEM_FAILED)
  {
    return false;
  }
  return true;
}

/*
 * Funkce pro uklid sdilenych prommenych, semaforu a vystupniho souboru
 *
 * @return        vraci true, pokud vsechno probehlo spravne
 */
bool clear()
{
  bool clear_ok = true;

  /****************************** Soubor ******************************/
  if(fclose(fp) == EOF)
  {
    clear_ok = false;
  }

  /****************************** Sdilene promenne ******************************/
  if(shmctl(action_counter_id, IPC_RMID, NULL) == -1)
  {
    clear_ok = false;
  }
  if(shmdt(action_counter) == -1)
  {
    clear_ok = false;
  }
  if(shmctl(passenger_counter_id, IPC_RMID, NULL) == -1)
  {
    clear_ok = false;
  }
  if(shmdt(passenger_counter) == -1)
  {
    clear_ok = false;
  }
  if(shmctl(finished_riders_id, IPC_RMID, NULL) == -1)
  {
    clear_ok = false;
  }
  if(shmdt(finished_riders) == -1)
  {
    clear_ok = false;
  }

  /****************************** Sdilene promenne ******************************/
  if((sem_close(bus_in_stop)) == -1 || sem_unlink(SEMAPHORE1_NAME) == -1)
  {
    clear_ok = false;
  }
  if((sem_close(writing)) == -1 || sem_unlink(SEMAPHORE2_NAME) == -1)
  {
    clear_ok = false;
  }
  if((sem_close(boarding)) == -1 || sem_unlink(SEMAPHORE3_NAME) == -1)
  {
    clear_ok = false;
  }
  if((sem_close(wait_for_board)) == -1 || sem_unlink(SEMAPHORE4_NAME) == -1)
  {
    clear_ok = false;
  }
  if((sem_close(wait_for_unboard)) == -1 || sem_unlink(SEMAPHORE5_NAME) == -1)
  {
    clear_ok = false;
  }
  if((sem_close(unboarding)) == -1 || sem_unlink(SEMAPHORE6_NAME) == -1)
  {
    clear_ok = false;
  }
  return clear_ok;
}

/*
 * Proces "rider"
 *
 * @param index       ID procesu
 */
void rider(int index)
{
  sem_wait(writing);
  fprintf(fp, "%d\t: RID %d\t: start\n", ++(*action_counter), index);
  sem_post(writing);

  sem_wait(bus_in_stop); // Pokud je bus v zastavce, cestujici nemuze vstoupit
  sem_wait(writing);
  fprintf(fp, "%d\t: RID %d\t: enter: %d\n", ++(*action_counter), index, ++(*passenger_counter));
  sem_post(writing);
  sem_post(bus_in_stop); // Opetovne otevreni zastavky -> kazdy proces rider ji po sobe zase otevre ->
                         // -> finalni zavreni provede az bus po opetovnem prijezdu do zastavky

  sem_wait(boarding); // Pokud nastupuje jiny cestujici, musi aktualni cestujici pockat
  sem_wait(writing);
  fprintf(fp, "%d\t: RID %d\t: boarding\n", ++(*action_counter), index);
  sem_post(writing);
  sem_post(wait_for_board); // Signal pro autobus, ze muze nabrat dalsiho cestujiciho

  sem_wait(unboarding); // Pokud vystupuje jiny cestujici nebo autobus prave simuluje jizdu, musi cestujici cekat
  sem_wait(writing);
  fprintf(fp, "%d\t: RID %d\t: finish\n", ++(*action_counter), index);
  sem_post(writing);
  sem_post(wait_for_unboard); // Signal pro autobus, ze muze vystoupit dalsi cestujici
  exit(EXIT_SUCCESS);
}

/*
 * Proces "bus"
 *
 * @param params        struktura nesouci data ze zpracovanych vstupnich argumentu
 */
void bus(params_t params)
{
  int capacity = 0;

  sem_wait(writing);
  fprintf(fp, "%d\t: BUS \t: start\n", ++(*action_counter));
  sem_post(writing);

  while(1)
  {
    sem_wait(writing);
    fprintf(fp, "%d\t: BUS \t: arrival\n", ++(*action_counter));
    sem_post(writing);

    if((*passenger_counter) != 0) // Pokud na zastavce nejsou cestujici, autobus rovnou odjizdi
    {

      sem_wait(writing);
      fprintf(fp, "%d\t: BUS \t: start boarding: %d\n", ++(*action_counter), *passenger_counter);
      sem_post(writing);

      for(int i = capacity; i > 0; i--) // Vystoupeni cestujicich z autobusu
      {
        sem_post(unboarding); // Signal pro cestujici, ze muzou nastoupit
        sem_wait(wait_for_unboard); // Ceka, dokud cestujici nenastoupi
      }
      capacity = 0; // Vynulovani kapacity autobusu -> vsichni vystoupili

      while((*passenger_counter) != 0 && capacity != params.capacity) // Cestujici nastupuju dokud neni autobus plny nebo dokud na zastavce dalsi nejsou
      {
        sem_wait(writing);
        (*passenger_counter)--; // Cestujici nastupuje -> pocet cestujicich na zastavce je snizen
        sem_post(writing);
        capacity++; // Cestujici nastupuje -> pocet cestujicich v autobuse je zvysen
        sem_wait(writing);
        (*finished_riders)++; // Citac odbavenych cestujicich
        sem_post(writing);
        sem_post(boarding); // Signal cestujicimu, ze muze nastoupit
        sem_wait(wait_for_board); // Ceka, dokud cestujici nenastoupi
      }

      sem_wait(writing);
      fprintf(fp, "%d\t: BUS \t: end boarding: %d\n", ++(*action_counter), *passenger_counter);
      sem_post(writing);
    }

    sem_wait(writing);
    fprintf(fp, "%d\t: BUS \t: depart\n", ++(*action_counter));
    sem_post(writing);
    sem_post(bus_in_stop); // Autobus odjizdi ze zastavky -> cestujici mohou prichazet na zastavku

    if(params.abt != 0) // Simulace jizdy autobusu
    {
      usleep((rand() % params.abt)*1000);
    }

    sem_wait(writing);
    fprintf(fp, "%d\t: BUS \t: end\n", ++(*action_counter));
    sem_post(writing);
    sem_wait(bus_in_stop); // Autobus se vraci na zastavku -> dalsi cestujici nemohou nastupovat
    if((*finished_riders) == params.riders) // Pokud byli jiz odbaveni vsichni cestujici, autobus konci
      break;
  }
  sem_wait(writing);
  fprintf(fp, "%d\t: BUS \t: finish\n", ++(*action_counter));
  sem_post(writing);

  for(int i = capacity; i > 0; i--) // Vystoupeni poslednich cestujicich
  {
    sem_post(unboarding);
    sem_wait(wait_for_unboard);
  }
}

int main(int argc, char *argv[])
{

  params_t params;
  if(get_params(argc, argv, &params) == false) // Zpracovani argumentu
  {
    fprintf(stderr, "ERROR:Spatne zadane argumenty.\n");
    return EXIT_FAILURE;
  }

  if((fp = fopen("proj2.out", "w")) == NULL) // Otevreni vystupniho souboru proj2.out pro zapis
  {
    fprintf(stderr, "ERROR:Nepodarilo se otevrit soubor pro zapisovani dat.\n");
    return EXIT_FAILURE;
  }

  setbuf(fp, NULL);

  if(init() == false) // Inicializace
  {
    fprintf(stderr, "ERROR:Chyba pri inicializaci.\n");
    return EXIT_FAILURE;
  }

  srand(time(NULL)); // Pattern pro funkci rand()

  pid_t rider_pid; // ID pro praci s procesy "rider"
  pid_t base_pid = fork(); // ID pro praci s procesy "bus"

  if(base_pid == 0) // Rider generator -> child proces
  {
    for(int i = 0; i < params.riders; i++) // Generovani N rideru podle vstupniho argumentu
    {
      rider_pid = fork();
      if(rider_pid == 0) // Proces "rider" -> child proces
      {
        rider(i+1);
      }
      else if(rider_pid > 0) // Prodleva mezi dalsim generovanim
      {
        if(params.art != 0)
        {
          usleep((rand() % params.art)*1000);
        }
        continue;
      }
      else // Chyba ve funkci fork()
      {
        fprintf(stderr, "ERROR:Chyba pri fork().\n");
        if(clear() == false)
        {
          fprintf(stderr, "ERROR:Chyba pri clear.\n");
          return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
      }
    }

    for(int i = 0; i < params.riders; i++) // Cekani na ukonceni vsech procesu "rider"
    {
      waitpid(-1, NULL, 0);
    }
    exit(EXIT_SUCCESS);
  }
  else if(base_pid > 0) // Bus -> parent proces
  {
    bus(params);
  }
  else // Chyba ve funkci fork()
  {
    fprintf(stderr, "ERROR:Chyba pri fork().\n");
    if(clear() == false)
    {
      fprintf(stderr, "ERROR:Chyba pri clear.\n");
      return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
  }

  waitpid(-1, NULL, 0); // Cekani na ukonceni generatoru rideru


  if(clear() == false) // Uklid
  {
    fprintf(stderr, "ERROR:Chyba pri clear.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
