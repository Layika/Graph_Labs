#pragma once

#include <iostream>
#include <stdlib.h>
#include "Matrix.h"

/* Class Graph has a matrix field where it can store any type of matrix as class Matrix *
 * Base class for oprating on graphs                                                    */

class Graph {
public:
  // Conctructor for graphs, only creates a new matrix, but doesn't fill it
  // In order to get a matrix we need to read from file or create a random matrix
  Graph() { matrix = new Matrix; }

  // Reads matrix from file. After a read matrix will be updated
  void readFile(std::string fileName);

  // Wrapper function converting any type to the type we want
  // It handles calling the right function (see private functions)
  void convertMatrix(RepresentationType to);

  // Wrapper functions for handling saving graph to file in adjacency list and debug print
  void saveGraph(std::string fileName) { convertMatrix(AdjacencyList); matrix->saveAdjList(fileName); }
  void print() const { matrix->print(); }

  // Helper function for random graphs, returns a random int
  static int intRand(const int min, const int max) { return rand() % (max-min+1) + min; }
  // Function for generating a random G(n,l) graph
  void generateRandomNL(unsigned int minVertices, unsigned int maxVertices, unsigned int minEdges, unsigned int maxEdges,  int& generatedVertices, int& generatedEdges);
  // Function for generating a random G(n,p) graph
  void generateRandomNP(unsigned int minVertices, unsigned int maxVertices, unsigned int minProbability, unsigned int maxProbability,  int& generatedVertices, int& generatedProbability);


private:
  Matrix* matrix;
  AbstractConverter* matrixConverter;

  // Functions for conversions. All of them create new data and then use Matrix method
  // saveData to change old matrix to a new one
  void adjMatToAdjList();
  void adjMatToIncMat();

  void adjListToAdjMat();
  void adjListToIncMat();

  void incMatToAdjMat();
  void incMatToAdjList();

    void setConverter(const RepresentationType &forMatrixType);
};
