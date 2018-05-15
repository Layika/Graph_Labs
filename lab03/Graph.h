#pragma once

#include <iostream>
#include <stdlib.h>
#include "Matrix.h"
#include "Converter.h"

/* Class Graph has a matrix field where it can store any type of matrix as class Matrix *
 * Base class for operating on graphs                                                    */

class Graph {
public:
  // Constructor for graphs, only creates a new matrix, but doesn't fill it
  // In order to get a matrix we need to read from file or create a random matrix
  Graph(GraphType type) { matrix = new Matrix; matrix->setGraphType(type); }

  // Reads matrix from file. After a read matrix will be updated
  void readFile(std::string fileName);

  // Getter for number of vertices
  unsigned int getVertexCount() {return matrix->getRows();}

  // Wrapper function converting any type to the type we want
  // It handles calling the right function (see private functions)
  void convertMatrix(RepresentationType to);

  // Wrapper functions for handling saving graph to file in adjacency list and debug print
  void saveGraph(std::string fileName) { convertMatrix(AdjacencyList); matrix->saveAdjList(fileName); }
  void print() const { matrix->print(); }
  void printWeights() const;

  // Helper function for random graphs, returns a random int
  static int intRand(const int min, const int max) { return rand() % (max-min+1) + min; }
  // Function for generating a random G(n,l) graph
  void generateRandomNL(unsigned int minVertices, unsigned int maxVertices, unsigned int minEdges, unsigned int maxEdges,  int& generatedVertices, int& generatedEdges);
  // Function for generating a random G(n,p) graph
  void generateRandomNP(unsigned int minVertices, unsigned int maxVertices, unsigned int minProbability, unsigned int maxProbability,  int& generatedVertices, int& generatedProbability);

  // Function for generating a random degree sequence
  static std::vector<unsigned int> makeRandomDegreeSequence(const unsigned int length);
  // Function checking if it's parameter is a degree sequence
  static bool isDegreeSequence(std::vector<unsigned int> sequence);

  // Function for finding connected components. Returns a vector which numbers every node according to
  // which component they belong to
  std::vector<unsigned int> findComponents();
  // Helper function for finding components which performs recursive depth-first search
  void depthFirstComponent(unsigned int counter, unsigned int node, std::vector<unsigned int>& components);
  // Function that returns a vector of nodes belonging to the biggest component
  std::vector<unsigned int> biggestComponent();

  // Function for generating random weights for each edge
  void generateRandomWeights(int minWeight, int maxWeight);

  // Getter and setter functions for weights
  int getWeight(unsigned int source, unsigned int dest);
  void setWeight(unsigned int source, unsigned int dest, int weight);

private:
  Matrix* matrix;
  Converter* matrixConverter;
  std::vector<std::vector<int>> weights;

  void setConverter(const RepresentationType &forMatrixType);
};
