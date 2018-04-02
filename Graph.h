#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
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
    void print(); //wypisuje wszystkie wezly (w postaci listy sasiedztwa)
    void buildFromAdjList(std::string _data);//tworzy graf z listy sasiedztwa zawartej w _data. Przyklad w "lista sasiedztwa.txt"
    std::string generateAdjList(); //zwraca liste sasiedztw (w takim formacie jak w buildFromAdjList)
    void buildFromAdjMatrix(std::string _data);//tworzy graf z macierzy sasiedztwa zawartej w _data. Przyklad w "macierz sasiedztwa.txt"
    std::string generateAdjMatrix();//zwraca macierz sasiedztw (w takim formacie jak w buildFromAdjMatrix)
    void buildFromIncMatrix(std::string _data);//tworzy graf z macierzy incydencji zawartej w _data. Przyklad w "macierz incydencji.txt"
    std::string generateIncMatrix();//zwraca macierz incydencji (w takim formacie jak w buildFromIncMatrix)
    void buildRandomByProbability(int _n, float _p);//generator losowy typu G(n, p)
    void buildRandomByAdjaciencies(int _n, int _l);//generator losowy tyou G(n, l)
    void generateGnuplotScript(std::string fileName);//tworzy skrypt do gnuplota, ktory z kolei generuje plik graficzny graf.png z grafem
};
