#pragma once
#include "Pieces.h"
class Queen :
    public Pieces
{
public:
    Queen(Position P, COLOR C, Board* B);
    bool IsLegal(Position, Position);
    void Draw_piece(int ri, int ci, char c);
    ~Queen();
};

