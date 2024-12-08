#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "aoc_helper.hpp"

void add_antinode_to_map(size_t i, size_t j, std::vector<std::string>& antinode_map) {
  if (i < antinode_map.size() && j < antinode_map.at(0).size()) {
    antinode_map.at(i).at(j) = '1';
  }
}

void add_antinode_for_points(size_t i, size_t j, size_t a, size_t b, std::vector<std::string>& antinode_map) {
  size_t bigger_x {i > a ? i : a};
  size_t smaller_x {i < a ? i : a};
  size_t bigger_y {j > b ? j : b};
  size_t smaller_y {j < b ? j : b};
  size_t delta_x {bigger_x - smaller_x};
  size_t delta_y {bigger_y - smaller_y};
  size_t bigger_antinode_x = bigger_x + delta_x;
  size_t bigger_antinode_y = bigger_y + delta_y;
  if (i < a && j < b) {
    add_antinode_to_map(bigger_antinode_x, bigger_antinode_y, antinode_map);
    if (smaller_y >= delta_y && smaller_x >= delta_x) {
      add_antinode_to_map(smaller_x - delta_x, smaller_y - delta_y, antinode_map);
    }
  } else {
    if (smaller_y >= delta_y) {
      add_antinode_to_map(bigger_antinode_x, smaller_y - delta_y, antinode_map);
    }
    if (smaller_x >= delta_x) {
      add_antinode_to_map(smaller_x - delta_x, bigger_antinode_y, antinode_map);
    }
  }
}

void add_all_antinodes_for_point(size_t i, size_t j, std::vector<std::string>& tower_map, std::vector<std::string>& antinode_map) {
  char freq = tower_map.at(i).at(j);
  for(size_t a {i}; a < tower_map.size(); a++) {
    size_t start {0};
    if (a == i) {
      start = j + 1;
    }
    for (size_t b {start}; b < tower_map.size(); b++) {
      if (tower_map.at(a).at(b) == freq) {
        std::cout << "Found pair at (" << i << "," << j << ") and (" << a << "," << b << ")\n";
        add_antinode_for_points(i, j, a, b, antinode_map);
      }
    }
  }
}

int num_antinodes(std::vector<std::string>& tower_map) {
  std::vector<std::string> antinode_map {};
  for (size_t i {0}; i < tower_map.size(); i++) {
    std::string s(tower_map.at(0).size(), '0');
    antinode_map.push_back(s);
  }

  for (size_t i {0}; i < tower_map.size(); i++) {
    for (size_t j {0}; j < tower_map.at(0).size(); j++) {
      if (tower_map.at(i).at(j) != '.') {
        add_all_antinodes_for_point(i, j, tower_map, antinode_map);
      }
    }
  }

  int node_cnt {0};
  for (auto& line: antinode_map) {
    for (auto& ch: line) {
      if (ch == '1') {
        node_cnt++;
      }
    }
  }
  return node_cnt;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "No argument given, exiting" << std::endl;
    return 0;
  }
  std::vector<std::string> rawInput = parseInput(argv[1]);
  
  int cnt = num_antinodes(rawInput);
  std::cout << "The answer to part 1 is: " << cnt << std::endl;
  
  return 0;
}
