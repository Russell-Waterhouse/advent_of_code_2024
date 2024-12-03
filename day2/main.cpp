#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(string input, string delimiter) {
    vector<string> tokens {};
    size_t pos {0};
    int i {0};
    do {
        pos = input.find(delimiter);
        if (pos == string::npos) {
            break;
        }
        string token = input.substr(0, pos);
        cout << "Token is " << token << endl;
        tokens.push_back(token);
        input.erase(0, pos + delimiter.size());
        i++;
    } while (i < 100);
    tokens.push_back(input);
    return tokens;
}


bool isAscendingSafely(vector<int> line) {
    size_t len {line.size()};
    cout << "Size is " << len << endl;
    size_t i {0};
    int diff {0};
    for (i = 0; i < len - 1; i++) {
        cout << "Checking " << line[i] << " against " << line[i + 1] << "\n";
        diff = line[i + 1] - line[i];
        if (diff > 3 || diff < 1) {
            return false;
        }
    }
    return true;
}

bool isDescendingSafely(vector<int> line) {
    size_t len {line.size()};
    size_t i {0};
    int diff {0};
    for (i = 0; i < len - 1; i++) {
        diff = line[i] - line[i + 1];
        if (diff > 3 || diff < 1) {
            return false;
        }
    }
    return true;
}

bool isAscendingSafelyWithDampener(vector<int> line) {
    if (isAscendingSafely(line)) {
        return true;
    }

    for (size_t i = 0; i < line.size(); i++) {
        vector<int> dampened_line {line};
        int index {static_cast<int>(i)};
        dampened_line.erase(dampened_line.begin() + index);
        if (isAscendingSafely(dampened_line)) {
            return true;
        }
    }
    return false;
}

bool isDescendingSafelyWithDampener(vector<int> line) {
    if (isDescendingSafely(line)) {
        return true;
    }

    for (size_t i = 0; i < line.size(); i++) {
        vector<int> dampened_line {line};
        int index {static_cast<int>(i)};
        dampened_line.erase(dampened_line.begin() + index);
        if (isDescendingSafely(dampened_line)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
     if (argc < 2) {
        cout << "No argument given, exiting" << endl;
        return 0;
    }
    string input_file_name = {argv[1]};
    ifstream inputFile(input_file_name);
    vector<string> rawInput {};
    string line {};
    while(std::getline(inputFile, line)) {
        if (line == "") {
            continue;
        }
        rawInput.push_back(line);
        // std::cout << "Pushed back: " << line << std::endl;
    }
    inputFile.close();

    vector<vector<int>> input {};
    for (auto line: rawInput) {
        vector<string> tokens {split(line, " ")};
        vector<int> line_ints {};
        for (auto token: tokens) {
            line_ints.push_back(stoi(token));
        }
        input.push_back(line_ints);
    }

    int safe {0};
    for (auto line: input) {
        const vector<int> line_ref {line};
        if (isAscendingSafely(line_ref) || isDescendingSafely(line_ref)) {
            safe++;
        }
    }

    cout << "There are this many safe readings: " << safe << endl;

    safe = 0;
    for (auto line: input) {
        const vector<int> line_ref {line};
        if (isAscendingSafelyWithDampener(line_ref) || isDescendingSafelyWithDampener(line_ref)) {
            safe++;
        }
    }
    cout << "PART 2: There are now this many safe readings: " << safe << endl;
    return 0;
}
