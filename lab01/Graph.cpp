#include "Graph.h"
#include <vector>

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
  matrix->setData(newData);

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
  matrix->setType(AdjacencyMatrix);
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
