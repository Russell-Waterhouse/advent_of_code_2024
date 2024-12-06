#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

struct Point {
    unsigned long int x;
    unsigned long int y;
    Point(unsigned long int x1, unsigned long int y1): x {x1}, y {y1} {}
};

inline bool operator<(const Point& p1, const Point& p2) {
  if (p1.x < p2.x) {
    return true;
  }
  if (p1.x > p2.x) {
    return false;
  }
  return p1.y < p2.y;
}

inline bool operator==(const Point& p1, const Point&p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

enum class Direction {
  kUp,
  kDown,
  kRight,
  kLeft
};

class Guard {
  public:
    unsigned long int m_num_positions;
    Direction m_direction;
    unsigned long int m_x; // string index
    unsigned long int m_y; // vector index
    std::vector<Point> positions;

    Guard(): m_num_positions {0}, m_direction {Direction::kUp}, m_x {0}, m_y {0}, positions {} {
      positions.push_back(Point(m_x, m_y));
    }

    // Returns true when it walks off the map
    unsigned long int update(std::vector<std::string> map) {
      size_t height = map.size();
      size_t width = map.at(0).size();
      switch (m_direction) {
        case Direction::kUp:
          if (m_y == 0) {
            // return m_num_positions;
            return positions.size();
          }
          if (map.at(m_y - 1).at(m_x) == '#') {
            m_direction = Direction::kRight;
            break;
          }
          m_y--;
          // m_num_positions++;
          positions.push_back(Point(m_x, m_y));
          break;
        case Direction::kDown:
          if (m_y == height - 1) {
            // return m_num_positions;
            return positions.size();
          }
          if (map.at(m_y + 1).at(m_x) == '#') {
            m_direction = Direction::kLeft;
            break;
          }
          m_y++;
          // m_num_positions++;
          positions.push_back(Point(m_x, m_y));
          break;
        case Direction::kRight:
          if (m_x == width - 1) {
            // return m_num_positions;
            return positions.size();
          }
          if (map.at(m_y).at(m_x + 1) == '#') {
            m_direction = Direction::kDown;
            break;
          }
          m_x++;
          // m_num_positions++;
          positions.push_back(Point(m_x, m_y));
          break;
        case Direction::kLeft:
          if (m_x == 0) {
            // return m_num_positions;
            return positions.size();
          }
          if (map.at(m_y).at(m_x - 1) == '#') {
            m_direction = Direction::kUp;
            break;
          }
          m_x --;
          // m_num_positions++;
          positions.push_back(Point(m_x, m_y));
          break;
          // should never be here
          throw new std::exception;
      }
      std::sort(positions.begin(), positions.end());
      std::cout << positions.size() << "(" << m_y << "," << m_x << ")\n";
      positions.erase( std::unique( positions.begin(), positions.end()), positions.end());
      std::cout << positions.size() << "(" << m_y << "," << m_x << ")\n";
      return 0;
    }
};

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

  size_t x {0};
  size_t y {0};
  Guard guard {};
  for (y = 0; y < rawInput.size(); y++) {
    for (x = 0; x < rawInput.size(); x++) {
      if (rawInput.at(y).at(x) == '^') {
        guard.m_y = y;
        guard.m_x = x;
      }
    }
  }

  unsigned long int guardUpdate {0};
  while (guardUpdate == 0) {
    guardUpdate = guard.update(rawInput);
  }

  std::cout << "The answer to part 1 is: " << guardUpdate - 1 << std::endl;

  return 0;
}
