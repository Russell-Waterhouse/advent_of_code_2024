#include <cstdlib>
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>

class Rule {
public:
  int m_first;
  int m_second;
  Rule(int first, int second): m_first {first}, m_second {second} {

  }

  bool is_valid(std::vector<int>& update_pages) {
    std::optional<unsigned long int> index_of_first {};
    std::optional<unsigned long int> index_of_second {};
    int x;
    for (unsigned long int i {0}; i < update_pages.size(); i++) {
      x = update_pages.at(i);
      if (x == m_first && !index_of_first.has_value()) {
        index_of_first = i;
      }
      if (x == m_second && !index_of_second.has_value()) {
        index_of_second = i;
      }
    }
    bool has_valid_values = index_of_first.has_value()
          && index_of_second.has_value()
          && index_of_first.value() < index_of_second.value();
    bool has_no_values = !index_of_first.has_value() || !index_of_second.has_value();


    return has_no_values || has_valid_values;
  }
};

class Update {
public:
  std::vector<Rule>& m_rules;
  std::vector<int> m_pages;
  Update(std::vector<Rule> rules, std::vector<int> pages): m_rules {rules}, m_pages {pages} {

  }

  int isValid() {
    for (auto rule: m_rules) {
      if (!rule.is_valid(m_pages)) {
        return 0;
      }
    }
    size_t middle_index {m_pages.size() / 2};
    return m_pages.at(middle_index);
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
  std::vector<std::string> rawInputRules {};
  std::vector<std::string> rawInputUpdates {};
  std::string line {};
  bool parsing_rules {true};
  while(std::getline(inputFile, line)) {
    if(line == "") {
      parsing_rules = false;
      continue;
    }
    if (parsing_rules) {
      rawInputRules.push_back(line);
    } else {
      rawInputUpdates.push_back(line);
    }
  }
  inputFile.close();

  std::vector<Rule> rules {};
  int first {};
  int second {};
  std::vector<std::string> line_inputs {};
  for (auto line: rawInputRules) {
    line_inputs = split(line, "|");
    if (line_inputs.size() != 2) {
      throw (new std::exception);
    }
    first = std::stoi(line_inputs.at(0));
    second = std::stoi(line_inputs.at(1));
    rules.push_back(Rule(first, second));
  }

  std::vector<Update> updates {};
  for (auto line: rawInputUpdates) {
    line_inputs = split(line, ",");
    std::vector<int> update_pages {};
    for (auto num: line_inputs) {
      update_pages.push_back(std::stoi(num));
    }
    Update update {rules, update_pages};
    updates.push_back(update);
  }

  int valid_middle_pages {0};
  for (auto update: updates) {
    int result = update.isValid();
    valid_middle_pages += result;
  }

  std::cout << "The answer to part 1 is: " << valid_middle_pages << std::endl;

  return 0;
}
