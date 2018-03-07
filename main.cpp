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

    Graph* graf2 = new Graph;
    ifstream inFile;
    inFile.open("lista sasiedztwa.txt", ios::in);
    stringstream fileContent;
    fileContent << inFile.rdbuf();
    graf2->generateFromAdjList(fileContent.str());
    inFile.close();
    graf2->print();
}
