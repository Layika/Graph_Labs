#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
  srand(time(NULL));

  std::cout << "Generating random connected graph..." << std::endl;
  Graph connectedGraph(Undirected);
  int vertices, edges;
  do {
    // If the biggest component is as big as the entire graph, then the entire graph is connected
    // So just keep generating random graphs until we find one that is connected
    connectedGraph.generateRandomNL(5, 8, 10, 15, vertices, edges);
  } while (connectedGraph.biggestComponent().size() < connectedGraph.getVertexCount());

  std::cout << "Found a graph with " << vertices << " vertices and " << edges << " edges" << std::endl;
  std::cout << std::endl << "Incidence matrix: " << std::endl;
  connectedGraph.convertMatrix(IncidenceMatrix);
  connectedGraph.print();

  connectedGraph.generateRandomWeights(1, 10);
  connectedGraph.printWeights();
}
