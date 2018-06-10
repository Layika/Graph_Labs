#include "Graph.h"
#include <iostream>

int main() {
  // PAGE RANK
  std::cout << "PAGE RANK" << std::endl << std::endl;
  Graph pageRankGraph(Directed);
  pageRankGraph.readFile("sample_input_data/pagerank.txt");
  pageRankGraph.PageRankPt();
}
