#include <cstdlib>
#include <iostream>
#include "Piece.h"

using namespace std;

class BlackPiece : public Piece {
public:
        BlackPiece() : Piece() {
                setIsRed(false);
        }

        BlackPiece(int id, int x, int y) : Piece(id, x, y) {
                setIsRed(false);
        }
};
