#include <cstdlib>
#include <iostream>
#include <fstream>
#include <optional>
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
    tokens.push_back(token);
    input.erase(0, pos + delimiter.size());
    i++;
    // print_vector(tokens);
  } while (i < 100);
  tokens.push_back(input);
  // print_vector(tokens);
  return tokens;
}

enum class Operator {
  kAdd,
  kMultiply,
  kConcat
};

void print_vector(std::vector<Operator>& ops) {
  for(auto& op: ops) {
    switch(op) {
      case Operator::kAdd:
        std::cout << " + ";
        break;
      case Operator::kMultiply:
        std::cout << " * ";
        break;
      case Operator::kConcat:
        std::cout << " || ";
        break;
    }
  }
  std::cout << std::endl;
}

std::optional<Operator> nextOperator(Operator& op) {
  switch(op) {
    case Operator::kAdd:
      return Operator::kMultiply;
    case Operator::kMultiply:
      return Operator::kConcat;
    case Operator::kConcat:
      return {};
  }
  return {};
}

// 0 0 0
// 0 0 1
// 0 0 2
// 0 1 0
// 0 1 1
// 0 1 2
// 0 2 0
// 0 2 1
// 0 2 2
// 1 0 0
// 1 0 0
// 1 0 1
// 1 0 2
// 1 1 0
// 1 1 1
// 1 1 2
// 1 2 0
// 1 2 1
// 1 2 2
// 2 0 0

std::optional <std::vector<Operator>> nextIteration(std::vector<Operator> operators) {
  for (size_t i {operators.size() - 1}; i <= 100; i--) {
    std::optional<Operator> next_op = nextOperator(operators.at(i));
    if (next_op.has_value()) {
      operators.at(i) = next_op.value();
      if ( i < operators.size() - 2) {
        // go back through and reset all less significant bits to zero
        for (size_t j {i + 1}; j < operators.size(); j++) {
          operators.at(j) = Operator::kAdd;
        }
      }

      return operators;
    }
  }

  return {};
}

class Equation{
  public:
    std::vector<long int> right;
    long int left;
    std::string line;

    Equation(std::string inputLine): right {}, left {}, line {inputLine}{
      std::vector<std::string> tokens = split(inputLine, " ");
      tokens.at(0).erase(tokens.at(0).size()); // remove the colon
      left = std::stol(tokens.at(0));
      for(size_t i {1}; i < tokens.size(); i++) {
        right.push_back(std::stol(tokens.at(i)));
      }
    }

    long int validEquationSum() {
      size_t exp = right.size() - 1;
      double num_choices = std::pow(2, exp);
      for (int i {0}; i < num_choices; i++) {
        long int test_right {right.at(0)};
        for (size_t j {0}; j < right.size() - 1; j++) {
          int jj = int(j);
          // use the bits of i to decide whether to multiply or divide
          if (((i >> jj) & 0b01)) {
            // multiply
            test_right = test_right * right.at(j + 1);
          } else {
            // add
            test_right = test_right + right.at(j + 1);
          }
        }
        if (test_right == left) {
          return left;
        }
      }
      return 0;
    }

    long int calculateEquation(std::vector<Operator>& operators) {
      if (operators.size() == 0) {
        // throw new std::exception;
      }
      long int calculation {right.at(0)};
      for(size_t i {1}; i < right.size(); i++) {
        switch (operators.at(i - 1)) {
          case Operator::kAdd:
            calculation += right.at(i);
            break;
          case Operator::kMultiply:
            calculation *= right.at(i);
            break;
          case Operator::kConcat:
            std::string s {std::to_string(calculation)};
            s.append(std::to_string(right.at(i)));
            calculation = std::stoi(s);
            break;
        }
      }
      if (left == calculation) {
        return left;
      }
      return 0;
    }

    long int validEquationSum2() {
      std::vector<Operator> ops {};
      std::optional<std::vector<Operator>> operators {ops};
      for (size_t i {0}; i < right.size() - 1; i++) {
        operators.value().push_back(Operator::kAdd);
      }
      size_t i {0};
      // if (!operators.has_value()) {
        // throw new std::exception;
      // }
      if (operators.value().size() < 1) {
        throw new std::exception;
      }
      do {
        i++;
        long int result = calculateEquation(operators.value());
        if (result != 0) {
          std::cout << "The result is " << result << " For Array: ";
          print_vector(right);
          print_vector(operators.value());
          return result;
        }
        operators = nextIteration(operators.value());
      } while (operators.has_value());
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
    equations.push_back(e);
  }

  long int validEquationSum {0};
  for (auto equation: equations) {
    validEquationSum += equation.validEquationSum();
  }

  std::cout << "The answer to part 1 is: " << validEquationSum << std::endl;

  long int part2EquationSum {0};
  for (auto equation: equations) {
    part2EquationSum += equation.validEquationSum2();
  }

  std::cout << "The answer to part 2 is: " << part2EquationSum << std::endl;
  return 0;
}
