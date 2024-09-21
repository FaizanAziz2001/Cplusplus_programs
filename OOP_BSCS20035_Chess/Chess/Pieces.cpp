#include "Pieces.h"
#include<iostream>

using namespace std;

Pieces::Pieces(Position m_P, COLOR m_C, Board* _Board)
{
	C = m_C;
	P = m_P;
	B = _Board;
	First = true;
}

void Pieces::Print_onebox(Position S,int sri,int sci,int Box_dim)
{
	char ch= -37;
	for (int ri = sri * Box_dim; ri < sri * Box_dim + Box_dim; ri++)
	{
		for (int ci = sci * Box_dim; ci < sci * Box_dim + Box_dim; ci++)
		{
			gotoRowCol(ri, ci);
			cout << ch;
		}
		cout << endl;
	}
}

void Pieces::Move_Piece(int ri, int ci,bool draw)
{
	char c{};
	char c2{};
	if (P.ri % 2 == 0)
	{
		if (P.ci % 2 == 0)
			c = 15;
		else
			c = 8 ;
	}
	else
	{
		if (P.ci % 2 == 0)
			c = 8;
		else
			c = 15;
	}

	if (ri % 2 == 0)
	{
		if (ci % 2 == 0)
			c2 = 15;
		else
			c2 = 8;
	}
	else
	{
		if (ci % 2 == 0)
			c2 = 8;
		else
			c2 = 15;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	if(draw)
	Print_onebox(P,P.ri,P.ci,Dim);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c2);
	if(draw)
	Print_onebox(P, ri, ci, Dim);
	P.ri = ri;
	P.ci = ci;
	
	if(draw)
		Draw_piece(P.ri, P.ci, c);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);



}

bool Pieces::GetKing()
{
	return false;
}

bool Pieces::IsHorizontal(Position S, Position D)
{
	return (S.ri == D.ri);
}

bool Pieces::IsVertical(Position S, Position D)
{
	return (S.ci == D.ci);
}

bool Pieces::IsDiagonal(Position S, Position D)
{
	return (abs(S.ri - D.ri) == abs(S.ci - D.ci));
}

bool Pieces::IsHorizontalPathClear(Position S, Position D)
{
	int si, ei;
	if (D.ci < S.ci)
	{
		si = D.ci + 1;
		ei = S.ci;
	}
	else
	{
		ei = D.ci;
		si = S.ci + 1;
	}

	for (int ci = si; ci < ei; ci++)
	{
		if (B->Get({ S.ri,ci }) != nullptr)
			return false;
	}

	return true;
}

bool Pieces::IsVerticalPathClear(Position S, Position D)
{
	int si, ei;
	if (D.ri < S.ri)
	{
		si = D.ri + 1;
		ei = S.ri;
	}
	else
	{
		ei = D.ri;
		si = S.ri + 1;
	}

	for (int ri = si; ri < ei; ri++)
	{
		if (B->Get({ ri,S.ci }) != nullptr)
			return false;
	}

	return true;
}

bool Pieces::IsDiagonalPathClear(Position S, Position D)
{
	int sri, sci, ei;
	bool flag = false;
	if (D.ri < S.ri && D.ci < S.ci)
	{
		sri = D.ri + 1;
		sci = D.ci + 1;
		ei = S.ri;

		flag = true;
	}
	else if (S.ri < D.ri && S.ci < D.ci)
	{
		ei = D.ri;
		sri = S.ri + 1;
		sci = S.ci + 1;

		flag = true;
	}

	if (flag)
	{
		for (int ri = sri, ci = sci; ri < ei; ri++, ci++)
		{
			if (B->Get({ ri,ci }) != nullptr)
				return false;
		}
		return true;
	}


	if (D.ri<S.ri && D.ci>S.ci)
	{

		sri = D.ri + 1;
		sci = D.ci - 1;
		ei = S.ri;
		flag = true;
	}
	else if (D.ri > S.ri && D.ci < S.ci)
	{
		sri = S.ri + 1;
		sci = S.ci - 1;
		ei = D.ri;
		flag = true;
	}

	if (flag)
	{
		for (int ri = sri, ci = sci; ri < ei; ri++, ci--)
		{
			if (B->Get({ ri,ci }) != nullptr)
				return false;
		}
		return true;
	}

	return false;
}

bool Pieces::IsKing(Position S, Position P)
{
	return ((abs(S.ri - P.ri) == 1 && abs(S.ci - P.ci) == 1) || (abs(S.ri - P.ri) == 1 && abs(S.ci - P.ci) == 0) ||  (abs(S.ri - P.ri) == 0 && abs(S.ci - P.ci) == 1));
}

bool Pieces::IsLshape(Position S, Position P)
{
	if (abs(S.ri - P.ri) == 2 && abs(S.ci - P.ci) == 1 )
		return true;
	else if (abs(S.ri - P.ri) == 1 && abs(S.ci - P.ci) == 2 )
		return true;
	return false;
}

bool Pieces::IsLegal(Position S, Position P)
{
	return true;
}

void Pieces::Draw_piece(int ri, int ci, char c)
{

}

COLOR Pieces::Getcolour()
{
	return C;
}

bool& Pieces::GetFirst()
{
	return First;
}

Pieces::~Pieces()
{

}
