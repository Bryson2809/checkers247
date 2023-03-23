#include <iostream>
#include "Piece.h"

using namespace std;

class PieceArray {
    friend ostream& operator<<(ostream&, PieceArray&);

public:

    PieceArray(); //Default
    ~PieceArray(); //Destructor

    void print() const;

    //BUT I WANT TO USE []!!
    Piece& operator[](int);
    Piece& operator=(Piece&);

    Piece* getData() const;
    int getSize() const;

private:

    Piece *data;
    int size;
    void setData(Piece*);
    void setSize(int);

};
