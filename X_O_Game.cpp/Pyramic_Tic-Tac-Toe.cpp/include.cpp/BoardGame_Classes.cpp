#ifndef _BoardGame_CLASSES_H
#define _BoardGame_CLASSES_H
using namespace std;

class Board {
protected:
   int n_rows, n_cols;
   char** board;
   int  n_moves = 0;

public:
   
   virtual bool update_board (int x, int y, char symbol) = 0;
   
   virtual bool is_winner() = 0;
   // Return true if all moves are done and no winner
   virtual bool is_draw() = 0;
   // Display the board and the pieces on it
   virtual void display_board() = 0;
   // Return true if game is over
   virtual bool game_is_over() = 0;
};

///////////////////////////////////////////

class X_O_Board:public Board {
public:
   X_O_Board ();
   bool update_board (int x, int y, char mark);
   void display_board();
   bool is_winner();
   bool is_draw();
   bool game_is_over();
};

///////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Player {
    protected:
        string name;
        char symbol;
    public:
        
        Player (char symbol); 
        Player (int order, char symbol);
        
        // Virtual (can change for other player types)
        virtual void get_move(int& x, int& y);
        // Give player info as a string
        string to_string();
        // Get symbol used by player
        char get_symbol();
};

///////////////////////////////////////////

class RandomPlayer: public Player {
    protected:
        int dimension;
    public:
        // Take a symbol and pass it to parent
        RandomPlayer (char symbol, int dimension);
        // Generate a random move
        void get_move(int& x, int& y);
};

///////////////////////////////////////////
class GameManager {
    private:
        Board* boardPtr;
        Player* players[2];
    public:
        GameManager(Board*, Player* playerPtr[2]);
        void run();
        

};

#endif
