#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// x and y are the coords of the 'A' we're looking at.
int read_mas_in_x_shape(std::vector<std::string>& puzzle, size_t x, size_t y) {
  try {
    if (puzzle.at(x).at(y) == 'A'
        && puzzle.at(x-1).at(y-1) == 'M'
        && puzzle.at(x+1).at(y+1) == 'S'
        && puzzle.at(x+1).at(y-1) == 'M'
        && puzzle.at(x-1).at(y+1) == 'S'
       ) {
      // m m
      //  a
      // s s
      return 1;
    }
    if (puzzle.at(x).at(y) == 'A'
        && puzzle.at(x-1).at(y-1) == 'S'
        && puzzle.at(x+1).at(y+1) == 'M'
        && puzzle.at(x+1).at(y-1) == 'S'
        && puzzle.at(x-1).at(y+1) == 'M'
       ) {
      // S S
      //  A
      // M M
      return 1;
    }
    if (puzzle.at(x).at(y) == 'A'
        && puzzle.at(x-1).at(y-1) == 'M'
        && puzzle.at(x+1).at(y+1) == 'S'
        && puzzle.at(x+1).at(y-1) == 'S'
        && puzzle.at(x-1).at(y+1) == 'M'
       ) {
      // M S
      //  A
      // M S
      return 1;
    }
    if (puzzle.at(x).at(y) == 'A'
        && puzzle.at(x-1).at(y-1) == 'S'
        && puzzle.at(x+1).at(y+1) == 'M'
        && puzzle.at(x+1).at(y-1) == 'M'
        && puzzle.at(x-1).at(y+1) == 'S'
       ) {
      // S M
      //  A
      // S M
      return 1;
    }
  } catch (...) {
    return 0;
  }
  return 0;

}

int countCrossingMas(std::vector<std::string>& puzzle) {
  int xmas_instance_cnt {0};
  size_t width = puzzle.size();
  size_t height = puzzle.at(0).size();
  std::cout << "Width is " << width << std::endl;
  std::cout << "Height is " << height << std::endl;
  for (size_t i {0}; i < height; i++) {
    for (size_t j {0}; j < width; j++) {
      if (puzzle.at(i).at(j) == 'A') {
        xmas_instance_cnt = xmas_instance_cnt + read_mas_in_x_shape(puzzle, i, j);
      }
    }
  }

  return xmas_instance_cnt;
}
// x and y are the coords of the 'X' we're looking at
int read_xmas_word(std::vector<std::string>& puzzle, size_t x, size_t y, int x_inc, int y_inc) {
  try {
    if (puzzle.at(x).at(y) == 'X'
        && puzzle.at(x + (1 * x_inc)).at(y + (1 * y_inc)) == 'M'
        && puzzle.at(x + (2 * x_inc)).at(y + (2 * y_inc)) == 'A'
        && puzzle.at(x + (3 * x_inc)).at(y + (3 * y_inc)) == 'S'
       ) {
      return 1;
    }
  } catch (...) {
    return 0;
  }
  return 0;
}

int countXmasInstances(std::vector<std::string>& puzzle) {
  int xmas_instance_cnt {0};
  size_t width = puzzle.size();
  size_t height = puzzle.at(0).size();
  std::cout << "Width is " << width << std::endl;
  std::cout << "Height is " << height << std::endl;
  for (size_t i {0}; i < height; i++) {
    for (size_t j {0}; j < width; j++) {
      if (puzzle.at(i).at(j) == 'X') {
        xmas_instance_cnt = xmas_instance_cnt 
          + read_xmas_word(puzzle, i, j, 1, 0) // read word forwardds
          + read_xmas_word(puzzle, i, j, -1, 0) // read word backawards
          + read_xmas_word(puzzle, i, j, 0, 1) // read word down
          + read_xmas_word(puzzle, i, j, 0, -1) // read word up
          + read_xmas_word(puzzle, i, j, 1, 1) // read word down forwards
          + read_xmas_word(puzzle, i, j, -1, -1) // read word up backwards
          + read_xmas_word(puzzle, i, j, 1, -1) // read word up forwards
          + read_xmas_word(puzzle, i, j, -1, 1); // read word down backwards
      }
    }
  }

  return xmas_instance_cnt;
}

int main(int argc, char *argv[]) {
   if (argc < 2) {
    std::cout << "No argument given, exiting" << std::endl;
    return 0;
  }
  std::string input_file_name = {argv[1]};
  std::ifstream inputFile(input_file_name);
  std::vector<std::string> rawInput {};
  std::string line {};
  while(std::getline(inputFile, line)) {
    if(line == "") {
      continue;
    }
    rawInput.push_back(line);
  }
  inputFile.close();

  std::vector<std::string>& puzzle {rawInput};
  int cnt = countXmasInstances(puzzle);
  std::cout << "The answer to part 1 is: "<< cnt << std::endl;

  cnt = countCrossingMas(puzzle);
  std::cout << "The answer to part 2 is: " << cnt << std::endl;

  return 0;
}
