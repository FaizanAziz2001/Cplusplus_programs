#include "King.h"

King::King(Position P, COLOR C, Board* B) : Pieces(P, C, B)
{
	
}

bool King::IsLegal(Position S, Position D)
{
    return (IsKing(S, D));
}

void King::Draw_piece(int ri, int ci, char c)
{
    char ch = -37;
    char color;
    if (C==BLACK)
        color = 4;
    else
        color = 6;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);


    for (int sci = (ci * Dim) + 4; sci < (ci * Dim) + 7; sci ++)
    {
        gotoRowCol((ri * Dim) + 2, sci);
        cout << ch;
    }

    for (int sci = (ci * Dim) + 2; sci < (ci * Dim) + 9; sci ++)
    {
        gotoRowCol((ri * Dim) + 3, sci);
        cout << ch;
    }

    for (int sri = (ri * Dim) + 4; sri < (ri * Dim) + 6; sri++)
    {
        gotoRowCol(sri, ci*Dim+5);
        cout << ch;
    }
   

    for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 8; sci++)
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

void King::Move_Piece(int ri, int ci)
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(P.ri, P.ci));
	Print_onebox(P, P.ri, P.ci, Dim);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
	Print_onebox(P, ri, ci, Dim);
	P.ri = ri;
	P.ci = ci;
	Draw_piece(P.ri, P.ci, Get_Box_colour(P.ri, P.ci));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	First = false;
}

King::~King()
{

}

bool King::GetKing()
{
    return true;
}

bool& King::GetFirst()
{
	return First;
}
