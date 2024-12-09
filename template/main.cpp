#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "aoc_helper.hpp"


template <typename T>
void print_vector(std::vector<T>& vec) {
  for (auto& v : vec) {
    std::cout << v << " \n";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "No argument given, exiting" << std::endl;
    return 0;
  }
  std::vector<std::string> rawInput = parseInput(argv[1]);
  
  int part_1 {0};
  std::cout << "The answer to part 1 is: " << part_1 << std::endl;
  
  int part_2 {0};
  std::cout << "The answer to part 2 is: " << part_2 << std::endl;
  return 0;
}
