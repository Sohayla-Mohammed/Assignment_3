// File: A3_SheetPb01_20220159.cpp
// purpose: The purpose of this problem is to design a flexible label generator system, implemented through an abstract class LabelGenerator,
// allowing clients to create and use arbitrary sequences of labels with a prefix and an integer sequence number. Additionally,
// the problem extends the functionality by introducing a derived class FileLabelGenerator that reads labels from a file and incorporates them into the generated labels.
// Author: Sohayla Mohammed Ahmed
// Section: S(2)
// ID: 20220159
// Date: 2_Dec_2023

#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class LabelGenerator {

private:
    string prefix;
    int InitialIndex;

public:
    LabelGenerator(const string& prefix, int initialIndex)
        : prefix(prefix), InitialIndex(initialIndex) {}

    virtual string nextLabel() {
        return prefix + to_string(InitialIndex++);
    }
};

class FileLabelGenerator : public LabelGenerator {

private:
    string fileName;
    vector<string> fileLabels;
    int fileLabelsIndex = 0;

    void readLabelsFromFile() {
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                fileLabels.push_back(line);
            }
            file.close();
        }
    }

public:
    FileLabelGenerator(const string& prefix, int initialIndex, const string& fileName)
        : LabelGenerator(prefix, initialIndex), fileName(fileName) {
            readLabelsFromFile();
        }

    string nextLabel() override {
        string label = LabelGenerator::nextLabel();
        if (fileLabelsIndex < fileLabels.size()) {
            label += " " + fileLabels[fileLabelsIndex++];
        }
        return label;
    }


};

int main() {
    LabelGenerator figureNumbers("Figure ", 1);
    LabelGenerator pointNumbers("P", 0);

    cout << "Figure numbers: ";
    for (int i = 0; i < 3; i++) {
        cout << figureNumbers.nextLabel() << ", ";
    }

    cout <<endl << "Point numbers: ";
    for (int i = 0; i < 5; i++) {
        cout << pointNumbers.nextLabel() << ", ";
    }

    cout <<endl << "More figures: ";
   for (int i = 0; i < 3; i++) {
       cout << figureNumbers.nextLabel() << ", ";
    }
    cout << endl;


    FileLabelGenerator figureLabels("Figure ", 1, "labels.txt");
    cout << "Figure labels: \n";
    for (int i = 0; i < 3; i++) {
        cout << figureLabels.nextLabel() << endl;
    }

    return 0;
}
