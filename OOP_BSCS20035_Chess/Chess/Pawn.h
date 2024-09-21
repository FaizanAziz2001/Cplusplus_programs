#pragma once
#include "Pieces.h"
class Pawn :
    public Pieces
{

public:
    Pawn(Position P,COLOR C,Board *B);
    bool Firstspace_check(Position S, Position P);
    bool Secondspace_check(Position S, Position P,bool);
    bool Firstmove(Position, Position);
    bool IsLegal(Position, Position);
    bool Diagonalcheck(Position, Position);
    void Draw_piece(int ri, int ci, char c);
    void Move_Piece(int ri, int ci);
    bool& GetFirst();
    ~Pawn();
};

