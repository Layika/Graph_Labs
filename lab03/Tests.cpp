#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
  srand(time(NULL));

  // RANDOM CONNECTED Graph
  std::cout << "RANDOM CONNECTED GRAPH" << std::endl;
  std::cout << "Generating random connected graph..." << std::endl;
  Graph connectedGraph(Undirected);
  int vertices, edges;
  do {
    // If the biggest component is as big as the entire graph, then the entire graph is connected
    // So just keep generating random graphs until we find one that is connected
    connectedGraph.generateRandomNL(7, 10, 2, 7, vertices, edges);
  } while (connectedGraph.biggestComponent().size() < connectedGraph.getVertexCount());

  std::cout << "Found a graph with " << vertices << " vertices and " << edges << " edges" << std::endl;
  std::cout << std::endl << "Adjacency list: " << std::endl;
  connectedGraph.convertMatrix(AdjacencyList);
  connectedGraph.print();
  std::cout << std::endl;

  // Generating random weights
  connectedGraph.generateRandomWeights(1, 10);
  connectedGraph.printWeights();
  std::cout << std::endl;

  // DIJKSTRA
  std::cout << "DIJKSTRA" << std::endl;
  unsigned int startVertex=Graph::intRand(0, connectedGraph.getVertexCount()-1);
  std::cout << "Finding shortest path distances from vertex " << startVertex+1 << " to every other vertex..." <<std::endl;
  connectedGraph.Dijkstra(startVertex, true);

  //DISTANCE MATRIX, CENTER AND MINIMAX CENTER OF THE GRAPH
  std::cout << "DISTANCE MATRIX, CENTER AND MINIMAX CENTER OF THE GRAPH" << std::endl;
  connectedGraph.min_distances();
  std::cout << std::endl;

  // MINIMUM SPANNING TREE
  std::cout << "MINIMUM SPANNING TREE" << std::endl;
  connectedGraph.primMST();

  std::cout << "\n\nTest graph:" << std::endl;
  Graph testGraph(Undirected);
  testGraph.readFile("sample_input_data/mst.txt");
  testGraph.createWeights();

  // Set weights in a graph
  /*
              2    3
          (0)--(1)--(2)
           |   / \   |
          6| 8/   \5 |7
           | /     \ |
          (3)-------(4)
                9              */
  testGraph.setWeight(1, 2, 2);
  testGraph.setWeight(1, 4, 6);
  testGraph.setWeight(2, 3, 3);
  testGraph.setWeight(2, 4, 8);
  testGraph.setWeight(2, 5, 5);
  testGraph.setWeight(3, 5, 7);
  testGraph.setWeight(4, 5, 9);

  testGraph.primMST();
}
