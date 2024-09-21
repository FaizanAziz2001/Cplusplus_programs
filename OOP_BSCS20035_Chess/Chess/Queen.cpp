#include "Queen.h"

Queen::Queen(Position P, COLOR C, Board* B) : Pieces(P, C, B)
{
	
}

bool Queen::IsLegal(Position P, Position D)
{
	if (IsHorizontal(P, D) && IsHorizontalPathClear(P, D))
		return true;
	else if (IsVertical(P, D) && IsVerticalPathClear(P, D))
		return true;
	else if (IsDiagonal(P, D) && IsDiagonalPathClear(P, D))
		return true;
	return false;
}

void Queen::Draw_piece(int ri, int ci, char c)
{
   
    char ch = -37;
    char color;
    if (C ==BLACK)
        color = 4;
    else
        color = 6;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);


    for (int sci = (ci * Dim) + 2; sci < (ci * Dim) + 9; sci=sci+2)
    {
        gotoRowCol((ri * Dim) + 3, sci);
        cout << ch;
    }

    for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 8; sci = sci + 2)
    {
        gotoRowCol((ri * Dim) + 4, sci);
        cout << ch;
    }

    for (int sci = (ci * Dim) + 4; sci < (ci * Dim) + 7; sci = sci + 2)
    {
        gotoRowCol((ri * Dim) + 5, sci);
        cout << ch;
    }

    for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 8; sci ++)
    {
        gotoRowCol((ri * Dim) + 6, sci);
        cout << ch;
    }

    for (int sci = (ci * Dim) + 2; sci < (ci * Dim) + 9; sci++)
    {
        gotoRowCol((ri * Dim) + 7, sci);
        cout << ch;
    }



	gotoRowCol((ri * Dim) + 6, ci * Dim + 5);
	cout << ch;



    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    gotoRowCol(ri, ci);
}

Queen::~Queen()
{

}
