#include "Rook.h"
#include<windows.h>

Rook::Rook(Position P, COLOR C, Board* B) : Pieces(P, C, B)
{

}

bool Rook::IsLegal(Position S,Position P)
{
	if (IsHorizontal(S, P) && IsHorizontalPathClear(S, P))
		return true;
	else if (IsVertical(S, P) && IsVerticalPathClear(S, P))
		return true;
	return false;
}

void Rook::Draw_piece(int ri, int ci, char c)
{
   
    char ch = -37;
    char color;
    if (C ==BLACK)
        color = 4;
    else 
        color = 6;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

    gotoRowCol(ri * Dim + (Dim / 2) - 1, ci * Dim + 2);
    cout << ch;
    gotoRowCol(ri * Dim + (Dim / 2) - 1, ci * Dim + 4);
    cout << ch;
    gotoRowCol(ri * Dim + (Dim / 2) - 1, ci * Dim + 6);
    cout << ch;

   
    int sri = (ri * Dim)+5;
    for (; sri < (ri * Dim + 5) + 2; sri++)
    {
        for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 6; sci++)
        {
            gotoRowCol(sri, sci);
            cout << ch;
        }
    }

    for (int sci = ci * Dim + 2; sci <= (ci * Dim) + 6; sci++)
    {
        gotoRowCol(sri, sci);
        cout << ch;
    }


 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    gotoRowCol(ri, ci);


}

void Rook::Move_Piece(int ri, int ci)
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(P.ri,P.ci));
	Print_onebox(P, P.ri, P.ci, Dim);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
	Print_onebox(P, ri, ci, Dim);
	P.ri = ri;
	P.ci = ci;
	Draw_piece(P.ri, P.ci, Get_Box_colour(P.ri, P.ci));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


	First = false;
}

bool& Rook::GetFirst()
{
    return First;
}

Rook::~Rook()
{

}
