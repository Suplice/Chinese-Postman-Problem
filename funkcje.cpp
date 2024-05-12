#include <iostream>
#include <ctype.h>
#include <map>
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
Graph LoadFromFile(const std::string& FileName)
{
	
	Graph graph;
	std::ifstream in(FileName);
	if (in)
	{
		std::string line;
		while (std::getline(in, line))
		{
			std::stringstream ss(line);
			std::string node1, node2, name_help, name;
			double length;
			if (!(ss >> node1)) continue;
			if (!(ss >> node2)) continue;
			if (!(ss >> length)) continue;
		
			while (ss >> name_help)
			{
				name += name_help;
				name += " ";
			}

			graph[node1].push_back({ {node2,length} , name});
			graph[node2].push_back({ {node1,length} , name});
			
			
			
			
		}

	}
	
	return graph;
}



std::set<std::string> BFS(const Graph& graph)
{
	std::string node = graph.begin()->first;
	std::set<std::string> wynik{ node };
	std::list<std::string> punkty{ node };
	
	while (!punkty.empty())
	{
		
		for (const auto& el : graph.at(punkty.front()))
		{
			if (wynik.count(el.first.first) == 0) //czy punkty nie by³ sprawdzany
			{
				wynik.insert(el.first.first);		//dodaj do sprawdzonych
				punkty.push_back(el.first.first);	//dodaj do sprawdzenia
			}
		}
		punkty.pop_front();
	}

	return wynik;

}

bool czy_sp(Graph graph, std::set<std::string> graph_pomoc)
{
	if (graph.size() == graph_pomoc.size())
		return true;
	else
		return false;
}

std::list<std::string> nieparzyste_punkty(const Graph& graph)
{
	std::list<std::string> nieparzyste_punkty;
	int licznik = 0;

	for (const auto& el : graph)
	{
		for (const auto& el2 : el.second)
		{
			licznik++;
		}
		if (licznik % 2 == 1) // dany punkty posiada nieparzyst¹ iloœæ po³¹czeñ
			nieparzyste_punkty.push_back(el.first);
		
			
		licznik = 0;
	}

	return nieparzyste_punkty;
}

std::map<std::string, double> dijkstry(Graph graph, std::string node)
{
	

	
	std::map<std::string, double> wynik;
	std::set<std::string> nodes;

	for (const auto& el : graph)
	{
		wynik[el.first] = std::numeric_limits<double>::infinity(); // ustaw wszystkie odleg³oœci w grafie na inf
	}
	wynik[node] = 0.0; 

	while (true)
	{
		for (const auto& el : graph.at(node))
		{
			if (wynik[el.first.first] > wynik[node] + el.first.second) //min odlegloœc do punktu_2 > odl(punktu) + odl do punktu_2 
			{
				wynik[el.first.first] = wynik[node] + el.first.second;
				nodes.insert(el.first.first);
			}
		}
		if (nodes.empty()) break; //jeœli wszystko zrobione to koñcz
		node = *min_element(nodes.begin(), nodes.end(), [&wynik](const auto& l, const auto& r) {return wynik[l] < wynik[r]; });
		nodes.erase(node); //usuñ ze sprawdzania punkt z najkrótsz¹ tras¹

	}
	

	return wynik;

}
std::vector<std::pair<std::pair<std::string, double>, std::string>> Wyszuk_niep_pary(Graph graph, std::list<std::string> lista)
{
	std::map<std::string, double> mapa_pomoc;		// mapa najkrótszych tras do wszystkich (wybieramy od jakiego punkty w liœcie)
	std::vector<std::pair<std::pair<std::string, double>, std::string>> pary; 
	bool kasuj = true;								
	
	//przesy³ par do wektora
	for (const auto& punkt : lista)					
	{
		mapa_pomoc = dijkstry(graph, punkt);		// nadajemy najkr. odl. do wszystkich punktów 
		for (const auto& el2 : mapa_pomoc)			// pobieramy parê (punkt oraz odleglosc) z mapy
		{
			kasuj = true; 
			pary.push_back({ el2 ,punkt });			// dodajemy do vectora dany element
			std::pair < std::pair<std::string, double>, std::string> para = pary.back();	// przypisujemy ostatni¹ dodan¹ parê do wektora
			for (const auto& punkt_spr : lista)		// przypisujemy wartoœæ punktów z listy
			{
				if (para.first.first == punkt_spr && para.first.second!=0) // sprawdzamy czy (dany punkt znajduje siê na liœcie && wybrane punkty nie s¹ takie same)
					kasuj = false;					// jeœli punkt znajduje siê na liœcie i nie jest taki sam

			}
			if (kasuj)								//brak punktu na liœcie
			{
				pary.pop_back();					 // kasowanie ostatniej dodanej pary do vectora
			}
		}
	
	}
	
	return pary; // zwracanie wyniku
}


std::vector<std::pair<std::pair<std::string, std::string>, double>>  Najlkrtosze_Pary(std::vector<std::pair<std::pair<std::string, double>, std::string>> pary, std::list<std::string> punkty)
{
	std::vector<std::pair<std::pair<std::string, std::string>, double>> wynik;
	std::map<std::pair<std::string, std::string>, double> odleglosci;
	std::vector <std::string> numerowanie_punktow;
	std::vector<std::vector<double>> vect;
	//przypisywanie odleglosci
	for (const auto& dane : pary)
	{
		odleglosci[{dane.second, dane.first.first}] = dane.first.second;
	}

	//przypisywanie kolejnych wartosci tj: 0, 1, 2... punktom
	for (const auto &punkt : punkty)
	{
		numerowanie_punktow.push_back(punkt);
	}

	//zerowanie tablicy operacyjnej
	for (int i = 0; i < punkty.size(); i++)
	{
		std::vector<double> wiersz;
		for (int j = 0; j < punkty.size(); j++)
		{
			wiersz.push_back(0.0);
		}
		vect.push_back(wiersz);
	}

	//wpisywanie wartosci do tablicy

	for (int i = 0; i < punkty.size();i++)
	{
		for (int j = 0; j < punkty.size(); j++)
		{
			if (i == j)
				vect[i][j] = std::numeric_limits<double>::infinity();
			else
			{
				vect[i][j] = odleglosci[{numerowanie_punktow.at(i), numerowanie_punktow.at(j)}];
				
			}
				
		}
	}
	
	//najmniejszy w wierszu i odejmowanie
	for (int i = 0; i < punkty.size(); i++)
	{
		double minimum = std::numeric_limits<double>::infinity();
		for (int j = 0; j < punkty.size(); j++)
		{
			if (vect[i][j] < minimum)
				minimum = vect[i][j];
		}
		for (int j = 0; j < punkty.size(); j++)
		{
			vect[i][j] -= minimum;
		}
	}
	//najmniejszy w kolumnie i odejmowanie
	for (int i = 0; i < punkty.size(); i++)
	{
		double minimum = std::numeric_limits<double>::infinity();
		for (int j = 0; j < punkty.size(); j++)
		{
			if (vect[j][i] < minimum)
				minimum = vect[j][i];
		}
		for (int j = 0; j < punkty.size(); j++)
		{
			vect[j][i] -= minimum;
		}
	}

	// inicjowanie tablicy dwuwymiarowej, mówi¹cej o miejscu znajdowania siê "0" w vect
	std::vector<std::vector<double>> czy_zero = vect;

	for (int i = 0; i < punkty.size(); i++)
	{
		for (int j = 0; j < punkty.size(); j++)
		{
			if (czy_zero[i][j]) // nadawanie wartoœci 1 w ka¿de miejsce, gdzie wystêpuje "0"
			{
				czy_zero[i][j] = 0;		
			}
			else
				czy_zero[i][j] = 1;
		}
	}

	//inicjowanie tablicy dwuwymiarowej, mówi¹cej o iloœci wystêpuj¹cych "0"  w kolumnie i wierszu, w zaleznosci od badanego zera niezale¿nego
	std::vector<std::vector<double>> wyst_zer = vect;
	//algorytm wêgierski

	for (int w = 0; w < punkty.size(); w++)
	{
		wyst_zer.clear(); // czyszczenie danych, do ponownego u¿ytku
		int ilosc_zer = 0; // licznik zer
		//zerowanie tablicy operacyjnej, mówi¹cej o iloœci zer kolumnie i wierszu od wyranego punktu
		for (int i = 0; i < punkty.size(); i++)
		{
			std::vector<double> pomoc;
			for (int j = 0; j < punkty.size(); j++)
			{
				pomoc.push_back(0.0);
			}
			wyst_zer.push_back(pomoc);
		}

		// przypisywanie iloœci zer wystêpuj¹cyh w kolumnie i wierszu od danej komórki, do danej komórki
		for (int i = 0; i < punkty.size(); i++)
		{
			ilosc_zer = 0;
			for (int j = 0; j < punkty.size(); j++)
			{
				if (czy_zero[i][j])
				{
					ilosc_zer++;
				}
				else
				{
					wyst_zer[i][j] = std::numeric_limits<double>::infinity();
				}
			}
			for (int j = 0; j < punkty.size(); j++)
			{
				if (czy_zero[i][j])
				{
					wyst_zer[i][j] += double(ilosc_zer - 1);
				}
			}
			ilosc_zer = 0;
			for (int j = 0; j < punkty.size(); j++)
			{
				if (czy_zero[j][i])
				{
					ilosc_zer++;
				}
			}
			for (int j = 0; j < punkty.size(); j++)
			{
				if (czy_zero[j][i])
				{
					wyst_zer[j][i] += double(ilosc_zer - 1);
				}
			}
		}


		//znalezienie komórki z minimaln¹ ilosci¹ zer w kolumnie i wierszu od tej komorki
		double min_zer = std::numeric_limits<double>::infinity(); // minimalna iloœc widzianych zer
		int pomoc_i = 0, pomoc_j = 0;
		for (int i = 0; i < punkty.size(); i++)
		{
			for (int j = 0; j < punkty.size(); j++)
			{
				if (wyst_zer[i][j] < min_zer)
				{
					min_zer = wyst_zer[i][j];
					pomoc_j = j;
					pomoc_i = i;

				}
			}
		}
		//przeslanie numerow punktow znalezionej wyzej komorki do tablicy wynikowej


		//sprawdzenie czy dane po³¹czenie nie jest dublowane
		bool czy_jest = false;
		for (auto& el : wynik)
		{
			if (el.first.second == numerowanie_punktow[pomoc_i] && el.first.first == numerowanie_punktow[pomoc_j])
				czy_jest = true;
		}
		//przeslanie numerow punktow znalezionej wyzej komorki do tablicy wynikowej
		if(!czy_jest)
		wynik.push_back({ { numerowanie_punktow[pomoc_i],numerowanie_punktow[pomoc_j]}, odleglosci[{numerowanie_punktow[pomoc_i],numerowanie_punktow[pomoc_j]}]});

		//usuwanie wszystkich widzianych zer w kolumnie i wierszu od komorki odnalezionej wyzej

		for (int z = 0; z < punkty.size(); z++)
		{
			czy_zero[pomoc_i][z] = 0;
			czy_zero[z][pomoc_j] = 0;
		}
	}



	return wynik;
}

Graph rekonstrukcja_trasy(Graph graph, std::vector<std::pair<std::pair<std::string, std::string>, double>> pary)
{
	std::map<std::string, int> numerowanie_punktow_string;
	std::map<int, std::string> numerowanie_punktow_int;
	std::vector<std::vector<double>> odleglosci;
	std::vector<std::vector<int>> wartosci;
	int licznik = 0;
	//numerowanie danych punktów
	for (const auto& el : graph)
	{
		numerowanie_punktow_string[el.first] = licznik;
		licznik++;
		numerowanie_punktow_int[numerowanie_punktow_string[el.first]] = el.first;
	}
	//uzupe³nianie tablicy odleg³oœci oraz wartoœci (poprzedników)
	for (int i = 0; i < licznik ; i++)
	{
		std::vector<double> pomoc1;
		std::vector<int>pomoc2;
		for (int j = 0; j < licznik ; j++)
		{
			if (i == j)
			{
				pomoc1.push_back(0.0);
			}
			else
			{
				pomoc1.push_back(std::numeric_limits<double>::infinity());
			}
			pomoc2.push_back(-1);
		}
		odleglosci.push_back(pomoc1);
		wartosci.push_back(pomoc2); // wszystkie wartoœci na -1

	}
	//nadawanie odleg³oœci miêdzy po³¹czonymi punktami
	for (const auto& el : graph)
	{
		for (const auto& el2 : el.second)
		{
			odleglosci[numerowanie_punktow_string[el.first]][numerowanie_punktow_string[el2.first.first]] = el2.first.second;
		}
	}


	//ustalanie punktów pocz¹tkowych przejœcia w wartoœciach
	for (int i = 0; i < licznik; i++)
	{
		for (int j = 0; j < licznik; j++)
		{
			if (i == j)
				continue;
			if (odleglosci[i][j] < std::numeric_limits<double>::infinity())
			{
				wartosci[i][j] = i;
			}
		}
	}
	
		
		for (int k = 0; k < licznik; k++) //k-ty punkty
		{
			for (int i = 0; i < licznik; i++)
			{
				for (int j = 0; j < licznik; j++)
				{
					if (odleglosci[i][j] > odleglosci[i][k] + odleglosci[k][j]) // czy odl (i->j) > odl(i->l) + odl(k->j)
					{
						odleglosci[i][j] = odleglosci[i][k] + odleglosci[k][j]; //odl(i->j) = -||-
						wartosci[i][j] = wartosci[k][j];						//aby dojœc do i trzeba przjeœæ przez k
					}
				}
			}
		}
	
		//odnajdywanie najszybszej œcie¿ki z punkty (poczatek) do punkty (koniec)
		for (const auto& el : pary)
		{
			std::vector<std::string> trasa;
			std::string poczatek = el.first.first, koniec = el.first.second;
			int pom_1 = numerowanie_punktow_string[poczatek], pom_2 = numerowanie_punktow_string[koniec];
			
			while (true)
			{
				trasa.push_back(numerowanie_punktow_int[pom_2]);
				pom_2 = wartosci[pom_1][pom_2];
				if (pom_2 == pom_1)
				{
					trasa.push_back(numerowanie_punktow_int[pom_2]);
					break;
				}
					
			}
	
			//dublowanie znalezionej (najszybszej) trasy
			for (int i = 0 ; i < trasa.size() - 1; i++)			
			{
				
				std::string p1 = trasa[i], p2 = trasa[i + 1];
				for (const auto& el : graph.at(p1))
				{
					
					if (el.first.first == p2)
					{
						graph[p1].push_front({ {p2,el.first.second},el.second });
						graph[p2].push_front({ {p1,el.first.second},el.second });
					}
				}
			}
		}
	return graph;
	
}

std::vector<std::pair<std::string, std::string>> Flurry(Graph graph, std::string punkt)
{
	std::vector<std::pair<std::string,std::string>> wynik;
	std::string node, node_2;
	std::map<std::string, std::vector<std::string>> pary;
	std::vector<std::string> pary_node, pary_node2;
	int pomoc_1 = 0, pomoc_2 = 0;
	//pobieranie po³¹czeñ z grafu i przesy³anie ich do par
	for (const auto& el : graph)
	{
		std::vector<std::string> pomoc;
		for (const auto& el2 : graph.at(el.first))
		{
			node = el.first;
			pomoc.push_back(el2.first.first);
		}
		pary[node] = pomoc;
	}
	node = punkt; // pocz¹tkowy punkt
	for (int i = 0; i < 10; i++)
	{
		//odnajdowanie punkty node
		for (const auto& el : pary)
		{
			if (el.first == node)
			{

				pary_node = el.second;
				for (int i = 0; i < pary_node.size(); i++)
				{
					//pobieranie kolejnego punktu po³¹czonego z node (node_2)
					node_2 = pary_node[i];
					//usuwanie po³¹czenia miêdzy node a node_2
					pary_node.erase(pary_node.begin() + i);
					pary[el.first] = pary_node;
					//usuwanie po³¹czenia miêdzy node_2 a node
					pary_node2 = pary[node_2];
					for (int i = 0; i < pary_node2.size(); i++)
					{
						if (pary_node2[i] == node)
						{
							pary_node2.erase(pary_node2.begin() + i);
							break;
						}
					}
					pary[node_2] = pary_node2;
					//zliczanie do ilu maksymalnie miejsc mo¿na dostaæ siê z danego punktu
					pomoc_1 = ile_widzi(pary, node);
					pomoc_2 = ile_widzi(pary, node_2);

					
					if (pomoc_1 > pomoc_2) // przywracamy trasê i przechodzimy do sprawdzania nastêpnego punktu
					{
						pary_node.insert(pary_node.begin(), node_2);
						pary[node] = pary_node;
						pary_node2.insert(pary_node2.begin(), node);
						pary[node_2] = pary_node2;
						continue;
					}
					else // przechodzimy do danego punktu
					{
						wynik.push_back({ node, node_2 });
						//std::cout << node << " " << node_2 << std::endl;
						node = node_2;
						break;

					}
				}
			}
			
			
		}

	}

	return wynik;
}

void wypisz_wynik(std::vector<std::pair<std::string, std::string>> wynik, Graph graph, std::string plik_wyjsciowy)
{
	std::ofstream z(plik_wyjsciowy);
	std::string node;
	for (const auto& el : wynik)
	{
		for (const auto& el2 : graph.at(el.first))
		{
			if (el2.first.first == el.second)
			{
				z << el.first << " " << el2.first.first << " " << el2.second << std::endl;
				break;
			}
		}
	}
}

int ile_widzi(std::map<std::string, std::vector<std::string>> pary, std::string node)
{
	int suma = 0;
	std::set<std::string> wynik{ node };
	std::list<std::string> punkty{ node };

	while (!punkty.empty())
	{
		for (const auto& el : pary.at(punkty.front()))
		{
			if (wynik.count(el) == 0)
			{
				wynik.insert(el);
				punkty.push_back(el);
			}
		}
		punkty.pop_front();
	}

	return wynik.size() - 1;

}
