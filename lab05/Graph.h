#pragma once

#include <iostream>
#include <stdlib.h>

#include "Matrix.h"
#include "Converter.h"

/* Class Graph has a matrix field where it can store any type of matrix as class Matrix *
 * Base class for operating on graphs                                                    */

class Graph {
public:
  // Constructor for graphs, only creates a new matrix, but doesn't fill it
  // In order to get a matrix we need to read from file or create a random matrix
  Graph(GraphType type) { matrix = new Matrix; matrix->setGraphType(type); createWeights(); }

  // Getter for number of vertices
  unsigned int getVertexCount() {return matrix->getRows();}

  // Wrapper for getting a degree sequence
  std::vector<unsigned int> getDegreeSequence() { return matrix->getDegreeSequence(); }
  // Reads matrix from file. After a read matrix will be updated
  void readFile(std::string fileName);

  // Wrapper function converting any type to the type we want
  // It handles calling the right function (see private functions)
  void convertMatrix(RepresentationType to);

  // Wrapper functions for handling saving graph to file in adjacency list and debug print
  void saveGraph(std::string fileName) {
    RepresentationType previousType = matrix->getRepresentationType();
    convertMatrix(AdjacencyList);
    matrix->saveAdjList(fileName);
    convertMatrix(previousType);

  }
  void print() const { matrix->print(); }
  void printFlowNetwork() const;
  void printDegrees();


  // Helper function for random graphs, returns a random int
  static int intRand(const int min, const int max) { return rand() % (max-min+1) + min; }
  // Function for generating a random G(n,l) graph
  void generateRandomNL(unsigned int minVertices, unsigned int maxVertices, unsigned int minEdges, unsigned int maxEdges,  int& generatedVertices, int& generatedEdges);
  // Function for generating a random G(n,p) graph
  void generateRandomNP(unsigned int minVertices, unsigned int maxVertices, unsigned int minProbability, unsigned int maxProbability,  int& generatedVertices, int& generatedProbability);

  // Function for generating a random degree sequence
  static std::vector<unsigned int> makeRandomDegreeSequence(const unsigned int length);
  // Function checking if it's parameter is a degree sequence
  static bool isDegreeSequence(std::vector<unsigned int> sequence);

  // Function for finding connected components. Returns a vector which numbers every node according to
  // which component they belong to
  std::vector<int> findComponents();
  // Helper function for finding components which performs recursive depth-first search
  void depthFirstComponent(unsigned int counter, unsigned int node, std::vector<int>& components);
  // Function that returns a vector of nodes belonging to the biggest component
  std::vector<unsigned int> biggestComponent();

  // Function for generating random k-regular graphs
  // It generates a new adjacency list
  // Changes type to undirected graph
  void generateRandomRegular(unsigned int minVertices, unsigned int maxVertices, unsigned int neighbours);

  // Hamiltonian cycle functions.
  bool checkHamiltonianCycle();
  bool hamiltonianCycleUtil(std::vector<int>& path, unsigned int pos);
  bool hamiltonianCanAdd(unsigned int vertex, std::vector<int>& path, unsigned int pos);
  void printHamiltonianCycle(std::vector<int>& cycle);

  // Eulerian graphs
  static bool isEulerianSequence(std::vector<unsigned int> sequence);
  bool areConnected(unsigned int rows);
  void DFSUtil(unsigned int v, bool visited[], std::vector<std::vector<int>> matrixData);
  int isEulerianCycle();

  // Randomizing function
  void randomize();

  // Function creating empty weights matrix
  void createWeights();
  // Function creating empty flows and capacities
  void createFlowsAndCapacities();
  // Function for generating random weights for each edge
  void generateRandomWeights(int minWeight, int maxWeight);
  // Function for generating random capacity values for each edge
  void generateRandomCapacities(int minCapacity, int maxCapacity);
  // Getter function which returns weight of an edge between source and dest. Returns -1 if such edge isn't registered in the 'weights' vector
  int getWeight(unsigned int source, unsigned int dest);
  // Setter function which assigns a new weight to an edge between source and dest.
  // If such edge isn't registered in the 'weights' vector, a new value will be added
  void setWeight(unsigned int source, unsigned int dest, int weight);
  // Function which synchronizes 'weights' with the actual graph, deleting weights for edges that don't exist anymore
  // and adding new weights for unregistered edges with a value of 0
  void updateWeights();
  // Print weights along with their edges
  void printWeights() const;
  // Below functions are getters and setters for flow and capacity values
  int getFlow(unsigned int source, unsigned int dest) { return getWeight(source, dest); }
  void setFlow(unsigned int source, unsigned int dest, int flow) { setWeight(source, dest, flow); }
  int getCapacity(unsigned int source, unsigned int dest);
  void setCapacity(unsigned int source, unsigned int dest, int capacity);
  // Print flows and capacities
  void printFlowsAndCapacities() const;

  // Functions used for finding shortest distances. Returns a vector of shortest distances to every vertex
  // If print is true, both shortest paths and distances will be printed
  std::vector<int> Dijkstra(unsigned int startVertex, bool print);
  int minDistance(std::vector<bool> visited, std::vector<int> distance);

  // Distance matrix, center of the graph and minimax center of the graph
  void minDistances();

  // Minimum spanning tree using Prim's algorithm Functions
  void primMST();
  void printMST(std::vector<int> parent);
  int minKey(std::vector<int> key, std::vector<bool> mstSet, unsigned int rows);

  // Strongly connected components, Kosaraju
  std::vector<int> Kosaraju();
  void visitDFS(unsigned int vertex, std::vector<int>& timeVisited, std::vector<int>& timeProcessed, unsigned int& times);
  Graph transpose();
  std::vector<unsigned int> getNeighbours(unsigned int vertex);
  void addComponents(unsigned int& componentNumber, unsigned int vertex, std::vector<int>& components);
  void setConverter(Converter* conv) { matrixConverter = conv; }


  void Johnson();
  // Wrapper function used to create a new vertex connected to every other vertex with a weight of 0
  void addS();
  std::vector<int> BellmanFord(int startVertex);
  int check;

  // Function for generating a random flow network
  void randomFlowNetwork(unsigned int layers);

  bool BFS(std::vector<unsigned int>& path);
  void FordFulkerson();
    
  // Function which returns a vector of vertices belonging to a specific layer
  std::vector<unsigned int> verticesFromLayer(unsigned int layer);
private:
  Matrix* matrix;
  Converter* matrixConverter;
  std::vector<std::vector<int>> weights;

  // Stores the number of layer for each vertex
  std::vector<unsigned int> vertexLayer;
  unsigned int numOfLayers;

  void setConverter(const RepresentationType &forMatrixType);
};
