#include "Graph.h"
#include <iostream>

int main() {
  // ADJACENCY LIST GRAPH
  std::cout << "ADJACENCY LIST GRAPH" << std::endl << std::endl;
  std::cout << "Creating adjacency list graph..." << std::endl;
  Graph adjacencyListGraph;

  std::cout << "Reading adjacency list from file:" << std::endl;
  adjacencyListGraph.readFile("adjlist.txt");
  adjacencyListGraph.print()
  std::cout << std::endl;

  std::cout << "Converting adjacency list to adjacency matrix:" << std::endl;
  adjacencyListGraph.convertMatrix(AdjacencyMatrix);
  adjacencyListGraph.print()
  std::cout << std::endl;

  std::cout << "Converting adjacency matrix to adjacency list:" << std::endl;
  adjacencyListGraph.convertMatrix(AdjacencyList);
  adjacencyListGraph.print()
  std::cout << std::endl;

  std::cout << "Saving graph to file graph.txt..." << std::endl;
  adjacencyListGraph.saveGraph("graph.txt")
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;
}
