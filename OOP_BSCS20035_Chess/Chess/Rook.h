#pragma once
#include "Pieces.h"

class Rook :
    public Pieces
{
public:
    Rook(Position P, COLOR C, Board* B);
    bool IsLegal(Position, Position);
    void Draw_piece(int ri, int ci, char c);
    void Move_Piece(int ri, int ci);
    bool& GetFirst();
    ~Rook();
};

