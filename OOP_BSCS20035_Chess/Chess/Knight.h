#pragma once
#include "Pieces.h"
class Knight :
    public Pieces
{
    public:
    Knight(Position P, COLOR C, Board* B);
    bool IsLegal(Position, Position);
    void Draw_piece(int ri, int ci, char c);
    ~Knight();
};

