#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    std::cout << "Token is " << token << std::endl;
    tokens.push_back(token);
    input.erase(0, pos + delimiter.size());
    i++;
  } while (i < 100);
  tokens.push_back(input);
  return tokens;
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

  return 0;
}
