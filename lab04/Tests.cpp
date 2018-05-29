#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
  srand(time(NULL));

  // DIRECTED GRAPHS
  std::cout << "DIRECTED GRAPHS" << std::endl;
  Graph directedRandomGraph(Directed);

  int minVertices = 10;
  int maxVertices = 10;
  int minProbability = 20;
  int maxProbability = 40;

  int chosenVertices, chosenProbability;
  directedRandomGraph.generateRandomNP(minVertices, maxVertices, minProbability, maxProbability, chosenVertices, chosenProbability);

  std::cout << "Vertices: " << chosenVertices << ", probability: " << chosenProbability << "%" << std::endl << std::endl;

  directedRandomGraph.print();

  std::cout << "\nSaving graph to directedRandomGraph.txt" << std::endl;
  directedRandomGraph.saveGraph("directedRandomGraph.txt");

  std::cout << std::endl << std::endl;


  // STRONGLY CONNECTED COMPONENTS
  std::cout << "STRONGLY CONNECTED COMPONENTS" << std::endl;
  std::vector<int> components = directedRandomGraph.Kosaraju();
  std::cout << std::endl << std::endl;

  //BELLMAN FORD
  Graph example(Directed);
  example.readFile("example_bellman_ford.txt");
  example.print();
  example.generateRandomWeights(-5, 10);
  example.setWeight(1,2,-1);
  example.setWeight(1,3,-4);
  example.setWeight(2,1,4);
  example.setWeight(3,2,2);
  example.printWeights();
  unsigned int startVertex=Graph::intRand(0, example.getVertexCount()-1);
  std::cout << "Finding shortest path distances from vertex " << startVertex+1 << " to every other vertex..." <<std::endl<<std::endl;
  std::vector<int> v=example.BellmanFord(startVertex);

  example.Johnson();





}
