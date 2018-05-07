#pragma once

#include <iostream>
#include "Matrix.h"

/* Class Graph has a matrix field where it can store any type of matrix as class Matrix *
 * Base class for oprating on graphs                                                    */

class Graph {
public:
  // Conctructor for graphs, only creates a new matrix, but doesn't fill it
  // In order to get a matrix we need to read from file or create a random matrix
  Graph() { matrix = new Matrix; }

  // Reads matrix from file. After a read matrix will be updated
  void readFile(std::string fileName) { matrix->readFile(fileName); }

  // Wrapper function converting any type to the type we want
  // It handles calling the right function (see private functions)
  void convertMatrix(RepresentationType to);

  // Wrapper functions for handling saving graph to file in adjacency list and debug print
  void saveGraph(std::string fileName) { convertMatrix(AdjacencyList); matrix->saveAdjList(fileName); }
  void print() const { matrix->print(); }

  // TODO: random graph
  // I think we should make a wrapper function too, but I'm not sure, I guess it will be consistent with other ones

private:
  Matrix* matrix;

  void adjMatToAdjList();
  void adjMatToIncMat();

  void adjListToAdjMat();
  void adjListToIncMat();

  void incMatToAdjMat();
  void incMatToAdjList();
};
