#include "Graph.h"
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

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

// Algorithm converting adjacency matrix to adjacency list
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

// Algorithm converting adjacency list to adjacency matrix
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

// Algorithm converting adjacency matrix to incidence matrix
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


// Algorithm converting adjacency list to incidence matrix
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

// Algorithm converting incidence matrix to adjacency matrix
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

// Algorithm converting incidence matrix to adjacency list
void Graph::incMatToAdjList() {
    std::vector<std::vector<int>> newData(matrix->getRows(), std::vector<int>());

    std::vector<unsigned int> indexesOfOne = matrix->findElement(1);
    while(indexesOfOne.size() == 2) {
        unsigned int rowOfMinusOne = matrix->findInCol(indexesOfOne[1], -1);
        newData[indexesOfOne[0]].push_back(rowOfMinusOne + 1);

        matrix->setElement(indexesOfOne, 0);
        indexesOfOne = matrix->findElement(1);
    }

    matrix->saveData(newData);
    matrix->setType(AdjacencyList);
}


// Function for generating a random G(n,l) graph
void Graph::generateRandomNL(unsigned int minVertices, unsigned int maxVertices, unsigned int minEdges, unsigned int maxEdges, int& generatedVertices, int& generatedEdges) {
  // TODO: better initialization
  int vertices = -1;
  int edges = 0;

  while (vertices <= 0 || edges <= 0 || edges > (vertices*(vertices-1))/2) {
    vertices = intRand(minVertices, maxVertices);
    edges = intRand(minEdges, maxEdges);
  }

  generatedVertices = vertices;
  generatedEdges = edges;

  this->matrix->createEmptyAdjacencyMat(vertices);

  int counter = 0;
  while (counter < edges) {
    int i = intRand(0, vertices-1);
    int j = intRand(0, vertices-1);

    if (i != j && matrix->getElement(i,j) == 0) {
      matrix->setElement(i, j, 1);
      matrix->setElement(j, i, 1);
      counter++;
    }
  }
}

// Function for generating a random G(n,p) graph
void Graph::generateRandomNP(unsigned int minVertices, unsigned int maxVertices, unsigned int minProbability, unsigned int maxProbability, int& generatedVertices, int& generatedProbability) {

    int vertices = -1;
    float probability = 0;
    while (vertices <= 0 || probability < 0 || probability > 100) {
        vertices = intRand(minVertices, maxVertices);
        probability = intRand(minProbability, maxProbability);
    }

    generatedVertices = vertices;
    generatedProbability = probability;

    this->matrix->createEmptyAdjacencyMat(vertices);

    int randomValue;
    for(int i=0; i<vertices; i++) {
        for(int j=0; j<vertices; j++) {
            if( i != j) {
                randomValue = intRand(1, 100);
                if(randomValue <= probability) {
                    matrix->setElement(i, j, 1);
                    matrix->setElement(j, i, 1);
                }
                else {
                    matrix->setElement(i, j, 0);
                    matrix->setElement(j, i, 0);
                }
            }
        }
    }
}
