#include <cstdlib>
#include <iostream>
#include "Piece.h"

using namespace std;

class RedPiece : public Piece {
    public:
        RedPiece() : Piece() {
            setIsRed(true);
        }

        RedPiece(int id, int x, int y) : Piece(id, x, y) {
            setIsRed(true);
        }
};