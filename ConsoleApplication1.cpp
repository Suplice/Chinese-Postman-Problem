#include <iostream>
#include <map>
#include <ctype.h>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>
#include <list>
#include <limits>
#include <vector>
#include "funkcje.h"

typedef std::map<std::string, std::list<std::pair<std::pair<std::string, double >, std::string>>> Graph;

int main(int argc, char* argv[])
{
	if (argc == 7)
	{
		std::string plik_wejsciowy = (argv[2]);		std::string plik_wyjsciowy = (argv[4]);
		std::string node = (argv[6]);
		std::list<std::string> niep_punkty;
		std::ofstream z(plik_wyjsciowy);
	
		auto graph = LoadFromFile(plik_wejsciowy);
		//pusty graf
		if (!graph.size())
			std::cout << "brak punktów";
	

		if (!czy_sp(graph, BFS(graph))) // spójność grafu
		{
			std::cout << "Graf nie jest spójny";
		}
		else if (nieparzyste_punkty(graph).size())
		{
			niep_punkty = nieparzyste_punkty(graph); //lista nieparzystych punktów
			std::vector<std::pair<std::pair<std::string, double>, std::string>> vectord = Wyszuk_niep_pary(graph, niep_punkty); //wszystkie możliwe pary z nieparzystych punktów
			std::vector<std::pair<std::pair<std::string, std::string>, double>> wynik = Najlkrtosze_Pary(vectord, niep_punkty); // najlepsze pary z nieparzystych punktów
			wypisz_wynik(Flurry(rekonstrukcja_trasy(graph, wynik), node), graph, plik_wyjsciowy); // najszybsza trasa, wraz z powrotem
		}
		else
		{
			wypisz_wynik(Flurry(graph, node), graph, plik_wyjsciowy); // najszybsza trasa, wraz z powrotem
		}





	}
	else
		std::cout << "nie dziala :(";
}

