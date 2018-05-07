#pragma once

#include <iostream>
#include "Matrix.h"

/* Class Graph has a matrix field where it can store any type of matrix as class Matrix.
 * It also handles translation of the matrix to all different types */

class Graph {
public:
  Graph() { matrix = new Matrix; }

  // TODO: wywalić do readFile i użyć setData
  void readFile(std::string fileName) { matrix->readFile(fileName); }

  // Wrapper functions for handling saving graph to file in adjacency list and debug print
  void saveGraph(std::string fileName) { convertMatrix(AdjacencyList); matrix->saveAdjList(fileName); }
  void print() const { matrix->print(); }

  void convertMatrix(RepresentationType to);

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
