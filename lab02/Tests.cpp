#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {

  srand(time(NULL));

  // DEGREE SEQUENCES
  // Make a random degree sequence and check if it can represent a graph
  unsigned int sequenceLen = 7;

  std::vector<unsigned int> sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  while (!Graph::isDegreeSequence(sequence)) sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  std::cout << "Found a good sequence!" << std::endl;
  std::sort(sequence.rbegin(), sequence.rend());
  for (unsigned int i=0; i<sequence.size(); ++i) std::cout << sequence[i] << " ";
  std::cout << std::endl;

  std::cout << std::endl;

 /*

  // RANDOM K-REGULAR GRAPHS
  std::cout << "Generating a regular graph..." << std::endl;
  Graph regularGraph(Undirected);

  unsigned int minVertices = 2;
  unsigned int maxVertices = 4;
  unsigned int neighbours = 1;
  regularGraph.generateRandomRegular(minVertices, maxVertices, neighbours);
  std::cout << "Adjacency list of a generated graph:" << std::endl;
  regularGraph.print();
  std::cout << "Saving graph..." << std::endl;
  regularGraph.saveGraph("regularGraph.txt");
  std::cout << std::endl;

  */


}
