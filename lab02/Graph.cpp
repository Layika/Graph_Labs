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
  int rowWidth = -1;
  int lines = 2;

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
  if (lines == 1) {
      matrix->setRepresentationType(DegreeSequence);
      matrixConverter = new DegreeSequenceConverter;
  } else if (rowWidth == newData.size()) {
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
    else if (forMatrixType == IncidenceMatrix) matrixConverter = new IncidenceMatrixConverter;
    else matrixConverter = new DegreeSequenceConverter;
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


// Function for generating a random degree sequence
std::vector<unsigned int> Graph::makeRandomDegreeSequence(const unsigned int length) {
  std::vector<unsigned int> sequence;

  while (sequence.size() < length) sequence.push_back(intRand(0, length-1));

  return sequence;
}


// Function checking if it's parameter is a degree sequence
bool Graph::isDegreeSequence(std::vector<unsigned int> sequence) {
  // Sort vector in descending order (r for reverse)
  std::sort(sequence.rbegin(), sequence.rend());

  // If number of odd elements in sequence is odd then we can't build a graph
  unsigned int odds=0;
  for (unsigned int i=0; i<sequence.size(); ++i) if (sequence[i]%2) odds++;
  if (odds%2) return false;

  // Make copy of the given sequence as we have to change values in it
  std::vector<unsigned int> sequenceCopy;
  for (unsigned int i=0; i<sequence.size(); ++i) sequenceCopy.push_back(sequence[i]);

  while (true) {
    // If all elements are equal to 0 return true - it means that we got a graph
    if (std::all_of(sequenceCopy.begin(), sequenceCopy.end(), [](unsigned int i) { return i==0; })) return true;

    // If we can't build a graph out of it (element smaller than 0 or bigger than length makes it impossible
    // as we have exactly length number of nodes) return false
    if (sequenceCopy[0] < 0 or sequenceCopy[0] >= sequenceCopy.size()) return false;

    for (unsigned int i=1; i<=sequenceCopy[0]; ++i) --sequenceCopy[i];

    sequenceCopy[0] = 0;

    // Sort vector again
    std::sort(sequenceCopy.rbegin(), sequenceCopy.rend());
  }
}

std::vector<unsigned int> Graph::findComponents() {
    // Counter value will be different for every component
    unsigned int counter = 0;
    convertMatrix(AdjacencyList);

    // Initialize components with -1 for every node
    unsigned int nodes = matrix->getRows();
    std::vector<unsigned int> components(nodes);
    std::fill(components.begin(), components.end(), -1);

    // For every node
    for(unsigned int i = 0; i < nodes; i++) {
        if (components[i] == -1) {
            // Mark the i-th node as part of a component numbered with counter
            components[i] = ++counter;
            // Depth-first search
            depthFirstComponent(counter, i, components);
        }
    }

    return components;
}

void Graph::depthFirstComponent(unsigned int counter, unsigned int node, std::vector<unsigned int>& components) {
    unsigned int adjacentNodes = matrix->getColumns(node);

    // For every adjacent node
    for (unsigned int i = 0; i < adjacentNodes; i++){
        // Get ID of i-th adjacent node
        unsigned int nodeID = matrix->getElement(node, i) - 1;
        if (components[nodeID] == -1) {
            // Mark the i-th node as part of a component numbered with counter
            components[nodeID] = counter;
            // Perform further depth-first search
            depthFirstComponent(counter, nodeID, components);
        }
    }
}

std::vector<unsigned int> Graph::biggestComponent() {
    convertMatrix(AdjacencyList);
    // Find every component and store it in "components"
    std::vector<unsigned int> components = findComponents();

    // nodeCount will store the amount of nodes per component
    unsigned int totalNodes = components.size();
    std::vector<unsigned int> nodeCount(totalNodes);

    // Count nodes per component, starting from 0
    std::fill(nodeCount.begin(), nodeCount.end(), 0);
    for (unsigned int i = 0; i < totalNodes; i++) {
        nodeCount[components[i]]++;
    }

    // Find the component with the biggest node count
    unsigned int biggestNodeCount = 0;
    unsigned int currentBiggestComponent = 0;
    for (unsigned int i = 0; i < totalNodes; i++) {
        if (nodeCount[i] > biggestNodeCount) {
            biggestNodeCount = nodeCount[i];
            currentBiggestComponent = i;
        }
    }

    // Build vector of nodes belonging to the biggest component
    std::vector<unsigned int> result;
    for(unsigned int i = 0; i < totalNodes; i++) {
        if (components[i] == currentBiggestComponent)
            result.push_back(i+1);
    }

    return result;
}
