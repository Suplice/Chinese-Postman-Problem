/** @file */
//deklaracje (nag³ówki plików)

#ifndef FUNKCJE_H
#define FUNKCJE_H
typedef std::map<std::string, std::list<std::pair<std::pair<std::string, double >, std::string>>> Graph;

/**
* @param FileName nazwa pliku z danymi
* @return Graf, utworzony z parametrów podanych w pliku wejœciowym
*/
Graph LoadFromFile(const std::string&FileName);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @param graph_pomoc tablica zawieraj¹ca wszystkie punkty, do których mo¿na dotrzeæ w danym grafie
* @return zwraca wartoœæ boolean, w zale¿noœci od tego czy graf jest spójny
*/
bool czy_sp(Graph graph, std::set<std::string> graph_pomoc);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @return tablica zawieraj¹ca wszystkie punkty, do których mo¿na dotrzeæ w danym grafie
*/
std::set<std::string> BFS(const Graph& graph);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @return lista zawieraj¹ca wszystkie punkty, posiadaj¹ce nieparzyst¹ iloœæ po³¹czeñ
*/
std::list<std::string> nieparzyste_punkty(const Graph& graph);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @param node punkt w zale¿noœci od którego wyliczana bêdzie najkrótsza odleg³oœæ do pozosta³ych
* @return mapa punktów i najkrótszych odleg³oœci, które trzeba pokonaæ, aby do nich dotrzeæ
*/
std::map<std::string, double> dijkstry(Graph graph, std::string node);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @param lista lista wszystkich znajduj¹cych siê w grafie punktów, zawieraj¹cych nieparzyst¹ iloœæ po³¹czeñ
* @return tablica zawieraj¹ca wszystkie kombinacje par oraz odleg³oœci miêdzy nimi, jakie mo¿na utworzyæ z listy punktów 
*/
std::vector<std::pair<std::pair<std::string, double>, std::string>> Wyszuk_niep_pary(Graph graph, std::list<std::string> lista);
/**
* @param pary tablica zawieraj¹ca wszystkie mo¿liwe pary, które mo¿na utworzyæ z punktów zawieraj¹cych nieparzyst¹ iloœæ po³¹czeñ w grafie wejœciowym 
* @param punkty wszystkie punkty grafu, posiadaj¹ce nieparzyst¹ iloœæ po³¹czeñ
* @return tablica zawieraj¹ca wszystkie punkty po³¹czone w unikatowe pary punktów, dla których suma odleg³oœci miêdzy punktami w parach jest najmniejsza
*/
std::vector<std::pair<std::pair<std::string, std::string>, double>> Najlkrtosze_Pary(std::vector<std::pair<std::pair<std::string, double>, std::string>> pary, std::list<std::string> punkty);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @param pary pary punktów, dla których najkrótsze trasy miêdzy nimi musza zostaæ zdublowane 
* @return wejœciowy graf w którym zdublowane zosta³y trasy miêdzy podanymi parami
*/
Graph rekonstrukcja_trasy(Graph graph, std::vector<std::pair<std::pair<std::string, std::string>, double>> pary);
/**
* @param pary graf zawieraj¹cy po³¹czenia miêdzy punktami
* @param node punkt pocz¹tkowy
* @return maksymalna iloœæ punktów, do których mo¿na dotrzeæ, rozpoczynaj¹c trasê w punkcie node
*/
int ile_widzi(std::map<std::string, std::vector<std::string>> pary, std::string node);
/**
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @param punkt punkt pocz¹tkowy, w którym listonosz rozpoczyna trasê
* @return mapa zawieraj¹ca trasê, jak¹ listonosz musi przebyæ, aby przejœæ przez wszystkie punkty i powróciæ na pocz¹tek
*/
std::vector<std::pair<std::string, std::string>> Flurry(Graph graph, std::string punkt);
/**
* @param wynik mapa zawieraj¹ca trasê, jak¹ listonosz musi przebyæ, aby przejœæ przez wszystkie punkty i powróciæ na pocz¹tek
* @param graph graf, utworzony z punktów zawartych w pliku wejœciowym
* @return dane do pliku wyjœciowego, sk³adaj¹ce siê z punktów oraz nazw ulic, przez które siê przemieszczamy
*/
void wypisz_wynik(std::vector<std::pair<std::string, std::string>> wynik, Graph graph, std::string);


#endif