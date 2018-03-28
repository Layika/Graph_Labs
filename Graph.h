#ifndef H_GRAPH
#define H_GRAPH

#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"

class Graph
{
private:
    Node** nodes; //lista wezlow w grafie
    int nodeNum; //liczba wezlow
public:
    Graph() {nodeNum = 0; nodes = new Node*[0];}
    ~Graph();
    void addNode(Node* _node); //Dodaje wezel do grafu. jesli w grafie istnieje juz wezel o takim samym ID jak _node, to nic nie robi
    Node* getNodeByID(int _ID); //Zwraca wskaznik do wezla o podanym _ID. NULL jesli takiego nie ma.
    void print();

    void generateFromAdjList(std::string _data);
    /*tworzy graf z listy sasiedztwa. _data jest blokiem tekstu z lista. Musi miec naglowek AdjList. Przykladowe _data:
    AdjList
    1 - 2 3
    2 - 1*/

    std::string generateAdjList(); //zwraca liste sasiedztw (w takim formacie jak wyzej)

    void generateFromAdjMatrix(std::string _data);
    /*tworzy graf z macierzy sasiedztwa. _data to blok tekstu. Musi miec naglowek AdjMatrix. Przykladowe dane w pliku "macierz sasiedztwa.txt".
    Poszczegolne wartosci musza byc oddzielane tabulacjami!*/


    /*
    Tu sie powinny pojawic takie metody:
    1. [ZROBIONE] metoda uzupelniajaca liste wezlow na podstawie podanej przez uzytkownika listy sasiedztwa.
    2. [ZROBIONE] metoda uzupelniajaca liste wezlow na podstawie tabelki typu wezel x wezel (macierz sasiedztwa)
    3. metoda uzupelniajaca liste wezlow na podstawie tabelki typu wezel x krawedz (macierz incydencji)
    4. [ZROBIONE] metoda tworzaca liste sasiedzta na podstawie wezlow w nodes
    5. metoda tworzaca tabelke typu wezel x wezel na podstawie wezlow w nodes
    6. metoda tworzaca tabelke typu wezel x krawedz na podstawie wezlow w nodes
    7. na koniec jakas metoda ktora zajmie sie graficznym przedstawieniem grafu. Moze byc na zasadzie tworzenia takiego skryptu, jaki nam Wach pokazala
    (ja sie na tym nie znam wiec help appreciated)
    */
};

#endif // H_GRAPH