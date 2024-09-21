#pragma once
#include "Pieces.h"
class Bishop :
    public Pieces
{
public:
    Bishop(Position P, COLOR C, Board* B);
    bool IsLegal(Position, Position);
    void Draw_piece(int ri, int ci, char c);
    ~Bishop();
};

