#include "Graph.h"
#include <vector>

// TODO: fix shitty code
void Graph::convertMatrix(RepresentationType to) {
  RepresentationType currentType = matrix->getRepresentationType();
  if (currentType != to) {
    switch (currentType) {
      case AdjacencyList:
        if (to == AdjacencyMatrix) adjListToAdjMat();
        else adjListToIncMat();
      case AdjacencyMatrix:
        if (to == AdjacencyList) adjMatToAdjList();
        else adjMatToIncMat();
      case IncidenceMatrix:
        if (to == AdjacencyList) incMatToAdjList();
        else incMatToAdjMat();
    }
  }
}

void Graph::adjMatToAdjList() {
  std::vector<std::vector<int>> newData;

  for (unsigned int row=0; row<matrix->getRows(); ++row) {
    std::vector<int> newRow;

    for (unsigned int col=0; col<matrix->getColumns(row); ++col)
      if (matrix->getElement(row,col) == 1) newRow.push_back(col+1);
    newData.push_back(newRow);
    }

  matrix->saveData(newData);
  matrix->saveType(AdjacencyList);
}

void Graph::adjListToAdjMat() {
  std::vector<std::vector<int>> newData;

  for (unsigned int row=0; row<matrix->getRows(); ++row) {
    std::vector<int> newRow;

    for (unsigned int col=0; col<matrix->getRows(); ++col) {
      if (matrix->isInRow(row, col+1)) newRow.push_back(1);
      else newRow.push_back(0);
    }
    newData.push_back(newRow);
  }

  matrix->saveData(newData);
  matrix->saveType(AdjacencyMatrix);
}



void Graph::adjMatToIncMat() {}

void Graph::adjListToIncMat() {
}

void Graph::incMatToAdjMat() {
  std::vector<std::vector<int>> newData;
  for (unsigned int i=0; i<matrix->getRows(); ++i) {
    std::vector<int> newRow;
    for (unsigned int j=0; j<matrix->getRows(); ++j) newRow.push_back(0);
    newData.push_back(newRow);
  }

  std::vector<int> indexesOfOne = matrix->findElement(1);
  while(indexesOfOne.size() == 2) {
    unsigned int rowOfMinusOne = matrix->findInCol(indexesOfOne[1], -1);
    newData[indexesOfOne[0]][rowOfMinusOne] = 1;

    matrix->setElement(indexesOfOne, 0);
    indexesOfOne = matrix->findElement(1);
  }

  matrix->saveData(newData);
  matrix->saveType(AdjacencyMatrix);
}

void Graph::incMatToAdjList() {}

int main() {
  Graph g;
  /*g.readFile("adjmatrix.txt");
  g.convertMatrix(AdjacencyList);
  g.print();
  g.convertMatrix(AdjacencyMatrix);
  g.print();*/

  g.readFile("incmatrix.txt");
  g.convertMatrix(AdjacencyMatrix);
  g.print();
}
