#include <set>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "aoc_helper.hpp"
#include <optional>


template <typename T>
void print_vector(std::vector<T>& vec) {
  for (auto& v : vec) {
    std::cout << v << " \n";
  }
  std::cout << std::endl;
}

class Plot {
  public:
    char letter;
    unsigned int perimeter;
    size_t mx;
    size_t my;
    bool left_edge;
    bool right_edge;
    bool top_edge;
    bool bottom_edge;
    Plot(size_t x, size_t y): mx {x}, my {y} {};
    Plot(size_t x, size_t y, std::vector<std::string>& map):
      letter {map.at(x).at(y)},
      perimeter {0},
      mx {x},
      my {y},
      left_edge {false},
      right_edge {false},
      top_edge {false},
      bottom_edge {false}
    {
      std::vector<int> idxs {-1, 1};
      if (x == 0 || map.at(x-1).at(y) != letter) {
        perimeter++;
        top_edge = true;
      }
      if (y == 0 || map.at(x).at(y-1) != letter) {
        perimeter++;
        left_edge = true;
      }
      if (x == map.size() -1 || map.at(x+1).at(y) != letter) {
        perimeter++;
        bottom_edge = true;
      }
      if (y == map.size() - 1 || map.at(x).at(y + 1) != letter) {
        perimeter++;
        right_edge = true;
      }
    };

    std::vector<Plot> adjacent_valid_leaves(std::vector<std::string>& map, std::set<Plot>& region) {
      std::vector<Plot> v {};
      if (mx != 0 && map.at(mx-1).at(my) == letter) {
        Plot p = Plot(mx-1, my, map);
        if (!region.contains(p)) {
          v.push_back(p);
        }
      }
      if (my != 0 && map.at(mx).at(my-1) == letter) {
        Plot p = Plot(mx, my-1, map);
        if (!region.contains(p)) {
          v.push_back(p);
        }
      }
      if (mx != map.size() -1 && map.at(mx+1).at(my) == letter) {
        Plot p = Plot(mx+1, my, map);
        if (!region.contains(p)) {
          v.push_back(p);
        }
      }
      if (my != map.size() - 1 && map.at(mx).at(my + 1) == letter) {
        Plot p = Plot(mx, my+1, map);
        if (!region.contains(p)) {
          v.push_back(p);
        }
      }

      return v;
    }

    void print() {
      std::cout << "Plot: " << letter << "; (" << mx << ","<<my<<")" << std::endl;
    }
};

inline bool operator<(const Plot& p1, const Plot& p2) {
  if(p1.mx < p2.mx) {
    return true;
  }
  if(p1.mx > p2.mx) {
    return false;
  }
  return p1.my < p2.my;
};

inline bool operator==(const Plot& p1, const Plot& p2) {
  return p1.mx == p2.mx && p1.my == p2.my;
}

class Region {
  public:
    char letter;
    std::set<Plot> plots; // probably has garbage in it by the end of the constructor?
    unsigned int perimeter;
    unsigned int area;
    unsigned int cost;
    unsigned int num_sides;
    unsigned int bulk_cost;
    Region(size_t x, size_t y, std::vector<std::string>& map):
      letter {map.at(x).at(y)},
      plots {},
      perimeter {0},
      area {0},
      cost {0},
      num_sides {0},
      bulk_cost {0}
    {
      std::queue<Plot> leaves {};
      Plot beginning = Plot(x, y, map);
      leaves.push(beginning);
      plots.insert(beginning);
      do {
        Plot leaf = leaves.front();
        for (Plot& new_leaf: leaf.adjacent_valid_leaves(map, plots)) {
          leaves.push(new_leaf);
          plots.insert(new_leaf);
        }
        leaves.pop();
      } while (leaves.size() > 0);
      for (size_t i {0}; i < map.size(); i++) {
        bool prev_was_top_edge = false;
        bool prev_was_bottom_edge = false;
        bool prev_was_left_edge = false;
        bool prev_was_right_edge = false;
        for (size_t j {0}; j < map.at(0).size(); j++) {
          // if (letter == 'C') { std::cout << << std::endl; }
          // scanning left to right
          Plot p = Plot(i, j, map);
          if (plots.contains(p)) {
            if (p.top_edge && !prev_was_top_edge) {
              num_sides++;
            }
            if (p.bottom_edge && !prev_was_bottom_edge) {
              num_sides++;
            }
            prev_was_bottom_edge = p.bottom_edge;
            prev_was_top_edge = p.top_edge;
          } else {
            prev_was_top_edge = false;
            prev_was_bottom_edge = false;
            if (letter == 'C') {
              // p.print();
            }
          }

          // flip i and j to scan top to bottom (input is square thank god)
          p = Plot(j, i, map);
          if (plots.contains(p)) {
            // if (letter == 'C') { std::cout << "Contains: " << j << "; " << i << std::endl; }
            if (p.left_edge && !prev_was_left_edge) {
              num_sides++;
            }
            if (p.right_edge && !prev_was_right_edge) {
              num_sides++;
            }
            prev_was_left_edge = p.left_edge;
            prev_was_right_edge = p.right_edge;
          } else {
            prev_was_left_edge = false;
            prev_was_right_edge = false;
            if (letter == 'C') {
              // p.print();
            }
          }
        }
      }
      for (Plot p: plots) {
        area++;
        perimeter += p.perimeter;
        map.at(p.mx).at(p.my) = '0'; // Mark this plot as handled
        if (letter == 'C') {
          // p.print();
        }
      }
      cost = perimeter * area;
      bulk_cost = area * num_sides;
    };

    void print() {
      std::cout << "Region: " << letter << "; Area: " << area << "; Perimeter: " << perimeter;
      std::cout << "; num_sides " << num_sides;
      std::cout << "; Cost: " << cost << "; bulk cost: " << bulk_cost << std::endl;
    }
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return 0;
  }
  std::vector<std::string> rawInput = parseInput(argv[1]);
  std::vector<Region> regions {};
  for (size_t i {0}; i < rawInput.size(); i++) {
    for (size_t j {0}; j < rawInput.at(0).size(); j++) {
      if (rawInput.at(i).at(j) != '0') {
        Region r = Region(i, j, rawInput);
        regions.push_back(r);
      }
    }
  }

  unsigned int part_1 {0};
  unsigned int part_2 {0};
  for (Region& region: regions) {
    part_1 += region.cost;
    part_2 += region.bulk_cost;
    region.print();
  }
  std::cout << "The answer to part 1 is: " << part_1 << std::endl;
  
  std::cout << "The answer to part 2 is: " << part_2 << std::endl;
  return 0;
}
