// File name: A3_SheetPb03_20221194.cpp
// Purpose:  A frequency table lists words and the number of times each word appears in a document or a file.
// Author(s):  Yasmin Yassen Moustata Bayoumi
// ID(s):  20221194
// Section: S2
// Date: 6/12/2023


#include <iostream> 
#include <bits/stdc++.h> 
#include <cctype>
#include <string>
#include <map>
#include <fstream>

using namespace std; 

string removepunct(const string& word) {
    int First_Index = 0;
    int Last_Index = word.length() - 1;
    while (First_Index < word.length() && ispunct(word[First_Index])) {
        First_Index++;
    }
    while (Last_Index > First_Index && ispunct(word[Last_Index])) {
        Last_Index--;
    }
    string result = word.substr(First_Index, Last_Index - First_Index + 1);
    return result;
}
string cleanWord(const string& word) {
    string cleanedWord;
    for (char Char : word) {
        if (isalnum(Char) || Char == '_') {
            cleanedWord += Char;
        }
    }
    return cleanedWord;
}
int main( ) 
{  
    string name_of_file;
    cout<<"plz enter your file name: ";
    cin>>name_of_file;
    ifstream inputFile(name_of_file); 
  
    if (!inputFile.is_open()) {
        cerr << "File not found" << endl;
        return 1;
    }

    map <string, int> frequency_table;

    string word;
    while (inputFile >> word) {
        string wordAfterRemovePunct = removepunct(word);
        string cleanedWord = cleanWord(wordAfterRemovePunct);
        for(char& Char : cleanedWord){
              Char = tolower(Char);
        }
        if(!cleanedWord.empty()){
            frequency_table[cleanedWord]++;
        }
    }
    cout << "Word Frequency Table:" << endl;
    for (auto it = frequency_table.begin(); it != frequency_table.end(); ++it) { 
            cout << it->first << ": " << it->second << " times" << endl;
    }

    inputFile.close();
    
 return 0;
}
