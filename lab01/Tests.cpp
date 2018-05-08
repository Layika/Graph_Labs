#include "Graph.h"
#include <iostream>

int main() {
  // ADJACENCY LIST GRAPH
  std::cout << "ADJACENCY LIST GRAPH" << std::endl << std::endl;
  std::cout << "Creating adjacency list graph..." << std::endl;
  Graph adjacencyListGraph;

  std::cout << "Reading adjacency list from file:" << std::endl;
  adjacencyListGraph.readFile("adjlist.txt");
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

  std::cout << "Saving graph to file graph.txt..." << std::endl;
  adjacencyListGraph.saveGraph("graph.txt");
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;


  // ADJACENCY MATRIX GRAPH
  std::cout << "ADJACENCY MATRIX GRAPH" << std::endl << std::endl;
  std::cout << "Creating adjacency matrix graph..." << std::endl;
  Graph adjacencyMatrixGraph;

  std::cout << "Reading adjacency matrix from file:" << std::endl;
  adjacencyMatrixGraph.readFile("adjmatrix.txt");
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

  std::cout << "Saving graph to file graph.txt..." << std::endl;
  adjacencyMatrixGraph.saveGraph("graph.txt");
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;


  // INCIDENCE MATRIX GRAPH
  std::cout << "INCIDENCE MATRIX GRAPH" << std::endl << std::endl;
  std::cout << "Creating incidence matrix graph..." << std::endl;
  Graph incidenceMatrixGraph;

  std::cout << "Reading incidence matrix from file:" << std::endl;
  incidenceMatrixGraph.readFile("incmatrix.txt");
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

  std::cout << "Saving graph to file graph.txt..." << std::endl;
  incidenceMatrixGraph.saveGraph("graph.txt");
  std::cout << "Graph ready to plot" << std::endl;
  std::cout << std::endl << std::endl;

  // RANDOM GRAPHS
  std::cout << "" << std::endl << std::endl;
}
