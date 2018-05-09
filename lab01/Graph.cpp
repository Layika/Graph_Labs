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
  if (rowWidth == newData.size()) {
      matrix->setRepresentationType(AdjacencyMatrix);
      matrixConverter = new AdjacencyMatrixConverter;
  } else if (rowWidth == -2) {
      matrix->setRepresentationType(AdjacencyList);
      matrixConverter = new AdjacencyListConverter;
  } else {
      matrix->setRepresentationType(IncidenceMatrix);
      matrixConverter = new IncidenceMatrixConverter;
  }

  matrix->saveData(newData);

  // Close the read file
  dataFile.close();
}

// TODO: fix shitty code
// Wrapper function converting any type to the type we want
// It handles calling the right function (see private functions)
void Graph::convertMatrix(RepresentationType to) {
    matrixConverter->convertRepresentation(matrix, to);
    delete matrixConverter;
    setConverter(to);
}

void Graph::setConverter(const RepresentationType &forMatrixType) { 
    if (forMatrixType == AdjacencyList) matrixConverter = new AdjacencyListConverter;
    else if (forMatrixType == AdjacencyMatrix) matrixConverter = new AdjacencyMatrixConverter;
    else matrixConverter = new IncidenceMatrixConverter;
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

  matrix->createEmptyAdjacencyMat(vertices);
  setConverter(AdjacencyMatrix);

  int counter = 0;
  while (counter < edges) {
    int i = intRand(0, vertices-1);
    int j = intRand(0, vertices-1);

    if (i != j && matrix->getElement(i,j) == 0) {
      matrix->setElement(i, j, 1);
      if (matrix->getGraphType() == Undirected) matrix->setElement(j, i, 1);
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

    matrix->createEmptyAdjacencyMat(vertices);
    setConverter(AdjacencyMatrix);

    int randomValue;
    for(int i=0; i<vertices; i++) {
        for(int j=0; j<vertices; j++) {
            if( i != j) {
                randomValue = intRand(1, 100);
                if(randomValue <= probability) {
                    matrix->setElement(i, j, 1);
                    if (matrix->getGraphType() == Undirected) matrix->setElement(j, i, 1);
                }
            }
        }
    }
}
