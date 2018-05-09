#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

enum RepresentationType {
  AdjacencyList,
  AdjacencyMatrix,
  IncidenceMatrix
};

enum GraphType {
  Undirected,
  Directed
};

class Matrix {
public:
  // Any matrix will be converted to adjacency list because Python script uses this format
  void saveAdjList(std::string fileName);

  // Getters for matrix
  RepresentationType getRepresentationType() { return representationType; }
  GraphType getGraphType() { return graphType; }
  unsigned int getRows() const { return data.size(); }
  unsigned int getColumns(unsigned int row) const { return data[row].size(); }
  int getElement(unsigned int row, unsigned int col) const { return data[row][col]; }

  // Setters for matrix
  void saveData(std::vector<std::vector<int>> newData) { data.clear(); data = newData; }
  void setRepresentationType(RepresentationType newType) { representationType = newType; }
  void setGraphType(GraphType newType) { graphType = newType; }

  // TODO: make this std::pair
  void setElement(std::vector<unsigned int> idx, int el) { data[idx[0]][idx[1]] = el; }
  void setElement(unsigned int x, unsigned int y, int el) { data[x][y] = el; }

  // Helper function used in converter functions
  // Might be useful for future operations on matrices
  bool isInRow(unsigned int row, int el) { return std::find(data[row].begin(),data[row].end(), el) != data[row].end(); }
  std::vector<unsigned int> findElement(int el);
  unsigned int findInCol(unsigned int col, int el);
  long numberOfOccurences(int el);
  unsigned int numberOfElements();

  // Function creating an empty adjacency matrix
  void createEmptyAdjacencyMat(unsigned int vertices);

  // Debug printing function for matrices
  void print() const;

private:
  std::vector<std::vector<int>> data;
  RepresentationType representationType;
  GraphType graphType;
};

class AbstractConverter {
  public:
    virtual void convertRepresentation(Matrix* matrix, RepresentationType to)=0;
    virtual ~AbstractConverter() {};
};

class AdjacencyListConverter: public AbstractConverter {
public:
    void convertRepresentation(Matrix* matrix, RepresentationType to) override;
    ~AdjacencyListConverter() override= default;

private:
    void adjListToAdjMat(Matrix *matrix);
    void adjListToIncMat(Matrix* matrix);
};


class AdjacencyMatrixConverter: public AbstractConverter {
public:
    void convertRepresentation(Matrix* matrix, RepresentationType to) override;
    ~AdjacencyMatrixConverter() override= default;

private:
    void adjMatToAdjList(Matrix* matrix);
    void adjMatToIncMat(Matrix* matrix);
};

class IncidenceMatrixConverter: public AbstractConverter {
public:
    void convertRepresentation(Matrix* matrix, RepresentationType to) override;
    ~IncidenceMatrixConverter() override= default;

private:
    void incMatToAdjMat(Matrix* matrix);
    void incMatToAdjList(Matrix* matrix);
};
