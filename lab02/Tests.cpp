#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {

  unsigned int sequenceLen = 8;

  srand(time(NULL));

  std::vector<unsigned int> sequence = Graph::makeRandomDegreeSequence(sequenceLen);
  //std::vector<unsigned  int> sequence = {2, 2, 1, 1, 0};

  while (!Graph::isDegreeSequence(sequence)) sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  std::cout << "Found good sequence!" << std::endl;

  for (unsigned int i=0; i<sequence.size(); ++i) std::cout << sequence[i] << " ";
  std::cout << std::endl << std::endl;

  std::cout << "Generating random graph..." << std::endl << std::endl;
  Graph randomGraph(Undirected);
  int a, b;
  randomGraph.generateRandomNP(8, 12, 5, 10, a, b);

  std::cout << "Adjacency list:" << std::endl;
  randomGraph.convertMatrix(AdjacencyList);
  randomGraph.print();

  std::cout << std::endl << "Finding separate components..." << std::endl;
  std::vector<unsigned int> components = randomGraph.findComponents();
  std::cout << "Nodes numbered by components:" << std::endl;
  for (unsigned int i = 0; i < components.size(); i++)
    std::cout << components[i] << " ";
  std::cout << std::endl << std::endl;

  std::cout << "Biggest component consists of the following nodes:" << std::endl;
  std::vector<unsigned int> biggestComp = randomGraph.biggestComponent();
  for (unsigned int i = 0; i < biggestComp.size(); i++)
    std::cout << biggestComp[i] << " ";
  std::cout << std::endl;
}
