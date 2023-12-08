// File name: A3_SheetPb06_20221194.cpp
// Purpose: program that implements the Game of Life cellular automaton
// Author(s): Yasmin Yassen Moustafa Bayoumi       
// ID(s): 20221194
// Section: S2
// Date: 6/12/2023

#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;
class Universe{
    protected:
      static const int row = 30;
      static const int col = 30;
      int arr1[row][col];

    public:

    void initialize(){
        for(int i=0 ; i < row ; i++){
            for (int j=0 ; j < col ; j++){
                arr1[i][j] = rand() % 2;
            }
        }
    }
     void initializeFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cout << "your file not opened " << endl;
            exit(1);
        }
       else {
           for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    char c;
                    inputFile >> c;
                    arr1[i][j] = c - '0';
                }
            }
            inputFile.close();
        }
    }
    void reset(){
        for(int i=0 ; i < row ; i++){
            for (int j=0 ; j < col ; j++){
                arr1[i][j] = 0;
            }
        }
        cout << "-----------------------"<<endl;
    }
    int count_neighbors(int x ,int y){
        int counter =0;
         for(int i = x-1 ; i <= x+1 ; i++){
            for(int j = y-1 ; j <= y+1 ; j++){
                 if( (i<0 || j<0) || (i >= row || j >= col) || (i==x && j==y)) continue;
                 if (arr1[i][j]==1) counter ++;
            }
         }
         return counter ;
    }
    void next_generation(){
        int arr2[row][col];
        for(int i=0 ; i < row ; i++){
            for (int j=0 ; j < col ; j++){
                int neighbors = count_neighbors(i , j);
                if(arr1[i][j]==1 && (neighbors < 2 || neighbors > 3)) {
                    arr2[i][j]=0;
                }
                else if (arr1[i][j]==1 && (neighbors == 2 || neighbors == 3)){
                    arr2[i][j]=1;
                }
                else if (arr1[i][j]==0 && neighbors == 3){
                    arr2[i][j]=1;
                }
                else {
                    arr2[i][j]=0;
                }
            }
        }
        for(int i=0 ; i < row ; i++){
            for (int j=0 ; j < col ; j++){
               arr1[i][j]=arr2[i][j];
            }
        }
    }
    void display (){
        system("cls");
        for(int i=0 ; i < row ; i++){
            for (int j=0 ; j < col ; j++){
                // 1 for live cell
                // 0 for dead cell
                cout<< (arr1[i][j]? '1' : '0');
            }
            cout << endl;
        }
        cout << endl;
    }
    void run (int Num_Of_Runs){
          for(int i = 0; i < Num_Of_Runs ;++i){
            display();
            next_generation();
            this_thread::sleep_for(chrono::milliseconds(500));
          }
    }
};

const int Universe::row;
const int Universe::col;

void initializByUserChoice (Universe& universe) {
    cout << "Choose your option:" << endl;
    cout << "Choose 1 if you want to Initialize with random generation" << endl;
    cout << "Choose 2 if you want to Initialize from your file" << endl;

    int yourChoice;
    cin >> yourChoice;

    if (yourChoice == 1) {
        universe.initialize();
    } else if (yourChoice == 2) {
        string Name_of_Your_file;
        cout << "Plz Enter Name_of_Your_file: ";
        cin >> Name_of_Your_file;
        universe.initializeFromFile(Name_of_Your_file);
    } else {
        cout << "Invalid choice." << endl;

    }

}



int main()
{
    Universe unverse;
    initializByUserChoice(unverse);
    unverse.run(5);
    unverse.reset();
    initializByUserChoice(unverse);
    unverse.run(3);

    return 0;
}
