#include <iostream>
#include <cstdlib>
#include "Piece.h"
#include "PieceArray.h"

using namespace std;

PieceArray::PieceArray(){
    data = new Piece[12];
    size = 0;
} //Default

PieceArray::~PieceArray()
{
    delete [] data;
} //Destructor

Piece& PieceArray::operator[](int index)
{
    return data[index];
}


Piece* PieceArray::getData() const
{
    return data;
}

int PieceArray::getSize() const
{
    return size;
}

void PieceArray::setData(Piece* _data)
{
    data = _data;
}

void PieceArray::setSize(int _size)
{
    if(_size > 0) size = _size;
    else size = 0; //raise error/warning
}
