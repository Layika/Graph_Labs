#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
  srand(time(0));

  // DIRECTED GRAPHS
  std::cout << "RANDOM FLOW NETWORK" << std::endl << std::endl;
  Graph flowNetwork(Undirected);
  unsigned int numOfLayers = Graph::intRand(2, 4);
  flowNetwork.randomFlowNetwork(numOfLayers);
  std::cout << "A random flow network with " << numOfLayers << " layers has been generated." << std::endl;
  std::cout << "Adjacency matrix: " << std::endl << std::endl;
  flowNetwork.printFlowNetwork();
  std::cout << std::endl;

  flowNetwork.gnuplotFlowNetwork("flowNetwork.plt");
  std::cout << std::endl << "Ready to plot" << std::endl << std::endl;

  std::cout << "GENERATING CAPACITY VALUES" << std::endl;
  flowNetwork.generateRandomCapacities(1, 10);
  flowNetwork.printFlowsAndCapacities();
    flowNetwork.saveGraph("flow.txt");
    flowNetwork.FordFulkerson();
}
