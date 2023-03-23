#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Board.cpp"
#include "Piece.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    Board board = *(new Board());
    cout << "Welcome to the game!" << endl;

    cout << endl;

     while(true) {
         board.checkKings();
         board.moveRed();
         board.updateBoard();
         board.PrintGrid();
         board.checkWinner();
         if (board.isOver()) break;
         board.moveBlack();
         board.updateBoard();
         board.PrintGrid();
         board.checkWinner();
         if (board.isOver()) break;
         cout << "\nTurns: " << board.getTurns() << endl;
     }


    return 0;
}