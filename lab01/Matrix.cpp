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

void Matrix::readFile(std::string fileName) {
  data.clear();

  // Open file with a matrix
  // Throw an exception if file fails to open
  std::ifstream dataFile(fileName);
  if (dataFile.fail()) { /* TODO: exception */ }

  // Now we need to be able to tell what matrix are we reading from file
  // TODO: describe how it tells what kind of matrix was read
  size_t rowWidth = -1;

  std::string line;
  while(getline(dataFile, line)) {
    std::istringstream lineStream(line);

    data.emplace_back(std::istream_iterator<int>(lineStream), std::istream_iterator<int>());

    if(rowWidth == -1) rowWidth = data.back().size();
    else if(rowWidth != data.back().size()) rowWidth = -2;

  }

  // Save type
  if (rowWidth == data.size()) {
      std::cout << "adjacency matrix" << std::endl;
      type = AdjacencyMatrix;
  } else if (rowWidth == -2) {
      std::cout << "adjacency list" << std::endl;
      type = AdjacencyList;
  } else {
      std::cout << "incidence matrix" << std::endl;
      type = IncidenceMatrix;
  }


  dataFile.close();
}
