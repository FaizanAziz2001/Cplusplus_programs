#include "Knight.h"

Knight::Knight(Position P, COLOR C, Board* B) : Pieces(P, C, B)
{
	
}

bool Knight::IsLegal(Position S, Position D)
{
	return (IsLshape(S, D));
}

void Knight::Draw_piece(int ri, int ci, char c)
{
	char ch = -37;
	char color;
	if (C ==BLACK)
		color = 4;
	else
		color = 6;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);


	for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 6; sci++)
	{
		gotoRowCol((ri * Dim) + 4, sci);
		cout << ch;
	}

	gotoRowCol((ri * Dim) + 4, ci * Dim + 2);
	cout << ch;
	gotoRowCol((ri * Dim) + 5, ci * Dim + 1);
	cout << ch;
	gotoRowCol((ri * Dim) + 5, ci * Dim + 2);
	cout << ch;

	for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 6; sci++)
	{
		gotoRowCol((ri * Dim) + 5, sci + 1);
		cout << ch;
	}

	for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 6; sci++)
	{
		gotoRowCol((ri * Dim) + 6, sci);
		cout << ch;
	}


	for (int sci = (ci * Dim) + 2; sci < (ci * Dim) + 8; sci++)
	{
		gotoRowCol((ri * Dim) + 7, sci);
		cout << ch;
	}


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	gotoRowCol(ri, ci);
}


Knight::~Knight()
{

}
