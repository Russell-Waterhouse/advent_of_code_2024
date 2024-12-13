#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "aoc_helper.hpp"
#include <string>


template <typename T>
void print_vector(std::vector<T>& vec) {
  for (auto& v : vec) {
    std::cout << v << " \n";
  }
  std::cout << std::endl;
}

class Stone{
  public:
    size_t val;
    Stone(size_t initial): val{initial} {};

    std::vector<Stone*> update() {
      std::vector<Stone*> v {};
      if (val == 0) {
        val = 1;
        v.push_back(this);
        return v;
      }
      std::string digits = std::to_string(val);
      if (digits.size() % 2 == 0) {
        std::string left = digits.substr(0, digits.size() / 2);
        std::string right = digits.substr(digits.size() / 2, digits.size() / 2);
        val = std::stoull(left);
        Stone* newstone = new Stone(stoull(right));
        v.push_back(this);
        v.push_back(newstone);
        return v;
      }

      val *= 2024;
      v.push_back(this);
      return v;
    }
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "No argument given, exiting" << std::endl;
    return 0;
  }
  std::vector<std::string> rawInput = parseInput(argv[1]);
  assert(rawInput.size() == 1);

  std::string s = rawInput.at(0);
  std::vector<std::string> inputs = split(s, " ");
  std::vector<Stone*> stones {};
  for (auto& input: inputs) {
    Stone* s = new Stone(std::stoull(input));
    stones.push_back(s);
    // std::cout << "Added: " << s->val << std::endl;
  }

  for (size_t i {0}; i < 25; i++) {
    std::vector<std::vector<Stone*>> updated_stones {};
    for (auto * stone: stones) {
      updated_stones.push_back(stone->update());
    }
    stones.clear();
    for (auto & vec: updated_stones) {
      for (auto * stone: vec) {
        stones.push_back(stone);
      }
    }
    std::cout << "Finished iteration " << i << std::endl;
  }

  size_t part_1 {stones.size()};
  std::cout << "The answer to part 1 is: " << part_1 << std::endl;
  
  int part_2 {0};
  std::cout << "The answer to part 2 is: " << part_2 << std::endl;

  for (auto* s: stones) {
    delete s;
  }
  return 0;
}
