#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {

  srand(time(NULL));

  // DEGREE SEQUENCES
  std::cout << "DEGREE SEQUENCES" << std::endl;
  std::cout << std::endl;

  // Make a random degree sequence and check if it can represent a graph
  unsigned int sequenceLen = 7;

  std::vector<unsigned int> sequence = Graph::makeRandomDegreeSequence(sequenceLen);
  //std::vector<unsigned  int> sequence = {2, 2, 1, 1, 0};

  while (!Graph::isDegreeSequence(sequence)) sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  std::cout << "Found a good sequence:" << std::endl;
  std::sort(sequence.rbegin(), sequence.rend());
  for (unsigned int i=0; i<sequence.size(); ++i) std::cout << sequence[i] << " ";
  std::cout << std::endl << std::endl;

  // Make a graph and read sequence from file
  Graph degreeSeqGraph(Undirected);
  std::cout << "Reading degree sequence from file:" << std::endl;
  degreeSeqGraph.readFile("sample_input_data/degreeseq.txt");
  degreeSeqGraph.print();
  // Save graph converts degree sequence to adjacency list so basically creates a graph out of it
  degreeSeqGraph.saveGraph("graph_sample.txt");
  std::cout << "Saved to file, generated a graph of adjacency list:" << std::endl;
  degreeSeqGraph.print();
  std::cout << std::endl << std::endl;

  // Eulerian graphs
  std::cout << "EULERIAN GRAPHS" << std::endl;

  Graph eulerianGraph(Undirected);
  std::cout << "Reading degree sequence from file:" << std::endl;
  eulerianGraph.readFile("sample_input_data/eulerianseq.txt");
  eulerianGraph.print();
  std::cout << "Saving graph to file..." << std::endl;
  eulerianGraph.saveGraph("euleriancycle.txt");
  std::cout << "Adjacency list of this graph:" << std::endl;
  eulerianGraph.print();

  sequenceLen = 5;
  sequence = Graph::makeRandomDegreeSequence(sequenceLen);
  while (!Graph::isEulerianCycle(sequence)) sequence = Graph::makeRandomDegreeSequence(sequenceLen);
  std::cout << std::endl << "Found a good eulerian sequence (with cycle):";
  for (unsigned int i=0; i<sequence.size(); ++i)
    std::cout << " " << sequence[i];
  std::cout << std::endl;



  std::cout << std::endl << std::endl;

  // SEPARATE COMPONENTS
  std::cout << "FINDING SEPARATE COMPONENTS" << std::endl;
  std::cout << "Generating random graph..." << std::endl;
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
  std::cout << std::endl << std::endl << std::endl;


  // HAMILTON CYCLE
  std::cout << "HAMILTON CYCLE" << std::endl << std::endl;
  std::cout << "Creating hamilton graph..." << std::endl;
  Graph hamilton(Undirected);

  std::cout << "Reading adjacency list from file:" << std::endl;
  hamilton.readFile("sample_input_data/hamiltoncycle.txt");
  hamilton.print();
  std::cout << std::endl;

  hamilton.checkHamiltonianCycle();
  std::cout << std::endl << std::endl;

  // RANDOM K-REGULAR GRAPHS
  std::cout << "RANDOM K-REGULAR GRAPHS" << std::endl << std::endl;
  std::cout << "Generating a regular graph..." << std::endl;
  Graph regularGraph(Undirected);

  unsigned int minVertices = 6;
  unsigned int maxVertices = 6;
  unsigned int neighbours = 2;
  regularGraph.generateRandomRegular(minVertices, maxVertices, neighbours);
  std::cout << "Adjacency list of a generated graph:" << std::endl;
  regularGraph.print();
  // TODO: segfault w konwerterze:
  //std::cout << "Saving graph..." << std::endl;
  //regularGraph.saveGraph("regularGraph.txt");
  //std::cout << std::endl;

}
