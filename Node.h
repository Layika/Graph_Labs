#pragma once

#include <iostream>

class Node
{
private:
    int ID;
    Node** adj; //lista przyleglych wezlow
    int adjNum; //liczba przyleglosci/krawedzi
public:
    Node(int _ID) : ID(_ID) {adjNum = 0; adj = new Node*[0];} //konstruktor przypisujacy wezlu identyfikator ID
    ~Node();
    operator int() {return ID;} //operator int zeby wygodnie odczytywac ID wezla
    int operator[] (int i) {return adj[i]->ID;} //operator [i] zwraca ID i-tego przyleglego (sasiedniego) wezla
    int getAdjNum() {return adjNum;}
    bool isAdj(Node* _node); //zwraca true gdy _node jest sasiadem (sprawdza tylko w jedna strone)
    void addAdj(Node* _node, bool viceVersa); //przylacza wezel _node. Jesli viceVersa == true to polaczenie jest dwustronne
    void print();
};
