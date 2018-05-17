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
    connectedGraph.generateRandomNL(7, 10, 12, 17, vertices, edges);
  } while (connectedGraph.biggestComponent().size() < connectedGraph.getVertexCount());

  std::cout << "Found a graph with " << vertices << " vertices and " << edges << " edges" << std::endl;
  std::cout << std::endl << "Adjacency list: " << std::endl;
  connectedGraph.convertMatrix(AdjacencyList);
  connectedGraph.print();
  std::cout << std::endl;

  // Generating random weights
  connectedGraph.generateRandomWeights(1, 10);
  connectedGraph.printWeights();

  // DIJKSTRA
  std::cout << std::endl << "DIJKSTRA" << std::endl;
  unsigned int startVertex=Graph::intRand(0, connectedGraph.getVertexCount()-1);
  std::cout << "Finding shortest path distances from vertex " << startVertex+1 << " to every other vertex..." <<std::endl;
  connectedGraph.Dijkstra(startVertex, true);
}
