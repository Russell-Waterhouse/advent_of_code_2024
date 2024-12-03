#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


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

std::vector<std::string> remove_conditional_commands(std::vector<std::string> input) {
    // 1. Remove everything from don't() to do()
    // I know this doesn't work for anything that wraps around lines,
    // but maybe I won't hit that case.
    std::regex r {"don't\\(\\).*?do\\(\\)"};
    std::smatch m;
    std::vector<std::string> new_input {};
    size_t pos {0};
    for (size_t i {0}; i < input.size(); i++) {
        std::regex_search(input[i], m, r);
        size_t num_matches = m.size();

        while (num_matches > 0) {
            std::string v = m[0];
            if (v == "") {
                break;
            }
            std::cout << "Finding : " << v << "\n";
            pos = input[i].find(v);
            if (pos == std::string::npos) {
                throw new std::exception();
            }
            std::cout << "Found at position: " << pos << "\n";
            input[i].erase(pos, v.length());
            std::regex_search(input[i], m, r);
            size_t num_matches = m.size();
        }
        std::cout << "new input line is: " << input[i] << std::endl;
        new_input.push_back(input[i]);
    }

    // this is sloppy because I am so close


    // remove the first don't to the end of the line
    std::regex new_r {"don't\\(\\).*$"};
    // also, I put everything on one line to make this easier
    std::regex_search(new_input[0], m, new_r);
    std::string s { m[0] };
    pos = new_input[0].find(s);

    new_input[0].erase(pos, s.length());

    return new_input;
}

std::vector<std::string> extract_multiplication_commands(std::string input) {
    auto multiplication_commands = std::vector<std::string> {};
    std::regex r("mul\\(\\d+,\\d+\\)");
    std::smatch m;
    std::regex_search(input, m, r);
    size_t num_matches = m.size();
    size_t pos {0};

    while (num_matches > 0) {
        std::string v = m[0];
        if (v == "") {
            break;
        }
        multiplication_commands.push_back(v);
        pos = input.find(v);
        if (pos == std::string::npos) {
            throw new std::exception();
        }
        input.erase(0, pos + v.length());
        std::regex_search(input, m, r);
        size_t num_matches = m.size();
    }

    return multiplication_commands;
}


int calculate_multiplications(std::vector<std::string> multiplication_commands) {
    int sum {0};
    for (auto command: multiplication_commands) {
        command.erase(0, std::string("mul(").size());
        command.erase(command.size(), command.size());
        std::vector<std::string> number_strs = split(command, ",");
        int num1 {std::stoi(number_strs[0])};
        int num2 {std::stoi(number_strs[1])};
        sum = sum + (num1 * num2);
    }
    return sum;
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
    std::vector<std::string> multiplication_commands {};
    for (auto l: rawInput){
        std::vector<std::string> new_multiplication_commands = extract_multiplication_commands(l);
        multiplication_commands.insert(multiplication_commands.end(), new_multiplication_commands.begin(), new_multiplication_commands.end());
    }
    int result = calculate_multiplications(multiplication_commands);
    std::cout << "The answer to part 1 is: " << result << std::endl;
    // TODO: use regex to just delete everything from "don't().*do()
    // Then call the same thing that I did in part 1
    std::vector<std::string> part_2_input = remove_conditional_commands(rawInput);
    multiplication_commands = {};
    for (auto l: part_2_input){
        std::cout << "Processing new line: " << l << std::endl;
        std::vector<std::string> new_multiplication_commands = extract_multiplication_commands(l);
        multiplication_commands.insert(multiplication_commands.end(), new_multiplication_commands.begin(), new_multiplication_commands.end());
    }
    result = calculate_multiplications(multiplication_commands);
    std::cout << "The answer to part 2 is: " << result << std::endl;

    return 0;
}
