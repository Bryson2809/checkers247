#include <cstdlib>
#include <iostream>
#include "Piece.h"

using namespace std;

    Piece::Piece() {
        id = -1;
        x_pos = 0;
        y_pos = 0;
        is_taken = false;
        is_king = false;
    }

    Piece::Piece(int id, int x, int y) {
        this->id = id;
        x_pos = x;
        y_pos = y;
        is_taken = false;
        is_king = false;
    }

    bool Piece::matches(Piece piece) {
        return this->getIsRed() == piece.getIsRed(); 
    }

    int Piece::getXPos() {
        return x_pos;
    }

    int Piece::getYPos() {
        return y_pos;
    }

    void Piece::setPos(int x, int y) {
        x_pos = x;
        y_pos = y;
    }

    bool Piece::getIsRed() {
        return is_red;
    }

    void Piece::setIsRed(bool b) {
        is_red = b;
    }

    int Piece::getID() {
        return id;
    }

    bool Piece::getIsTaken() {
        return is_taken;
    }

    void Piece::setIsTaken() {
        is_taken = true;
        x_pos = -1;
        y_pos = -1;
    }

    bool Piece::getIsKing() {
        return is_king;
    }

    void Piece::king() {
        is_king = true;
    }

    bool Piece::getNoMove() {
        return no_move;
    }

    void Piece::setNoMove(bool b) {
        no_move = b;
    }

    char Piece::toString() {
        if(is_red) {
            return 'R';
        } else {
            return 'B';
        }
    }