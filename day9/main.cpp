#include <cassert>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include "aoc_helper.hpp"


template <typename T>
void print_vector(std::vector<T>& vec) {
  for (auto& v : vec) {
    std::cout << v << " \n";
  }
  std::cout << std::endl;
}

std::unique_ptr<std::vector<std::optional<unsigned int>>> print_expanded(std::unique_ptr<std::vector<std::optional<unsigned int>>> expanded) {
  for (size_t i {0}; i < expanded->size(); i++) {
    if(expanded->at(i).has_value()) {
      std::cout << "(" << (expanded->at(i)).value() << ")";
    } else {
      std::cout << ".";
    }
  }
  std::cout << std::endl;
  return expanded;
}


unsigned long int calculate_checksum(std::unique_ptr<std::vector<std::optional<unsigned int>>> expanded_sorted_drive) {
  unsigned long int checksum {0};
  for (unsigned int i {0}; i < expanded_sorted_drive->size(); i++){
    if (expanded_sorted_drive->at(i).has_value()) {
      checksum += expanded_sorted_drive->at(i).value() * i;
    }
  }
  return checksum;
}

std::unique_ptr<std::vector<std::optional<unsigned int>>> sort_expanded_drive2(std::unique_ptr<std::vector<std::optional<unsigned int>>> expanded) {
  size_t back_idx {expanded->size() - 1};
  size_t front_idx {0};
  while (back_idx > front_idx ) {
    if (!expanded->at(back_idx).has_value()) {
      back_idx--;
      continue;
    }
    if (expanded->at(front_idx).has_value()) {
      front_idx++;
      continue;
    }
    expanded->at(front_idx) = expanded->at(back_idx);
    expanded->at(back_idx) = {};
    back_idx--;
  }
  return print_expanded(std::move(expanded));
}

std::unique_ptr<std::vector<std::optional<unsigned int>>> sort_expanded_drive(std::unique_ptr<std::vector<std::optional<unsigned int>>> expanded) {
  size_t back_idx {expanded->size() - 1};
  size_t front_idx {0};
  while (back_idx > front_idx ) {
    if (!expanded->at(back_idx).has_value()) {
      back_idx--;
      continue;
    }
    if (expanded->at(front_idx).has_value()) {
      front_idx++;
      continue;
    }
    expanded->at(front_idx) = expanded->at(back_idx);
    expanded->at(back_idx) = {};
    back_idx--;
  }
  return print_expanded(std::move(expanded));
}

std::unique_ptr<std::vector<std::optional<unsigned int>>> expand_drive(std::vector<std::string>& input) {
  assert(input.size() == 1);
  std::string s = input.at(0);
  auto expanded = std::make_unique<std::vector<std::optional<unsigned int>>>();
  for (unsigned int i {0}; i < s.size(); i++) {
    char c = s.at(i);
    unsigned long int size = std::stoul(std::string(1, c));
    for (size_t j = 0; j < size; j++) {
      if (i % 2 == 0) {
        unsigned int file_idx = i / 2;
        expanded->push_back(file_idx);
      } else {
        expanded->push_back({});
      }
    }
  }

  return print_expanded(std::move(expanded));;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "No argument given, exiting" << std::endl;
    return 0;
  }
  std::vector<std::string> rawInput = parseInput(argv[1]);
  
  auto expanded = expand_drive(rawInput);
  auto sorted_expanded_drive = sort_expanded_drive(std::move(expanded));
  unsigned long int part_1 {calculate_checksum(std::move(sorted_expanded_drive))};
  std::cout << "The answer to part 1 is: " << part_1 << std::endl;
  
  auto expanded2 = expand_drive(rawInput);
  auto sorted_expanded_drive2 = sort_expanded_drive2(std::move(expanded2));
  unsigned long int part_2 = calculate_checksum(std::move(sorted_expanded_drive2));
  std::cout << "The answer to part 2 is: " << part_2 << std::endl;
  return 0;
}
