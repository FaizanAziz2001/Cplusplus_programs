#include "Pawn.h"
#include<iostream>
#include"Pieces.h"

Pawn::Pawn(Position P, COLOR C,Board *B): Pieces(P,C,B)
{

}

bool Pawn::Firstspace_check(Position S,Position P)
{
	return (IsVertical(S, P) && B->Get({ P.ri,P.ci }) == nullptr && (abs(S.ri - P.ri) == 1));
}

bool Pawn::Secondspace_check(Position S, Position P,bool First)
{
	return (IsVertical(S, P) && B->Get({ P.ri,P.ci }) == nullptr && First == true && (abs(S.ri - P.ri) == 2) && IsVerticalPathClear(S,P));
}

bool Pawn::Firstmove(Position S, Position P)
{ 
	if (B->GetTurn() == WHITE)
	{
		if (S.ri > P.ri)
		{
			if (Firstspace_check(S, P) || Secondspace_check(S, P, First))
			{
				return true;
			}
			
		}
	}
	else if (B->GetTurn() == BLACK)
	{
		if (S.ri < P.ri)
		{
			if (Firstspace_check(S, P) || Secondspace_check(S, P, First))
			{
		
				return true;
			}
		}
	}
	return false;
}

bool Pawn::Diagonalcheck(Position S, Position P)
{
	if (C == BLACK)
	{
		if (P.ri - S.ri == 1 && (P.ci - S.ci == -1 || P.ci - S.ci == 1) && B->Get({ P.ri,P.ci }) != nullptr)
		{
			return true;
		}
	}
	else
	{
		if (P.ri - S.ri == -1 && (P.ci - S.ci == -1 || P.ci - S.ci == 1) && B->Get({ P.ri,P.ci }) != nullptr)
		{
			return true;
		}
	}
	return false;
		
}

bool Pawn::IsLegal(Position S, Position D)
{

	if (Firstmove(S, D))
	{
		return true;
	}
	else if(Diagonalcheck(S, D))
		return true;
	return false;
}

void Pawn::Draw_piece(int ri, int ci, char c)
{
	char ch = -37;
	char color;
	if (C==BLACK)
		color = 4;
	else
		color = 6;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	for (int sri = (ri * Dim) + 3; sri < (ri * Dim) + 5; sri++)
	{

		for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 7; sci++)
		{
			gotoRowCol(sri, sci);
			cout << ch;
		}
		
	}

	for (int sri = (ri * Dim) + 5; sri < (ri * Dim) + 7; sri++)
	{

		for (int sci = (ci * Dim) + 4; sci < (ci * Dim) + 6; sci++)
		{
			gotoRowCol(sri, sci);
			cout << ch;
		}

	}

	for (int sci = (ci * Dim) + 2; sci < (ci * Dim) + 8; sci++)
	{
		gotoRowCol(ri*Dim+7, sci);
		cout << ch;
	}

	for (int sri = (ri * Dim) + 7; sri < (ri * Dim) + 5; sri++)
	{

		for (int sci = (ci * Dim) + 3; sci < (ci * Dim) + 7; sci++)
		{
			gotoRowCol(sri, sci);
			cout << ch;
		}

	}
	

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	gotoRowCol(ri, ci);


}

void Pawn::Move_Piece(int ri, int ci)
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(P.ri, P.ci));
	Print_onebox(P, P.ri, P.ci, Dim);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
	Print_onebox(P, ri, ci, Dim);
	P.ri = ri;
	P.ci = ci;
	Draw_piece(P.ri, P.ci, Get_Box_colour(P.ri, P.ci));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (ri == 6 || ri == 1)
		First = true;
	else
		First =false;



}

bool& Pawn::GetFirst()
{
	return First;
}

Pawn::~Pawn()
{

}
