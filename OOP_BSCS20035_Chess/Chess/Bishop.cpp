#include "Bishop.h"

Bishop::Bishop(Position P, COLOR C, Board* B) : Pieces(P, C, B)
{

}

bool Bishop::IsLegal(Position S, Position P)
{
	return (IsDiagonal(S, P) && IsDiagonalPathClear(S, P));

}

void Bishop::Draw_piece(int ri, int ci, char c)
{
	char ch = -37;
	char color;
	if (C==BLACK)
		color = 4;
	else
		color = 6;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);


	gotoRowCol((ri * Dim) + 3, ci * Dim + 5);
	cout << ch;


	for (int sci = (ci * Dim) + 4; sci < (ci * Dim) + 7; sci++)
	{
		gotoRowCol((ri * Dim) + 4, sci);
		cout << ch;
	}

	for (int sri = (ri * Dim) + 5; sri < (ri * Dim) + 6; sri++)
	{
		gotoRowCol(sri, ci * Dim + 5);
		cout << ch;
	}

	for (int sci = (ci * Dim) + 4; sci < (ci * Dim) + 7; sci++)
	{
		gotoRowCol((ri * Dim) + 6, sci);
		cout << ch;
	}

	for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 8; sci++)
	{
		gotoRowCol((ri * 10) + 7, sci);
		cout << ch;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	gotoRowCol(ri, ci);
}

Bishop::~Bishop()
{

}
