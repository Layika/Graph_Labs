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
  int lines = 0;

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

    ++lines;
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

void Graph::generateRandomRegular(unsigned int minVertices, unsigned int maxVertices, unsigned int neighbours) {
  // Get a random nuber of vertices
  unsigned int vertices = intRand(minVertices, maxVertices);

  // Create a new list
  std::vector<std::vector<int>> newList(vertices);

  // Change data type and graph type in case it was different
  matrix->setRepresentationType(AdjacencyList);
  matrix->setGraphType(Undirected);

  // For each vertex
  for (unsigned int v=0; v<vertices; ++v) {

    // If there are not enough neighbours for it
    while (newList[v].size() < neighbours) {

      // Get a random vertex number that is not equal to current vertex
      unsigned int randomVertex = intRand(1, vertices);
      while (randomVertex == v+1 ||
        (std::find(newList[v].begin(), newList[v].end(), randomVertex) != newList[v].end())) {
          randomVertex = intRand(1, vertices);
      }

      // (Check if both of them don't have enough neighbours)
      if (newList[randomVertex-1].size() < neighbours) {
        // And add it as a neighbour
        newList[v].push_back(randomVertex);
        newList[randomVertex-1].push_back(v+1);

      }
    }
  }

  matrix->saveData(newList);
}


/* This function solves the Hamiltonian Cycle problem using Backtracking.
  It mainly uses hamiltonianCycleUtil() to solve the problem. It returns false
  if there is no Hamiltonian Cycle possible, otherwise return true and
  prints the path. Please note that there may be more than one solutions,
  this function prints one of the feasible solutions. */

bool Graph::checkHamiltonianCycle() {

  // We need adjacency matrix so first convert whatever we have to this type
  convertMatrix(AdjacencyMatrix);

  // Prepare path variable and fill it with -1
  std::vector<int> path(matrix->getRows());
  std::fill(path.begin(), path.end(), -1);

  // Lets put vertex 1 as the first vertex in the path
  // If there is a Hamiltonian Cycle, then the path can be started
  // from any point of the cycle as the graph is undirected
  path[0] = 1;

  if (hamiltonianCycleUtil(path, 1) == false) {
    std::cout << "Solution does not exist" << std::endl;
    return false;
  }

  printHamiltonianCycle(path);
  return true;
}


// A recursive utility function to solve hamiltonian cycle problem
bool Graph::hamiltonianCycleUtil(std::vector<int>& path, unsigned int pos) {

  // base case: If all vertices are included in Hamiltonian Cycle
  if (pos == matrix->getRows()) {
      // And if there is an edge from the last included vertex to the first vertex
      if (matrix->getElement(path[pos-1]-1, path[0]-1) == 1 ) return true; //numerror
      //if (matrix->getElement(path[pos-1], path[0]) == 1 ) return true;
      else return false;
  }

  // Try different vertices as a next candidate in Hamiltonian Cycle.
  // We don't try for 1 as we included 1 as starting point in in checkHamiltonianCycle()
  for (unsigned int v=1; v<matrix->getRows(); v++) {

      // Check if this vertex can be added to Hamiltonian Cycle
      if (hamiltonianCanAdd(v, path, pos)) {
        path[pos] = v+1; //numerror
        //path[pos] = v;

        std::cout << "PATH:";
        for (int i=0; i<path.size(); ++i) std::cout << " " << path[i];
        std::cout << std::endl;

        // Recur to construct rest of the path
        if (hamiltonianCycleUtil(path, pos+1) == true) return true;
        // If adding vertex v doesn't lead to a solution, then remove it
        else path[pos] = -1;
      }

  }

  // If no vertex can be added to Hamiltonian Cycle constructed so far, then return false
  return false;
}

// A utility function to check if the vertex v can be added at index 'pos'
// in the Hamiltonian Cycle constructed so far (stored in 'path[]')
bool Graph::hamiltonianCanAdd(unsigned int vertex, std::vector<int>& path, unsigned int pos) {

  // Check if this vertex is an adjacent vertex of the previously added vertex
  if (matrix->getElement(path[pos-1]-1, vertex) == 0) return false;//numerror
  //if (matrix->getElement(path[pos-1], vertex) == 0) return false;
  // Check if the vertex has already been included
  for (unsigned int i=0; i<pos; i++)
    if (path[i] == vertex+1) return false;//numerror
    //if (path[i] == vertex) return false;

  return true;
}

// Function for printing hamiltonian cycle
void Graph::printHamiltonianCycle(std::vector<int>& cycle) {

  std::cout << "Hamiltonian Cycle:";
  for (unsigned int i=0; i<cycle.size(); ++i) std::cout << " " << cycle[i];
  std::cout << " " << cycle[0];

  std::cout << std::endl;
}

// Function for checking if a degree sequence is eulerian
bool Graph::isEulerianSequence(std::vector<unsigned int> sequence) {
  // If given sequence is a degree sequence
  if (Graph::isDegreeSequence(sequence)) {
    // And all degrees are even then it's eulerian too
    for (unsigned int i=0; i<sequence.size(); ++i)
      if (sequence[i] % 2) return false;
    return true;
  }
  return false;
}


void Graph::DFSUtil(unsigned int v, bool visited[], std::vector<std::vector<int>> matrixData) {
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i = matrixData[v].begin(); i != matrixData[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited, matrixData);
}

// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool Graph::areConnected(unsigned int rows) {
    // Mark all the vertices as not visited
    bool visited[rows];
    unsigned int i;
    for (i=0; i<rows; i++) visited[i] = false;

    // Find a vertex with non-zero degree
    for (i=0; i<rows; i++)
        if (matrix->getColumns(i) != 0) break;

    // If there are no edges in the graph, return true
    if (i == rows) return true;

    // Start DFS traversal from a vertex with non-zero degree
    std::vector<std::vector<int>> matrixData = matrix->getMatrix();
    DFSUtil(i, visited, matrixData);

    // Check if all non-zero degree vertices are visited
    for (i=0; i<rows; i++)
       if (visited[i] == false && matrix->getColumns(i) > 0) return false;

    return true;
}

/* The function returns one of the following values
   0 --> If grpah is not Eulerian
   1 --> If graph has an Euler path (Semi-Eulerian)
   2 --> If graph has an Euler Circuit (Eulerian)  */
int Graph::isEulerianCycle() {

    convertMatrix(AdjacencyList);
    unsigned int rows = matrix->getRows();

    // Check if all non-zero degree vertices are connected
    if (areConnected(rows) == false) return 0;

    // Count vertices with odd degree
    int odd = 0;
    for (unsigned int i=0; i<rows; i++)
        if (matrix->getColumns(i) & 1) odd++;

    // If count is more than 2, then graph is not Eulerian
    if (odd > 2) return 0;

    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    return (odd)? 1 : 2;
}

void Graph::randomize() {
    // The objective is to pick random A, B, C, D vertices, which form A-B and C-D edges
    // Then remove A-B and C-D edges in order to create new edges: A-D and B-C
    convertMatrix(AdjacencyList);

    // chosenVertices represents A, B, C and D vertices
    std::vector<int> chosenVertices;

    // Pick random A, B, D, C vertices
    for (unsigned int i = 0; i < 4; i++) {
        int randomVertex = intRand(1, matrix->getRows());
        while (std::find(chosenVertices.begin(), chosenVertices.end(), randomVertex) != chosenVertices.end()) {
            randomVertex = intRand(1, matrix->getRows());
        }
        chosenVertices.push_back(randomVertex);
    }

    convertMatrix(AdjacencyMatrix);

        // Check if chosen vertices fulfill requirements (stated in the first comment)
        if(matrix->getElement(chosenVertices[0]-1, chosenVertices[2]-1)) return;
        if(matrix->getElement(chosenVertices[0]-1, chosenVertices[3]-1)) return;
        if(matrix->getElement(chosenVertices[1]-1, chosenVertices[2]-1)) return;
        if(matrix->getElement(chosenVertices[1]-1, chosenVertices[3]-1)) return;
        if(matrix->getElement(chosenVertices[0]-1, chosenVertices[1]-1) == 0) return;
        if(matrix->getElement(chosenVertices[2]-1, chosenVertices[3]-1) == 0) return;

        // Remember connections before switching them
        int AtoB = matrix->getElement(chosenVertices[0]-1, chosenVertices[1]-1);
        int CtoD = matrix->getElement(chosenVertices[2]-1, chosenVertices[3]-1);
        int AtoD = matrix->getElement(chosenVertices[0]-1, chosenVertices[3]-1);
        int BtoC = matrix->getElement(chosenVertices[1]-1, chosenVertices[2]-1);

        // Set A-B edge
        matrix->setElement(chosenVertices[0]-1, chosenVertices[1]-1, AtoD);
        matrix->setElement(chosenVertices[1]-1, chosenVertices[0]-1, AtoD);

        // Set C-D edge
        matrix->setElement(chosenVertices[2]-1, chosenVertices[3]-1, BtoC);
        matrix->setElement(chosenVertices[3]-1, chosenVertices[2]-1, BtoC);

        // Set A-D edge
        matrix->setElement(chosenVertices[0]-1, chosenVertices[3]-1, AtoB);
        matrix->setElement(chosenVertices[3]-1, chosenVertices[0]-1, AtoB);

        // Set B-C edge
        matrix->setElement(chosenVertices[1]-1, chosenVertices[2]-1, CtoD);
        matrix->setElement(chosenVertices[2]-1, chosenVertices[1]-1, CtoD);
}

void Graph::printDegrees() {
    convertMatrix(AdjacencyList);
    for (unsigned int i = 0; i < matrix->getRows(); i++) {
        std::cout << matrix->getColumns(i) << " ";
    }
    std::cout << std::endl;
}
