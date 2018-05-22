#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
  srand(time(NULL));

  // DIRECTED GRAPHS
  std::cout << "DIRECTED GRAPHS" << std::endl;
  Graph directedRandomGraph(Directed);

  int minVertices = 6;
  int maxVertices = 10;
  int minProbability = 5;
  int maxProbability = 10;

  int chosenVertices, chosenPprobability;
  directedRandomGraph.generateRandomNP(minVertices, maxVertices, minProbability, maxProbability, chosenVertices, chosenProbability);

  std::cout << "Vertices: " << chosenVertices << ", probability: " << chosenProbability << "%" << std::endl << std::endl;
  
  directedRandomGraph.print();
  std::cout << "\nSaving graph to directedRandomGraph.txt" << std::endl;
  directedRandomGraph.saveGraph("directedRandomGraph.txt");

  std::cout << std::endl << std::endl;
}
