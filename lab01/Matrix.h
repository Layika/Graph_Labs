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

  void print() const;

  void clearData() { data.clear(); }
  RepresentationType getRepresentationType() { return type; }

  unsigned int getRows() const { return data.size(); }
  unsigned int getColumns(unsigned int row) const { return data[row].size(); }
  int getElement(unsigned int row, unsigned int col) const { return data[row][col]; }
  void saveData(std::vector<std::vector<int>> newData) { data.clear(); data = newData; }
  void saveType(RepresentationType newType) { type = newType; }
  void setElement(std::vector<int> idx, int el) { data[idx[0]][idx[1]] = el; }

  // adjListToAdjMat
  bool isInRow(unsigned int row, int el) { return std::find(data[row].begin(),data[row].end(), el) != data[row].end(); }

  // incMatToAdjMat
  std::vector<unsigned int> findElement(int el) {
    std::vector<unsigned int> v;
    for(unsigned int row = 0; row < getRows(); ++row) {
      auto column = std::find(data[row].begin(),data[row].end(), el);
      if (column !=  data[row].end()){
        v.push_back(row);
        v.push_back(column);
        return v;
      }
    }

    return v;
  }
  unsigned int findInCol(unsigned int col, int el) {
    unsigned int idx = 0;
    for (unsigned int row=0; row<getRows(); ++row) {
      if (data[row][col] == el) idx=row;
    }
    return idx;
  }

private:
  std::vector<std::vector<int>> data;
  RepresentationType type;
};
