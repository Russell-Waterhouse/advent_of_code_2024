#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

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
        if(line == "") {
            continue;
        }
        rawInput.push_back(line);
        // std::cout << "Pushed back: " << line << std::endl;
    }
    inputFile.close();

    vector<string> firstColumn {};
    vector<string> secondColumn {};
    for (auto &line : rawInput) {
        // cout << line << endl;
        string first = line.substr(0, line.find(" "));
        string second = line.substr(line.find(" ") + 1);
        firstColumn.push_back(first);
        secondColumn.push_back(second);
    }

    vector<int> firstColumnInt {};
    vector<int> secondColumnInt {};
    for (auto &line : firstColumn) {
        firstColumnInt.push_back(stoi(line));
    }
    for (auto &line : secondColumn) {
        secondColumnInt.push_back(stoi(line));
    }

    int sum {};

    sort(firstColumnInt.begin(), firstColumnInt.end());
    sort(secondColumnInt.begin(), secondColumnInt.end());
    for (long unsigned int i = 0; i < firstColumnInt.size(); i++) {
        sum += abs(firstColumnInt[i] - secondColumnInt[i]);
        cout << "Added " << abs(firstColumnInt[i] - secondColumnInt[i]) << "From subtracting " << firstColumnInt[i] << " and " << secondColumnInt[i] << endl;
    }

    cout << "Sum: " << sum << endl;

    int similarityScore = 0;
    for (long unsigned int i = 0; i < firstColumn.size(); i++) {
      int num_encounters { 0 };
      for (long unsigned int j = 0; j < secondColumn.size(); j++) {
        if (firstColumnInt[i] == secondColumnInt[j]) {
          num_encounters++;
        }
        if (firstColumn[i] < secondColumn[j]) {
          break;
        }
      }
      similarityScore += num_encounters * (firstColumnInt[i]);
    }

    cout << "Similarity Score: " << similarityScore << endl;


    return 0;
}
