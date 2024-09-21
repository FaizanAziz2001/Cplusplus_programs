#pragma once
#include "Header.h"
#include "Board.h"
#include<windows.h>
#include<iostream>
using namespace std;

class Board;
class Pieces
{

protected:
	Position P;
	COLOR C;
	Board* B;
	int Dim = 10;
	bool First;

public:
	Pieces(Position m_P,COLOR m_C,Board* _Board );
	virtual bool IsLegal(Position S,Position P);
	virtual void Draw_piece(int ri, int ci, char c);
	virtual void Move_Piece(int,int,bool draw=true);
	virtual bool GetKing();
	virtual bool& GetFirst();

	bool IsHorizontal(Position S, Position P);
	bool IsVertical(Position S, Position P);
	bool IsDiagonal(Position S, Position P);
	bool IsHorizontalPathClear( Position S, Position P);
	bool IsVerticalPathClear( Position S, Position P);
	bool IsDiagonalPathClear(Position S, Position P);
	bool IsKing(Position S, Position P);
	bool IsLshape(Position S, Position P);
	void Print_onebox(Position S, int sri,int sci, int Box_dim);
	COLOR Getcolour();
	
	
	~Pieces();

};

