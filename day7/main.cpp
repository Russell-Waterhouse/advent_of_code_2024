#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

template <typename T>
void print_vector(std::vector<T>& vec) {
  for (auto& v : vec) {
    std::cout << v << ", ";
  }
  std::cout << std::endl;
}

std::vector<std::string> split(std::string input, std::string delimiter) {
  std::vector<std::string> tokens {};
  size_t pos {0};
  int i {0};
  do {
    pos = input.find(delimiter);
    if (pos == std::string::npos) {
      break;
    }
    std::string token = input.substr(0, pos);
    // std::cout << "Token is " << token << std::endl;
    tokens.push_back(token);
    input.erase(0, pos + delimiter.size());
    i++;
    // print_vector(tokens);
  } while (i < 100);
  // // std::cout << "Made it out of the loop" << std::endl;
  tokens.push_back(input);
  // std::cout << "Returning" << std::endl;
  // print_vector(tokens);
  return tokens;
}

class Equation{
  public:
    std::vector<int> right;
    int left;
    std::string line;

    Equation(std::string inputLine): right {}, left {}, line {inputLine}{
      std::vector<std::string> tokens = split(inputLine, " ");
      // std::cout << "In the constructor" << std::endl;
      tokens.at(0).erase(tokens.at(0).size()); // remove the colon
      // std::cout << "In the constructor further" << std::endl;
      left = std::stoi(tokens.at(0));
      for(size_t i {1}; i < tokens.size(); i++) {
        right.push_back(std::stoi(tokens.at(i)));
      }
    }

    int validEquationSum() {
      size_t exp = right.size() - 2;
      double num_choices = std::pow(2, exp);
      for (int i {0}; i < num_choices; i++) {
        int test_right {0};
        for (size_t j {0}; j < right.size(); j++) {
          int jj = int(j);
        }
      }
      return 0;
    }
};

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

  std::vector<Equation> equations {};
  for (auto line: rawInput) {
    Equation e {line};
    // std::cout << "Got returned" << std::endl;
    equations.push_back(e);
  }

  int validEquationSum {0};
  for (auto equation: equations) {
    validEquationSum += equation.validEquationSum();
  }

  std::cout << "The answer to part 1 is: " << validEquationSum << std::endl;



  return 0;
}
