#include "Graph.h"

int main() {
  Graph g;
  g.readFile("adjmatrix.txt");
//  g.convertMatrix(IncidenceMatrix);
//  g.print();
//  std::cout << std::endl << std::endl;
  g.convertMatrix(AdjacencyList);
    g.print();
  g.convertMatrix(IncidenceMatrix);
  g.print();
  g.convertMatrix(AdjacencyList);
    g.print();

//  g.readFile("incmatrix.txt");
//  g.print();
//  g.convertMatrix(AdjacencyMatrix);
//  g.print();
//  g.convertMatrix(IncidenceMatrix);
//  g.print();
}
