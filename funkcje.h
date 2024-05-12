/** @file */
//deklaracje (nag��wki plik�w)

#ifndef FUNKCJE_H
#define FUNKCJE_H
typedef std::map<std::string, std::list<std::pair<std::pair<std::string, double >, std::string>>> Graph;

/**
* @param FileName nazwa pliku z danymi
* @return Graf, utworzony z parametr�w podanych w pliku wej�ciowym
*/
Graph LoadFromFile(const std::string&FileName);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @param graph_pomoc tablica zawieraj�ca wszystkie punkty, do kt�rych mo�na dotrze� w danym grafie
* @return zwraca warto�� boolean, w zale�no�ci od tego czy graf jest sp�jny
*/
bool czy_sp(Graph graph, std::set<std::string> graph_pomoc);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @return tablica zawieraj�ca wszystkie punkty, do kt�rych mo�na dotrze� w danym grafie
*/
std::set<std::string> BFS(const Graph& graph);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @return lista zawieraj�ca wszystkie punkty, posiadaj�ce nieparzyst� ilo�� po��cze�
*/
std::list<std::string> nieparzyste_punkty(const Graph& graph);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @param node punkt w zale�no�ci od kt�rego wyliczana b�dzie najkr�tsza odleg�o�� do pozosta�ych
* @return mapa punkt�w i najkr�tszych odleg�o�ci, kt�re trzeba pokona�, aby do nich dotrze�
*/
std::map<std::string, double> dijkstry(Graph graph, std::string node);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @param lista lista wszystkich znajduj�cych si� w grafie punkt�w, zawieraj�cych nieparzyst� ilo�� po��cze�
* @return tablica zawieraj�ca wszystkie kombinacje par oraz odleg�o�ci mi�dzy nimi, jakie mo�na utworzy� z listy punkt�w 
*/
std::vector<std::pair<std::pair<std::string, double>, std::string>> Wyszuk_niep_pary(Graph graph, std::list<std::string> lista);
/**
* @param pary tablica zawieraj�ca wszystkie mo�liwe pary, kt�re mo�na utworzy� z punkt�w zawieraj�cych nieparzyst� ilo�� po��cze� w grafie wej�ciowym 
* @param punkty wszystkie punkty grafu, posiadaj�ce nieparzyst� ilo�� po��cze�
* @return tablica zawieraj�ca wszystkie punkty po��czone w unikatowe pary punkt�w, dla kt�rych suma odleg�o�ci mi�dzy punktami w parach jest najmniejsza
*/
std::vector<std::pair<std::pair<std::string, std::string>, double>> Najlkrtosze_Pary(std::vector<std::pair<std::pair<std::string, double>, std::string>> pary, std::list<std::string> punkty);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @param pary pary punkt�w, dla kt�rych najkr�tsze trasy mi�dzy nimi musza zosta� zdublowane 
* @return wej�ciowy graf w kt�rym zdublowane zosta�y trasy mi�dzy podanymi parami
*/
Graph rekonstrukcja_trasy(Graph graph, std::vector<std::pair<std::pair<std::string, std::string>, double>> pary);
/**
* @param pary graf zawieraj�cy po��czenia mi�dzy punktami
* @param node punkt pocz�tkowy
* @return maksymalna ilo�� punkt�w, do kt�rych mo�na dotrze�, rozpoczynaj�c tras� w punkcie node
*/
int ile_widzi(std::map<std::string, std::vector<std::string>> pary, std::string node);
/**
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @param punkt punkt pocz�tkowy, w kt�rym listonosz rozpoczyna tras�
* @return mapa zawieraj�ca tras�, jak� listonosz musi przeby�, aby przej�� przez wszystkie punkty i powr�ci� na pocz�tek
*/
std::vector<std::pair<std::string, std::string>> Flurry(Graph graph, std::string punkt);
/**
* @param wynik mapa zawieraj�ca tras�, jak� listonosz musi przeby�, aby przej�� przez wszystkie punkty i powr�ci� na pocz�tek
* @param graph graf, utworzony z punkt�w zawartych w pliku wej�ciowym
* @return dane do pliku wyj�ciowego, sk�adaj�ce si� z punkt�w oraz nazw ulic, przez kt�re si� przemieszczamy
*/
void wypisz_wynik(std::vector<std::pair<std::string, std::string>> wynik, Graph graph, std::string);


#endif