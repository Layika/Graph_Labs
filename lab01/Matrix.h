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

class Matrix {
public:
  // TODO: Any matrix will be converted to adjacency list because Python script uses this format
  void saveAdjList(std::string fileName);

  // Getters for matrix
  RepresentationType getRepresentationType() { return type; }
  unsigned int getRows() const { return data.size(); }
  unsigned int getColumns(unsigned int row) const { return data[row].size(); }
  int getElement(unsigned int row, unsigned int col) const { return data[row][col]; }

  // Setters for matrix
  void saveData(std::vector<std::vector<int>> newData) { data.clear(); data = newData; }
  void setType(RepresentationType newType) { type = newType; }
  void setElement(std::vector<unsigned int> idx, int el) { data[idx[0]][idx[1]] = el; }

  // Helper function used in converter functions
  // Might be useful for future operations on matrices
  // adjListToAdjMat
  bool isInRow(unsigned int row, int el) { return std::find(data[row].begin(),data[row].end(), el) != data[row].end(); }
  // incMatToAdjMat
  std::vector<unsigned int> findElement(int el);
  unsigned int findInCol(unsigned int col, int el);
  long numberOfOccurences(int el);

  // Debug printing function for matrices
  void print() const;

private:
  std::vector<std::vector<int>> data;
  RepresentationType type;
};
