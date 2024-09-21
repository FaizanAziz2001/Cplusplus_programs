#pragma once
#include "Pieces.h"
class King :
    public Pieces
{
public:
    King(Position P, COLOR C, Board* B);
    bool IsLegal(Position S, Position P);
    void Draw_piece(int ri, int ci, char c);
    void Move_Piece(int ri, int ci);
    bool GetKing();
    bool& GetFirst();
    ~King();
};

