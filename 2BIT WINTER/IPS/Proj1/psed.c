//Tomas Venkrbec (xvenkr01) && Jakub Frejlach (xfrejl00)

#include<stdio.h>
#include<unistd.h>
#include<thread>
#include<queue>
#include<mutex>
#include<vector>
#include<iostream>
#include<string.h>
#include<regex>
#include<string>

int eof = 0; // Globalni promenna signalizujici konec souboru
int x; // Globalni promenna signalizujici pocet threadu, co nevypsaly aktualni output
std::string line;

std::vector<std::mutex*> zamky; // pole zamku promenne velikosti
std::vector<std::mutex*> mutex; // pole mutexu promenne velikosti

void f(int ID, char **argv)
{
	std::regex re(argv[ID*2 + 1]);
	std::string output;

	while(23)
	{
		zamky[ID]->lock(); // Cekame na predani rizeni
		if(eof != 0) // Pokud je konec souboru, skoncime
			break;
		output = std::regex_replace(line, re, argv[ID*2 + 2]); //Provedeme nahradu

		mutex[ID]->lock(); // Pristup do mutexu chranici vystup a globalni promennou
		std::cout << output << "\n";
		x--;
		mutex[ID+1]->unlock();

	}
}

int main(int argc, char **argv)
{
	/*******************************
	* Inicializace threadu a zamku
	* *****************************/
	int num = (argc - 1) / 2;
	x = num;
	int num_zamky = num;
	std::vector <std::thread*> threads; // pole threadu promenne velikosti

	// vytvorime zamky
	zamky.resize(num_zamky); // nastavime si velikost pole zamky
	for(int i = 0; i < num_zamky; i++)
	{
		std::mutex *new_zamek = new std::mutex();
		zamky[i] = new_zamek;
		zamky[i]->lock();
	}

	mutex.resize(num_zamky + 1); // nastavime si velikost pole mutex
	for(int i = 0; i <= num_zamky; i++)
	{
		std::mutex *new_mutex = new std::mutex();
		mutex[i] = new_mutex;
		mutex[i]->lock();
	}

	// vytvorime thready
	threads.resize(num); // nastavime si velikost pole threads
	for(int i = 0; i < num; i++)
	{
		std::thread *new_thread = new std::thread (f, i, argv);
		threads[i] = new_thread;
	}

	/**********************************
		* Vlastni vypocet psed
	* ********************************/

	std::getline(std::cin, line); //Nacteme radek
	while (!std::cin.eof())
	{
		for(int i = 0; i < num; i++)
		{
			zamky[i]->unlock(); // Predame rizeni
		}
		mutex[0]->unlock();
		while(x != 0);
		x = num;

		std::getline(std::cin, line);
	}
	eof = 1;
	for(int i = 0; i < num; i++)
	{
		zamky[i]->unlock(); // Pustime thready na konec jejich funkce
	}

	/**********************************
		* Uvolneni pameti
	* ********************************/
	// provedeme join a uvolnime pamet threads
	for(int i = 0; i < num; i++)
	{
		(*(threads[i])).join();
		delete threads[i];
	}

	// uvolnime pamet zamku
	for(int i = 0; i < num_zamky; i++)
	{
		delete zamky[i];
	}

	//uvolnime mutexy
	for(int i = 0; i < num_zamky+1; i++)
	{
		delete mutex[i];
	}

}
