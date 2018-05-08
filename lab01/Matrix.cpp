#include "Matrix.h"

#include <sstream>
#include <iterator>

void Matrix::saveAdjList(std::string fileName) {
  // Open out file
  std::ofstream outfile(fileName);

  // Write there formated data
  for (unsigned int i=0; i<data.size(); ++i) {
    for (unsigned int j=0; j<data[i].size(); ++j) {
      outfile << data[i][j];
      if (j!=data[i].size()-1) outfile << " ";
    }

    outfile << std::endl;
  }

  // Close the file
  outfile.close();
}

void Matrix::print() const {
  for(auto row : data) {
    for(auto col : row) std::cout << col << ' ';
    std::cout << std::endl;
  }
}

unsigned int Matrix::findInCol(unsigned int col, int el) {
  unsigned int idx = 0;
  for (unsigned int row=0; row<getRows(); ++row) {
    if (data[row][col] == el) idx=row;
  }
  return idx;
}

std::vector<unsigned int> Matrix::findElement(int el) {
  std::vector<unsigned int> v;
  for(unsigned int row = 0; row < getRows(); ++row) {
    auto colIter = std::find(data[row].begin(),data[row].end(), el);
    int column = std::distance(data[row].begin(), colIter);
    if (column <  data[row].size()){
      v.push_back(row);
      v.push_back(column);
      return v;
    }
  }

  return v;
}

long Matrix::numberOfOccurences(int el) {
  long count = 0;
  for(unsigned int row = 0; row < getRows(); ++row) {
    count += std::count(data[row].begin(), data[row].end(), el);
  }

  return count;
}

unsigned int Matrix::numberOfElements() {
    unsigned int number = 0;
    for(auto &row: data) {
        number += row.size();
    }

    return number;
}
