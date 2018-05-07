#include "Matrix.h"

#include <sstream>
#include <iterator>

void Matrix::saveAdjList(std::string fileName) {
  std::ofstream outfile(fileName);

  for (unsigned int i=0; i<data.size(); ++i) {

    for (unsigned int j=0; j<data[i].size(); ++j) {
      outfile << data[i][j];
      if (j!=data[i].size()-1) outfile << " ";
    }

    outfile << std::endl;
  }

  outfile.close();
}

void Matrix::print() const {
  for(auto row : data) {
    for(auto col : row) std::cout << col << ' ';
    std::cout << std::endl;
  }
}
