#pragma once

#include <iostream>
#include "Matrix.h"

/* Class Graph has a matrix field where it can store any type of matrix as class Matrix. */

class Graph {
public:
  Graph() { matrix = new Matrix; }

  // TODO: wywalić do readFile i użyć setData
  void readFile(std::string fileName) { matrix->readFile(fileName); }
  void saveGraph(std::string fileName) { convertMatrix(AdjacencyList); matrix->saveAdjList(fileName); }

  void convertMatrix(RepresentationType to);
  void print() const { matrix->print(); }

  // TODO: random graph

private:
  Matrix* matrix;

  void adjMatToAdjList();
  void adjMatToIncMat();

  void adjListToAdjMat();
  void adjListToIncMat();

  void incMatToAdjMat();
  void incMatToAdjList();
};
