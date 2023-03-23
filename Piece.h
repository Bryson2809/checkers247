#include <cstdlib>
#include <iostream>

#ifndef PIECE_H
#define PIECE_H

using namespace std;

class Piece {
    public:

        Piece();
        Piece(int, int, int);

        bool matches(Piece);
        int getXPos();
        int getYPos();
        void setPos(int,int);
        bool getIsRed();
        void setIsRed(bool);
        int getID();
        bool getIsTaken();
        void setIsTaken();
        bool getIsKing();
        void king();
        bool getNoMove();
        void setNoMove(bool);
        char toString();

    private:
        int id;
        int x_pos;
        int y_pos;
        bool is_king;
        bool is_taken;
        bool is_red;
        bool no_move;
};

#endif