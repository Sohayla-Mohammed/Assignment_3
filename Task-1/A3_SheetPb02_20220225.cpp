// File: A3_SheetPb02_20220225.cpp
// Author: Omar Saeed Othman
// Section: S(1)
// ID: 20220225

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_set>


using namespace std;

class StringSet {
private:

     bool is_Punctuation(char c) {
        return c=='.' || c==':' || c==',' || c=='?'|| c==' ' || c=='-' || c=='!'||c==';'||c=='\n' ;
    }
    unordered_set<string>dataset;
    bool is_File(string &filename){
        fstream myFile(filename);
        if (myFile.is_open()){
            return true;
        } else{
            return false;
        }
    }
    void loadFromstring(string string1){
        string word="";
        char ch;
        for (char i : string1) {
            ch=i;
            if (is_Punctuation(ch)){
                if (!word.empty()){
                    dataset.insert(word);
                }
                word.clear();
            }
            else{
                ch= tolower(ch);
                word+=ch;
            }
        }
        if (!word.empty()){
            dataset.insert(word);
        }
    }
    void loadFromfile(string filename){
        ifstream file(filename);
        char ch;
        string word="";
        while (file.get(ch)){

            if (is_Punctuation(ch)){
                if (!word.empty()){

                    dataset.insert(word);
                }
                word.clear();
            } else{
                ch= tolower(ch);
                word+=ch;

            }
        }
        if (!word.empty()){
            dataset.insert(word);
        }
    }

public:

    StringSet(string filename_or_string ){
        if (is_File(filename_or_string))
        {
        loadFromfile(filename_or_string);
        } else
        {
            loadFromstring(filename_or_string);
        }
    }
    StringSet(){}
    void addString(string addedString){
        dataset.insert(addedString);


    }
    void removestring(string removedString){
        auto it=dataset.find(removedString);
        if (it!=dataset.end()){
            dataset.erase(removedString);

        } else{
            cerr<<"String you want to remove does not exist \n";
        }



    }
    void clear(){
        dataset.clear();
    }
    void print() const{
        if (!dataset.empty()){
            vector<string> vec(dataset.begin(), dataset.end());
            reverse(vec.begin(),vec.end());
            cout<<"{";
            for (int i = 0; i < vec.size(); ++i) {
                if (i!=vec.size()-1){
                    cout<<vec.at(i)<<", ";
                } else{
                    cout<<vec.at(i)<<"}\n";
                }
            }

        } else{
            cout<<"Set is empty.\n";
        }
    }
    int size() const{
        return dataset.size();
    }
    StringSet operator+(const StringSet& other) const {
        StringSet result = *this;
        result.dataset.insert(other.dataset.begin(), other.dataset.end());
        return result;
    }
    StringSet operator*(const StringSet& other) const {
        StringSet result;
        for (const auto& word : dataset) {
            if (other.dataset.find(word) != other.dataset.end()) {
                result.dataset.insert(word);
            }
        }
        return result;
    }
    double computeSimilarity(const StringSet& other) const {
        int commonWords = (*this * other).size();
        double similarity = static_cast<double>(commonWords) / (sqrt(size()) * sqrt(other.size()));
        return similarity;
    }
};
int main() {
  StringSet s("input.txt"); //Load Data From File
  s.print();
  StringSet s1("Chocolate ice cream, chocolate milk, and chocolate bars are delicious.");
  StringSet s2("Water ,salt ,sugar ,ice ,milk.");
  StringSet s3=s1+s2;
  StringSet s4=s1*s2;
  cout<<"Similarity = "<<s1.computeSimilarity(s2)<<"\n";
  s3.print();
  s4.print();
  s1.addString("Egg");
  s2.removestring("milk");
  s1.print();
  s2.print();
  s3.clear();
  s3.print();
  cout<<s1.size()<<" "<<s3.size();

    return 0;
}
