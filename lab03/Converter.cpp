#include "Converter.h"
#include <algorithm>

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

void DegreeSequenceConverter::convertRepresentation(Matrix* matrix, RepresentationType to) {
    if ( to == AdjacencyList) {
        degreeSeqToAdjList(matrix);
    }
}

struct degreeNode {
    int value;
    unsigned int order;
};

bool compareByValue(const degreeNode &a, const degreeNode &b) {
    return a.value > b.value;
}



void DegreeSequenceConverter::degreeSeqToAdjList(Matrix* matrix) {
    std::vector<degreeNode> sequence(matrix->getColumns(0));
    for (int i = 0; i < matrix->getColumns(0); ++i) {
        sequence[i].value = matrix->getElement(0, i);
        sequence[i].order = i;
    }


   std::vector<std::vector<int>> newData(matrix->getColumns(0), std::vector<int>());

   while (sequence[0].value != 0) {
       int d = sequence[0].value;
       for (int i = 1; i < d; ++i) {
           newData[sequence[i].order].push_back(sequence[0].order + 1);
           newData[sequence[0].order].push_back(sequence[i].order + 1);
           sequence[i].value = sequence[i].value - 1;
       }
       sequence[0].value = 0;
       sort(sequence.begin(), sequence.end(), compareByValue);
   }

   matrix->saveData(newData);

 }
