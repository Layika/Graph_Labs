#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Node.h"

class Graph
{
private:
    Node** nodes; //lista wezlow w grafie
    int nodeNum; //liczba wezlow
public:
    Graph() {nodeNum = 0; nodes = new Node*[0]; srand(time(NULL));}
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

    std::string generateAdjMatrix();//zwraca macierz sasiedztw (w takim formacie jak w generateFromAdjMatrix)

    void generateFromIncMatrix(std::string _data);//tworzy graf z macierzy incydencji zawartej w _data. Przyklad w "macierz incydencji.txt"

    std::string generateIncMatrix();//zwraca macierz incydencji (w takim formacie jak w generateFromIncMatrix)

    void generateRandomByProbability(int _n, float _p);//generator losowy typu G(n, p)
    void generateRandomByAdjaciencies(int _n, int _l);//generator losowy tyou G(n, l)


    /*
    Tu sie powinny pojawic takie metody:
    1. [ZROBIONE] metoda uzupelniajaca liste wezlow na podstawie podanej przez uzytkownika listy sasiedztwa.
    2. [ZROBIONE] metoda uzupelniajaca liste wezlow na podstawie tabelki typu wezel x wezel (macierz sasiedztwa)
    3. [ZROBIONE] metoda uzupelniajaca liste wezlow na podstawie tabelki typu wezel x krawedz (macierz incydencji)
    4. [ZROBIONE] metoda tworzaca liste sasiedzta na podstawie wezlow w nodes
    5. [ZROBIONE] metoda tworzaca tabelke typu wezel x wezel na podstawie wezlow w nodes
    6. [ZROBIONE] metoda tworzaca tabelke typu wezel x krawedz na podstawie wezlow w nodes
    7. [ZROBIONE] losowy generator grafow typu G(n, p)
    8. [ZROBIONE] losowy generator grafow typu G(n, l)
    9. na koniec jakas metoda ktora zajmie sie graficznym przedstawieniem grafu. Moze byc na zasadzie tworzenia takiego skryptu, jaki nam Wach pokazala
    (ja sie na tym nie znam wiec help appreciated)
    */
};
