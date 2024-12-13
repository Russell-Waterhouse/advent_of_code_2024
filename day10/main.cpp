#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "aoc_helper.hpp"
#include <stack>
#include <set>


template <typename T>
void print_vector(std::vector<T>& vec) {
  for (auto& v : vec) {
    std::cout << v << " \n";
  }
  std::cout << std::endl;
}

std::vector<int> string_to_ints(std::string& s) {
  std::vector<int> v {};
  for (size_t i {0}; i < s.size(); i++) {
    std::string substr = s.substr(i, 1);
    v.push_back(std::stoi(substr));
  }
  return v;
}

struct Point {
  size_t x;
  size_t y;
  Point(size_t x_param, size_t y_param): x {x_param}, y {y_param} {};
};

bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Point& lhs, const Point& rhs) {
  if (lhs.x == rhs.x) {
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}

class Tree {
  public:
    size_t mx;
    size_t my;
    size_t mx_prev;
    size_t my_prev;
    Tree(size_t x, size_t y, size_t x_prev, size_t y_prev): mx {x}, my {y}, mx_prev {x_prev}, my_prev {y_prev} {};

    std::set<Point> trailhead_endpoints(std::vector<std::vector<int>>& map) {
      std::stack<Tree> stack {};
      int this_node = map.at(mx).at(my);
      // std::cout << "This node value is " << this_node << std::endl;
      if (this_node == 9) {
        std::cout << "Found a leaf node at " << mx << ", " << my << "From " << mx_prev << ", " << my_prev << std::endl;
        std::set<Point> set {};
        set.insert(Point(mx, my));
        return set;
      }
      int next_node = this_node + 1;
      if (mx > 0 && map.at(mx-1).at(my) == next_node) {
        stack.push(Tree(mx-1, my, mx, my));
      }
      if (my > 0 && map.at(mx).at(my-1) == next_node) {
        stack.push(Tree(mx, my-1, mx, my));
      }
      if(mx < map.size() - 1 && map.at(mx+1).at(my) == next_node) {
        stack.push(Tree(mx+1, my, mx, my));
      }
      if(my < map.at(0).size() - 1 && map.at(mx).at(my+1) == next_node) {
        stack.push(Tree(mx, my+1, mx, my));
      }

      std::set<Point> endpoints {};
      while (stack.size() > 0) {
        endpoints.merge(stack.top().trailhead_endpoints(map));
        stack.pop();
      }

      return endpoints;
    }

};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "No argument given, exiting" << std::endl;
    return 0;
  }
  std::vector<std::string> rawInput = parseInput(argv[1]);
  std::vector<std::vector<int>> map {};
  for (std::string& s: rawInput) {
    map.push_back(string_to_ints(s));
  }

  size_t part_1 {0};
  for (size_t i {0}; i < map.size(); i++) {
    for (size_t j {0}; j < map.at(0).size(); j++) {
      if (map.at(i).at(j) == 0) {
        part_1 += Tree(i, j, 99, 99).trailhead_endpoints(map).size();
      }
    }
  }
  std::cout << "The answer to part 1 is: " << part_1 << std::endl;
  
  int part_2 {0};
  std::cout << "The answer to part 2 is: " << part_2 << std::endl;
  return 0;
}
