#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
  srand(time(NULL));

  // DIRECTED GRAPHS
  std::cout << "DIRECTED GRAPHS" << std::endl;
  Graph directedRandomGraph(Directed);

  int vertices, probability;
  directedRandomGraph.generateRandomNP(6, 10, 5, 10, vertices, probability);
  std::cout << "Vertices: " << vertices << ", probability: " << probability << "%" << std::endl << std::endl;
  directedRandomGraph.print();
  std::cout << "\nSaving graph to directedRandomGraph.txt" << std::endl;
  directedRandomGraph.saveGraph("directedRandomGraph.txt");

  std::cout << std::endl << std::endl;
}
