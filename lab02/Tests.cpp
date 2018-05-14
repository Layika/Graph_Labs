#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {

  srand(time(NULL));

  // DEGREE SEQUENCES
  // Make a random degree sequence and check if it can represent a graph
  unsigned int sequenceLen = 7;

  std::vector<unsigned int> sequence = Graph::makeRandomDegreeSequence(sequenceLen);
  //std::vector<unsigned  int> sequence = {2, 2, 1, 1, 0};

  while (!Graph::isDegreeSequence(sequence)) sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  std::cout << "Found a good sequence!" << std::endl;
  std::sort(sequence.rbegin(), sequence.rend());
  for (unsigned int i=0; i<sequence.size(); ++i) std::cout << sequence[i] << " ";
  std::cout << std::endl << std::endl;

  std::cout << "Generating random graph..." << std::endl << std::endl;
  Graph randomGraph(Undirected);
  int a, b;
  randomGraph.generateRandomNP(8, 12, 5, 10, a, b);

  std::cout << std::endl;



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


  // HAMILTON CYCLE
  std::cout << "HAMILTON CYCLE" << std::endl << std::endl;
  std::cout << "Creating hamilton graph..." << std::endl;
  Graph hamilton(Undirected);

  std::cout << "Reading adjacency list from file:" << std::endl;
  hamilton.readFile("sample_input_data/hamiltoncycle.txt");
  hamilton.print();
  std::cout << std::endl;

  hamilton.checkHamiltonianCycle();


  // RANDOM K-REGULAR GRAPHS
  std::cout << "Generating a regular graph..." << std::endl;
  Graph regularGraph(Undirected);

  unsigned int minVertices = 6;
  unsigned int maxVertices = 6;
  unsigned int neighbours = 2;
  regularGraph.generateRandomRegular(minVertices, maxVertices, neighbours);
  std::cout << "Adjacency list of a generated graph:" << std::endl;
  regularGraph.print();
  std::cout << "Saving graph..." << std::endl;
  regularGraph.saveGraph("regularGraph.txt");
  std::cout << std::endl;

}
