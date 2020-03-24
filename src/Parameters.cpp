#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "const.h"
#include "utils.h"
#include "Parameters.h"

Parameters::Parameters() {
  
}

Parameters::~Parameters() {

}

void Parameters::init() {
  zNames.clear();
  zValues.clear();
}

void Parameters::read_line(std::string line) {
  std::vector < std::string > words =
    utils::split(utils::remove_comment(line), ' ');

  if (words.size() > 0) {
    if (name_occurs(words.front())) {
      throw std::invalid_argument(
        "Parameter name must occur only once."
      );
    }

    zNames.push_back(words.front());
    words.erase(std::begin(words));
    zValues.push_back(words);
  }
}

int Parameters::name_occurs(std::string name) {
  return (
    std::find(
      zNames.begin(),
      zNames.end(),
      name
    )
    != zNames.end()
  );
}

std::vector < std::string > Parameters::get_values(
 std::string name) {
  for ( unsigned int i = 0; i < zNames.size(); i++ ) {
    if (zNames[i] == name) {
      return zValues[i];
    }
  }
  throw std::invalid_argument(
    "Parameter name does not occur."
  );
}

void Parameters::read_file(std::string filename) {
  std::ifstream file(filename.c_str());

  init();

  if ( ! file ) {
    throw std::invalid_argument(
      "File not found: parameter file"
    );
  }

  std::string line;
  while ( getline(file, line) ) {
    read_line(line);
  }

}
