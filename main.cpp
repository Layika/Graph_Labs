#include "Node.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void genRandomNL(Graph* _graph)
{
    int n, l;
    cout << "Liczba wierzcholkow n: ";
    cin >> n;
    cout << "Liczba krawedzi l: ";
    cin >> l;
    _graph->buildRandomByAdjaciencies(n, l);
    cout << endl;
    _graph->print();
}

void genRandomNP(Graph* _graph)
{
    int n;
    float p;
    cout << "Liczba wierzcholkow n: ";
    cin >> n;
    cout << "Prawdopodobienstwo sasiedztwa [0 - 1]: ";
    cin >> p;
    _graph->buildRandomByProbability(n, p);
    cout << endl;
    _graph->print();
}

void readFromFile(Graph* _graph)
{
    string fileName;
    cout << "Nazwa pliku: ";
    cin.ignore();
    getline(cin, fileName);
    if(fileName.length() == 0) {cout << "Nie mozna odczytac pliku" << endl; return;}
    ifstream inFile;
    inFile.open(fileName, ios::in);
    stringstream fileContent;
    fileContent << inFile.rdbuf();
    string fileData = fileContent.str();
    if(fileData.length() == 0) cout << "Nie mozna odczytac pliku" << endl;
    else if(fileData.substr(0, 7) == "AdjList") _graph->buildFromAdjList(fileData);
    else if(fileData.substr(0, 9) == "AdjMatrix") _graph->buildFromAdjMatrix(fileData);
    else if(fileData.substr(0, 9) == "IncMatrix") _graph->buildFromIncMatrix(fileData);
    else cout << "Nieznany typ pliku" << endl;
    cout << endl;
    _graph->print();
    inFile.close();
}

void saveAdjList(Graph* _graph)
{
    string saveData = _graph->generateAdjList();
    FILE* file = fopen("ls.txt", "w");
    fprintf(file, "%s", saveData.c_str());
    cout << "Zapisano do \"ls.txt\"" << endl;
    fclose(file);
}

void saveAdjMatrix(Graph* _graph)
{
    string saveData = _graph->generateAdjMatrix();
    FILE* file = fopen("ms.txt", "w");
    fprintf(file, "%s", saveData.c_str());
    cout << "Zapisano do \"ms.txt\"" << endl;
    fclose(file);
}

void saveIncMatrix(Graph* _graph)
{
    string saveData = _graph->generateIncMatrix();
    FILE* file = fopen("mi.txt", "w");
    fprintf(file, "%s", saveData.c_str());
    cout << "Zapisano do \"mi.txt\"" << endl;
    fclose(file);
}

void genGnuplotScript(Graph* _graph)
{
    _graph->generateGnuplotScript("graf.plt");
    cout << "Zapisano do \"graf.plt\"" << endl;
    cout << "Po uruchomieniu skryptu zostanie utworzony plik \"graf.png\"" << endl;
}

int main()
{
    int answer;
    Graph* graph = new Graph();
    do
    {
        cout << endl << "Menu: " << endl
        << "[1] Wygeneruj losowy graf G(n, l)" << endl
        << "[2] Wygeneruj losowy graf G(n, p)" << endl
        << "[3] Wczytaj graf z pliku" << endl
        << "[4] Zapisz liste sasiedztwa do pliku" << endl
        << "[5] Zapisz macierz sasiedztwa do pliku" << endl
        << "[6] Zapisz macierz incydencji do pliku" << endl
        << "[7] Wygeneruj skrypt gnuplot" << endl
        << "[0] Zakoncz" << endl << endl << "Wybor: ";
        cin >> answer;
        switch(answer)
        {
        case 0:
            break;
        case 1:
            genRandomNL(graph);
            break;
        case 2:
            genRandomNP(graph);
            break;
        case 3:
            readFromFile(graph);
            break;
        case 4:
            saveAdjList(graph);
            break;
        case 5:
            saveAdjMatrix(graph);
            break;
        case 6:
            saveIncMatrix(graph);
            break;
        case 7:
            genGnuplotScript(graph);
            break;
        default:
            cout << "Nie ma takiej opcji" << endl;
            break;
        }
    } while (answer != 0);
}
