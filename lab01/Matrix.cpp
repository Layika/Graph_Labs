#include "Matrix.h"

#include <sstream>
#include <iterator>

void Matrix::saveAdjList(std::string fileName) {
  // Open out file
  std::ofstream outfile(fileName);

  // Write there formated data
  for (unsigned int i=0; i<data.size(); ++i) {
    for (unsigned int j=0; j<data[i].size(); ++j) {
      outfile << data[i][j];
      if (j!=data[i].size()-1) outfile << " ";
    }

    outfile << std::endl;
  }

  // Close the file
  outfile.close();
}

void Matrix::print() const {
  for(auto row : data) {
    for(auto col : row) std::cout << col << ' ';
    std::cout << std::endl;
  }
}

unsigned int Matrix::findInCol(unsigned int col, int el) {
  unsigned int idx = 0;
  for (unsigned int row=0; row<getRows(); ++row) {
    if (data[row][col] == el) idx=row;
  }
  return idx;
}

std::vector<unsigned int> Matrix::findElement(int el) {
  std::vector<unsigned int> v;
  for(unsigned int row = 0; row < getRows(); ++row) {
    auto colIter = std::find(data[row].begin(),data[row].end(), el);
    int column = std::distance(data[row].begin(), colIter);
    if (column <  data[row].size()){
      v.push_back(row);
      v.push_back(column);
      return v;
    }
  }

  return v;
}

long Matrix::numberOfOccurences(int el) {
  long count = 0;
  for(unsigned int row = 0; row < getRows(); ++row) {
    count += std::count(data[row].begin(), data[row].end(), el);
  }

  return count;
}

unsigned int Matrix::numberOfElements() {
    unsigned int number = 0;
    for(auto &row: data) {
        number += row.size();
    }

    return number;
}

// Function creating an empty adjacency matrix
void Matrix::createEmptyAdjacencyMat(unsigned int vertices) {
  std::vector<std::vector<int>> emptyMatrix(vertices, std::vector<int>(vertices));

  for (unsigned int i=0; i<vertices; ++i) std::fill(emptyMatrix[i].begin(), emptyMatrix[i].end(), 0);

  representationType = AdjacencyMatrix;

  saveData(emptyMatrix);
}


void AdjacencyListConverter::convertRepresentation(Matrix* matrix, RepresentationType to) {
  if (to == AdjacencyMatrix) {
    adjListToAdjMat(matrix);
  } else if (to == IncidenceMatrix) {
    adjListToIncMat(matrix);
  }
}

void AdjacencyListConverter::adjListToAdjMat(Matrix *matrix) {
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
  matrix->setRepresentationType(AdjacencyList);
}


void AdjacencyListConverter::adjListToIncMat(Matrix* matrix) {
  std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>(matrix->numberOfElements()));
  unsigned int numberOfEdge = 0;
  for (unsigned int row=0; row<matrix->getRows(); ++row) {

      for (unsigned int col=0; col<matrix->getColumns(row); ++col) {
          newData[row][numberOfEdge] = 1;
          if (matrix->getGraphType() == Directed) newData[matrix->getElement(row, col) - 1][numberOfEdge] = -1;
          else newData[matrix->getElement(row, col) - 1][numberOfEdge] = 1;
          ++numberOfEdge;
      }
  }

  matrix->saveData(newData);
  matrix->setRepresentationType(IncidenceMatrix);
}

void AdjacencyMatrixConverter::convertRepresentation(Matrix* matrix, RepresentationType to) {
  if (to == AdjacencyList) {
    adjMatToAdjList(matrix);
  } else if (to == IncidenceMatrix) {
    adjMatToIncMat(matrix);
  }
}

void AdjacencyMatrixConverter::adjMatToAdjList(Matrix* matrix) {
  std::vector<std::vector<int>> newData;

  for (unsigned int row=0; row<matrix->getRows(); ++row) {
    std::vector<int> newRow;

    for (unsigned int col=0; col<matrix->getColumns(row); ++col)
      if (matrix->getElement(row,col) == 1) newRow.push_back(col+1);
    newData.push_back(newRow);
  }

  matrix->saveData(newData);
  matrix->setRepresentationType(AdjacencyList);
}

void AdjacencyMatrixConverter::adjMatToIncMat(Matrix* matrix) {
  long numberOfEdges = matrix->numberOfOccurences(1);
  std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>(numberOfEdges));

  if(numberOfEdges == 0) {
    matrix->saveData(newData);
    return;
  }

  std::vector<unsigned int> indexesOfOne = matrix->findElement(1);
  unsigned int onesCounter = 0;
  while(indexesOfOne.size() == 2) {
    newData[indexesOfOne[0]][onesCounter] = 1;
    if (matrix->getGraphType() == Directed) newData[indexesOfOne[1]][onesCounter] = -1;
    else newData[indexesOfOne[1]][onesCounter] = 1;

    matrix->setElement(indexesOfOne, 0);
    indexesOfOne = matrix->findElement(1);
    ++onesCounter;
  }

  matrix->saveData(newData);
  matrix->setRepresentationType(IncidenceMatrix);
}


void IncidenceMatrixConverter::convertRepresentation(Matrix* matrix, RepresentationType to) {
  if (to == AdjacencyList) {
    incMatToAdjList(matrix);
  } else if (to == AdjacencyMatrix) {
    incMatToAdjMat(matrix);
  }
}

void IncidenceMatrixConverter::incMatToAdjMat(Matrix* matrix) {
  std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>(matrix->getRows()));

  std::vector<unsigned int> indexesOfOne = matrix->findElement(1);
  while(indexesOfOne.size() == 2) {
    unsigned int rowOfMinusOne;
    if (matrix->getGraphType() == Directed) rowOfMinusOne = matrix->findInCol(indexesOfOne[1], -1);
    else rowOfMinusOne = matrix->findInCol(indexesOfOne[1], 1);
    newData[indexesOfOne[0]][rowOfMinusOne] = 1;

    matrix->setElement(indexesOfOne, 0);
    indexesOfOne = matrix->findElement(1);
  }

  matrix->saveData(newData);
  matrix->setRepresentationType(AdjacencyMatrix);
}

void IncidenceMatrixConverter::incMatToAdjList(Matrix* matrix) {
  std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>());

  std::vector<unsigned int> indexesOfOne = matrix->findElement(1);
  while(indexesOfOne.size() == 2) {
      unsigned int rowOfMinusOne;
      if (matrix->getGraphType() == Directed) rowOfMinusOne = matrix->findInCol(indexesOfOne[1], -1);
      else {
        rowOfMinusOne = matrix->findInCol(indexesOfOne[1], 1);
        matrix->setElement(indexesOfOne, 0);
      }

      newData[indexesOfOne[0]].push_back(rowOfMinusOne + 1);

      if (matrix->getGraphType() == Undirected) {
        std::vector<unsigned int> indexes;
        indexes.push_back(rowOfMinusOne);
        indexes.push_back(indexesOfOne[1]);
        matrix->setElement(indexes, 0);
      }

      else matrix->setElement(indexesOfOne, 0);
      indexesOfOne = matrix->findElement(1);
  }

  matrix->saveData(newData);
  matrix->setRepresentationType(AdjacencyList);
}
