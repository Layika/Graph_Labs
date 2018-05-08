#include "Graph.h"
#include <vector>
#include <string>
#include <sstream>

void Graph::readFile(std::string fileName) {

  // Open file with a matrix
  // Throw an exception if file fails to open
  std::ifstream dataFile(fileName);
  if (dataFile.fail()) { /* TODO: exception */ }

  // Create a new data matrix where we can store new data
  std::vector<std::vector<int>> newData;

  // Now we need to be able to tell what matrix are we reading from file
  // TODO: Make it a bit better than using -1 and -2
  size_t rowWidth = -1;

  // Read the file line by line and store each line in line variable
  std::string line;
  while(getline(dataFile, line)) {

    // Change line variable (string) to stream because we need a stream to iterate through it
    std::istringstream lineStream(line);

    // Change data to ints and add it to newData matrix
    newData.emplace_back(std::istream_iterator<int>(lineStream), std::istream_iterator<int>());

    // Update type symbols in case they need to be changed because we got a different
    // line length etc. We can use it later to determine data type
    if(rowWidth == -1) rowWidth = newData.back().size();
    else if(rowWidth != newData.back().size()) rowWidth = -2;
  }

  // Save the new type and new data matrix
  if (rowWidth == newData.size()) matrix->setType(AdjacencyMatrix);
  else if (rowWidth == -2) matrix->setType(AdjacencyList);
  else matrix->setType(IncidenceMatrix);
  matrix->saveData(newData);

  // Close the read file
  dataFile.close();
}

// TODO: fix shitty code
// Wrapper function converting any type to the type we want
// It handles calling the right function (see private functions)
void Graph::convertMatrix(RepresentationType to) {
  // Get current representation type
  RepresentationType currentType = matrix->getRepresentationType();

  // If the type is different than the one we want to convert to
  // then use convertion functions
  if (currentType != to) {
    switch (currentType) {

      case AdjacencyList:
        if (to == AdjacencyMatrix) adjListToAdjMat();
        else adjListToIncMat();
        break;
      case AdjacencyMatrix:
        if (to == AdjacencyList) adjMatToAdjList();
        else adjMatToIncMat();
        break;
      case IncidenceMatrix:
        if (to == AdjacencyList) incMatToAdjList();
        else incMatToAdjMat();
        break;
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
  matrix->setType(AdjacencyList);
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
  matrix->setType(AdjacencyMatrix);
}



void Graph::adjMatToIncMat() {
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
    newData[indexesOfOne[1]][onesCounter] = -1;

    matrix->setElement(indexesOfOne, 0);
    indexesOfOne = matrix->findElement(1);
    ++onesCounter;
  }

  matrix->saveData(newData);
  matrix->setType(IncidenceMatrix);
}

void Graph::adjListToIncMat() {
    std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>(matrix->numberOfElements()));
    unsigned int numberOfEdge = 0;
    for (unsigned int row=0; row<matrix->getRows(); ++row) {

        for (unsigned int col=0; col<matrix->getColumns(row); ++col) {
            newData[row][numberOfEdge] = 1;
            newData[matrix->getElement(row, col) - 1][numberOfEdge] = -1;
            ++numberOfEdge;
        }
    }

    matrix->saveData(newData);
    matrix->setType(IncidenceMatrix);
}

void Graph::incMatToAdjMat() {
  std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>(matrix->getRows()));

  std::vector<unsigned int> indexesOfOne = matrix->findElement(1);
  while(indexesOfOne.size() == 2) {
    unsigned int rowOfMinusOne = matrix->findInCol(indexesOfOne[1], -1);
    newData[indexesOfOne[0]][rowOfMinusOne] = 1;

    matrix->setElement(indexesOfOne, 0);
    indexesOfOne = matrix->findElement(1);
  }

  matrix->saveData(newData);
  matrix->setType(AdjacencyMatrix);
}

void Graph::incMatToAdjList() {}

int main() {
  Graph g;
  g.readFile("adjmatrix.txt");
  g.convertMatrix(IncidenceMatrix);
  g.print();
//  g.convertMatrix(AdjacencyMatrix);
//  g.print();

//  g.readFile("incmatrix.txt");
//  g.print();
//  g.convertMatrix(AdjacencyMatrix);
//  g.print();
//  g.convertMatrix(IncidenceMatrix);
//  g.print();
}
