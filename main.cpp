#include "Node.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/*
ZAZNACZAM ZE TEN CALY PLIK SLUZYL MI TYLKO DO TESTOW, WIEC NIE ZWRACAJCIE UWAGI NA POLSKIE NAZWY ZMIENNYCH/OBIEKTOW
BO W FINALNM PROGRAMIE ICH NIE BEDZIE.
*/

int main()
{
    //tworzymy wezly
    Node* wezel1 = new Node(1);
    Node* wezel2 = new Node(2);
    Node* wezel3 = new Node(3);

    //wypisujemy ich identyfikatury i wezly do nich przylegle (obecnie brak)
    wezel1->print();
    wezel2->print();
    wezel3->print();
    cout << endl;

    //tworzymy graf i umieszczamy w nim wezly
    Graph* graf = new Graph;
    graf->addNode(wezel1);
    graf->addNode(wezel2);
    graf->addNode(wezel3);
    graf->addNode(wezel1); //ten wezel juz jest w grafie, wiec nie zostaje dodany

    //tworzymy jednostronne polaczenie z wezla 1 do 2
    wezel1->addAdj(wezel2, false);

    //Sprawdzamy stany wezlow
    graf->print();

    //tworzymy dwustronne polaczenie wezla 1 i 3
    wezel3->addAdj(wezel1, true);

    //Sprawdzamy stany wezlow
    graf->print();

    cout << "Lista sasiadow wezla 1: " << endl;
    int liczbaSasiadow = wezel1->getAdjNum();
    int* sasiedzi = new int[liczbaSasiadow]; //przygotowujemy array w ktorym znajda sie identyfikatory wszystkich sasiadow wezla 1
    for(int i=0; i<liczbaSasiadow; i++) sasiedzi[i] = (*wezel1)[i];
    for(int i=0; i<liczbaSasiadow; i++) cout << sasiedzi[i] << " "; //wypisujemy powstala liste
    cout <<endl;

    //tu jest wczytywanie grafu z pliku z lista sasiedztwa i wyswietlenie go
    Graph* graf2 = new Graph;
    ifstream inFile;
    inFile.open("lista sasiedztwa.txt", ios::in);
    stringstream fileContent;
    fileContent << inFile.rdbuf();
    graf2->generateFromAdjList(fileContent.str());
    inFile.close();
    graf2->print();
    cout << graf2->generateAdjList() << endl;//utworzenie i wyswietlenie listy sasiedztwa z nodes

    //tu jest wczytywanie grafu z pliku z macierza sasiedztwa i wyswietlenie go
    Graph* graf3 = new Graph;
    inFile.open("macierz sasiedztwa.txt", ios::in);
    stringstream fileContent2;
    fileContent2 << inFile.rdbuf();
    graf3->generateFromAdjMatrix(fileContent2.str());
    inFile.close();
    graf3->print();
    cout << graf3->generateAdjMatrix() << endl;//utworzenie i wyswietlenie mecierzy sasiedztwa z nodes

    //tu jest wczytywanie grafu z pliku z macierza incydencji i wyswietlenie go
    Graph* graf4 = new Graph;
    inFile.open("macierz incydencji.txt", ios::in);
    stringstream fileContent3;
    fileContent3 << inFile.rdbuf();
    graf4->generateFromIncMatrix(fileContent3.str());
    inFile.close();
    graf4->print();
    cout << graf4->generateIncMatrix() << endl;//utworzenie i wyswietlenie mecierzy incydencji z nodes

    //generowanie losowego grafu wedlug prawdopodobienstwa G(n, p) i wyswietlenie go we wszystkich mozliwych postaciach
    cout << "Losowy graf G(n, p):" << endl << endl;
    Graph* graf5 = new Graph;
    graf5->generateRandomByProbability(5, 0.2);
    graf5->print();
    cout << graf5->generateAdjList() << endl << graf5->generateAdjMatrix() << endl << graf5->generateIncMatrix() << endl;

    //generowanie losowego grafu wedlug liczby krawedzi G(n, l) i wyswietlenie go we wszystkich mozliwych postaciach
    cout << "Losowy graf G(n, l):" << endl << endl;
    Graph* graf6 = new Graph;
    graf6->generateRandomByAdjaciencies(5, 20);
    graf6->print();
    cout << graf6->generateAdjList() << endl << graf6->generateAdjMatrix() << endl << graf6->generateIncMatrix() << endl;
}
