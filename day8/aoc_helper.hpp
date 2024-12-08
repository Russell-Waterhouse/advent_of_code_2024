#ifndef AOC_HELPERS
#define AOC_HELPERS

#include <vector>
#include <string>

template <typename T>
void print_vector(std::vector<T>& vec);

std::vector<std::string> split(std::string input, std::string delimiter);

std::vector<std::string> parseInput(const std::string& input_file_name);

#endif // !AOC_HELPERS
