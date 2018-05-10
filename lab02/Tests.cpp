#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {

  unsigned int sequenceLen = 3;

  std::vector<unsigned int> sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  while (!Graph::isDegreeSequence(sequence)) sequence = Graph::makeRandomDegreeSequence(sequenceLen);

  std::cout << "Found good sequence!" << std::endl;

  for (unsigned int i=0; i<sequence.size(); ++i) std::cout << sequence[i] << " ";
  std::cout << std::endl;

}
