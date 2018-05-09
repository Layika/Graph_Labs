#include "Graph.h"
#include <iostream>
#include <time.h>

int main() {
    srand(time(NULL));
  // ADJACENCY LIST GRAPH
  std::cout << "ADJACENCY LIST GRAPH" << std::endl << std::endl;
  std::cout << "Creating adjacency list graph..." << std::endl;
  Graph adjacencyListGraph(Undirected);

  std::cout << "Reading adjacency list from file:" << std::endl;
  adjacencyListGraph.readFile("adjlist_simple.txt");
  adjacencyListGraph.print();
  std::cout << std::endl;

  std::cout << "Converting adjacency list to adjacency matrix:" << std::endl;
  adjacencyListGraph.convertMatrix(AdjacencyMatrix);
  adjacencyListGraph.print();
  std::cout << std::endl;

  std::cout << "Converting adjacency matrix to adjacency list:" << std::endl;
  adjacencyListGraph.convertMatrix(AdjacencyList);
  adjacencyListGraph.print();
  std::cout << std::endl;

  std::cout << "Saving graph to file graph_al.txt..." << std::endl;
  adjacencyListGraph.saveGraph("graph_al.txt");
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;


  // ADJACENCY MATRIX GRAPH
  std::cout << "ADJACENCY MATRIX GRAPH" << std::endl << std::endl;
  std::cout << "Creating adjacency matrix graph..." << std::endl;
  Graph adjacencyMatrixGraph(Undirected);

  std::cout << "Reading adjacency matrix from file:" << std::endl;
  adjacencyMatrixGraph.readFile("adjmatrix_simple.txt");
  adjacencyMatrixGraph.print();
  std::cout << std::endl;

  std::cout << "Converting adjacency matrix to incidence matrix:" << std::endl;
  adjacencyMatrixGraph.convertMatrix(IncidenceMatrix);
  adjacencyMatrixGraph.print();
  std::cout << std::endl;

  std::cout << "Converting incidence matrix to adjacency matrix:" << std::endl;
  adjacencyMatrixGraph.convertMatrix(AdjacencyMatrix);
  adjacencyMatrixGraph.print();
  std::cout << std::endl;

  std::cout << "Saving graph to file graph_am.txt..." << std::endl;
  adjacencyMatrixGraph.saveGraph("graph_am.txt");
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;


  // INCIDENCE MATRIX GRAPH
  std::cout << "INCIDENCE MATRIX GRAPH" << std::endl << std::endl;
  std::cout << "Creating incidence matrix graph..." << std::endl;
  Graph incidenceMatrixGraph(Undirected);

  std::cout << "Reading incidence matrix from file:" << std::endl;
  incidenceMatrixGraph.readFile("incmatrix_simple.txt");
  incidenceMatrixGraph.print();
  std::cout << std::endl;

  std::cout << "Converting incidence matrix to adjacency list:" << std::endl;
  incidenceMatrixGraph.convertMatrix(AdjacencyList);
  incidenceMatrixGraph.print();
  std::cout << std::endl;

  std::cout << "Converting adjacency list to incidence matrix:" << std::endl;
  incidenceMatrixGraph.convertMatrix(IncidenceMatrix);
  incidenceMatrixGraph.print();
  std::cout << std::endl;

  std::cout << "Saving graph to file graph_im.txt..." << std::endl;
  incidenceMatrixGraph.saveGraph("graph_im.txt");
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;

  // RANDOM GRAPHS
  std::cout << "RANDOM GRAPHS" << std::endl << std::endl;

  int vertices, edges, probability;
  std::cout << "Generating random G(n,l) graph..." << std::endl << std::endl;
  Graph randomGraphNL(Undirected);
  randomGraphNL.generateRandomNL(6, 10, 5, 10, vertices, edges);
  std::cout << "Vertices: " << vertices << ", edges: " << edges << std::endl;
  randomGraphNL.print();

  std::cout << std::endl << "Saving graph to file random_graph_nl.txt..." << std::endl;
  randomGraphNL.saveGraph("graph_random_nl.txt");
  std::cout << "Graph ready to plot" << std::endl << std::endl;

  std::cout << "Generating random G(n,p) graph..." << std::endl << std::endl;
  Graph randomGraphNP(Undirected);
  randomGraphNP.generateRandomNP(6, 10, 20, 80, vertices, probability);
  std::cout << "Vertices: " << vertices << ", probability: " << probability << "%" << std::endl;
  randomGraphNP.print();

  std::cout << std::endl << "Saving graph to file random_graph_np.txt..." << std::endl;
  randomGraphNP.saveGraph("graph_random_np.txt");
  std::cout << "Graph ready to plot" << std::endl;
}
