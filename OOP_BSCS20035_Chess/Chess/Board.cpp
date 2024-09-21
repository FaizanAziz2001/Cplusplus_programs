#include "Board.h"
#include "Pawn.h"
#include"King.h"
#include"Rook.h"
#include"Bishop.h"
#include"Queen.h"
#include"Knight.h"
#include"Header.h"
#include<iostream>
#include<vector>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<windows.h>
#include<vector>
using namespace std;

Board::Board()
{
	Dim = 8;
	counter = 1;
	Load_check = false;
	Init();
}

int Get_Box_colour(int ri, int ci)
{
	int c;
	if (ri % 2 == 0)
	{
		if (ci % 2 == 0)
			c = 15;
		else
			c = 8;
	}
	else
	{
		if (ci % 2 == 0)
			c = 8;
		else
			c = 15;
	}
	return c;
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void Board::Init()
{
	Ps = new Pieces * *[Dim] {};
	for (int ri = 0; ri < Dim; ri++)
	{
		Ps[ri] = new Pieces * [Dim] {};
		for (int ci = 0; ci < Dim; ci++)
		{
			if (ri == 1)
				Ps[ri][ci] = new Pawn(Position{ ri, ci }, BLACK, this);
			else if (ri == 6)
				Ps[ri][ci] = new Pawn(Position{ ri,ci }, WHITE, this);
			else if (ri == 0)
			{
				if (ci == 0 || ci == Dim - 1)
					Ps[ri][ci] = new Rook(Position{ ri,ci }, BLACK, this);
				else if (ci == 0 || ci == Dim - 1)
					Ps[ri][ci] = new Rook(Position{ ri,ci }, BLACK, this);
				else if (ci == 1 || ci == Dim - 2)
					Ps[ri][ci] = new Knight(Position{ ri,ci }, BLACK, this);
				else if (ci == 2 || ci == Dim - 3)
					Ps[ri][ci] = new Bishop(Position{ ri,ci }, BLACK, this);
				else if (ci == 3)
					Ps[ri][ci] = new Queen(Position{ ri,ci }, BLACK, this);
				else if (ci == 4)
					Ps[ri][ci] = new King(Position{ ri,ci }, BLACK, this);
			}
			else if (ri == Dim - 1)
			{
				if (ci == 0 || ci == Dim - 1)
					Ps[ri][ci] = new Rook(Position{ ri,ci }, WHITE, this);
				else if (ci == 0 || ci == Dim - 1)
					Ps[ri][ci] = new Rook(Position{ ri,ci }, WHITE, this);
				else if (ci == 1 || ci == Dim - 2)
					Ps[ri][ci] = new Knight(Position{ ri,ci }, WHITE, this);
				else if (ci == 2 || ci == Dim - 3)
					Ps[ri][ci] = new Bishop(Position{ ri,ci }, WHITE, this);
				else if (ci == 3)
					Ps[ri][ci] = new Queen(Position{ ri,ci }, WHITE, this);
				else if (ci == 4)
					Ps[ri][ci] = new King(Position{ ri,ci }, WHITE, this);
			}

		}
	}

}

void Board::Print_Board(char ch, int sri, int sci, char c)
{
	for (int ri = sri * Box_dim; ri < sri * Box_dim + Box_dim; ri++)
	{
		for (int ci = sci * Box_dim; ci < sci * Box_dim + Box_dim; ci++)
		{
			gotoRowCol(ri, ci);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << ch;
		}
		cout << endl;
	}
}

void Board::Menu()
{
	char ch = -37;
	int ri = 1;
	int ci = (Dim + 30) * Dim;
	for (; ri < 5; ri++, ci += 5)
	{
		gotoRowCol(ri, ci);
		for (int si = ci; si < ci + 10; si++)
		{
			cout << ch;
		}
	}
	for (; ri < 10; ri++, ci -= 5)
	{
		gotoRowCol(ri, ci);
		for (int si = ci; si < ci + 10; si++)
		{
			cout << ch;
		}
	}
	gotoRowCol(ri + 1, ci);
	cout << "Replay";
	ri += 10;

	for (; ri < 25; ri++, ci -= 5)
	{
		gotoRowCol(ri, ci);
		for (int si = ci; si < ci + 10; si++)
		{
			cout << ch;
		}
	}
	for (; ri < 31; ri++, ci += 5)
	{
		gotoRowCol(ri, ci);
		for (int si = ci; si < ci + 10; si++)
		{
			cout << ch;
		}
	}
	gotoRowCol(ri + 1, ci);
	cout << "Undo";
	ri += 10;
	for (; ri < 45; ri++)
	{
		gotoRowCol(ri, ci);
		for (int si = ci; si < ci + 10; si++)
		{
			cout << ch;
		}
	}
	gotoRowCol(ri + 1, ci);
	cout << "Save Game";
	ri += 15;

	for (; ri < 70; ri++)
	{
		gotoRowCol(ri, ci);
		cout << ch;
		gotoRowCol(ri, ci + 1);
		cout << ch;
	}

	for (int si = 0; si < 10; si++, ci++)
	{
		gotoRowCol(ri, ci);
		cout << ch;
	}
	gotoRowCol(ri + 1, ci);
	cout << "Load Game";



}

void Board::Draw()
{
	char c = 15;
	char ch = -37;
	bool flag = true;

	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{

			c = (flag) ? 15 : 8;
			flag = !flag;
			Print_Board(ch, ri, ci, c);
			if (Ps[ri][ci] != nullptr)
			{
				Ps[ri][ci]->Draw_piece(ri, ci, c);
			}
		}
		flag = !flag;
	}

	for (int ci = Box_dim / 2, a = 65; ci < Dim * Box_dim; ci = ci + Box_dim)
	{
		gotoRowCol(Dim * Box_dim + 2, ci);
		cout << char(a++) << "\t\t";
	}
	for (int ri = Box_dim / 2, i = Dim; ri < Dim * Box_dim; ri = ri + Box_dim)
	{
		gotoRowCol(ri, Dim * Box_dim + 2);
		cout << i-- << "\t\t";
	}

}

void Board::Play()
{

	Draw();
	Menu();
	Move();

}

void Board::Move()
{

	bool flag = false;
	int ri, ci, m_ri, m_ci;
	Position P;
	do
	{
		gotoRowCol(0, (Dim + 3) * Dim);
		if (turn == 1)
			cout << "White Turn";
		else if (turn == 0)
			cout << "Black Turn";

		do
		{
			Select_Cordinates(ri, ci, m_ri, m_ci, flag);
			Location.IB.push_back(Ps[ri][ci]);

			if (Castlecheck({ ri,ci }, { m_ri,m_ci }))
			{
				if (ci < m_ci)
					ShortCastling({ ri,ci }, { m_ri,m_ci });
				else
					LongCastling({ ri,ci }, { m_ri,m_ci });
				break;
			}
			else if (Ps[ri][ci]->IsLegal({ ri,ci }, { m_ri,m_ci }) && !Selfcheck({ ri,ci }, { m_ri, m_ci }))
			{
				Location.PA.push_back({ ri,ci });
				Location.FB.push_back(Ps[m_ri][m_ci]);

				if (Promotion({ ri,ci }, { m_ri,m_ci }))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
					Ps[ri][ci]->Print_onebox({ ri,ci }, ri, ci, Box_dim);
					Ps[ri][ci] = nullptr;
					gotoRowCol(counter, (Dim + 15) * Dim);
					cout << (turn == WHITE ? "White" : "Black");
					gotoRowCol(counter++, (Dim + 20) * Dim);
					cout << char('A' + m_ci) << (Dim - m_ri);
					Location.CA.push_back({ m_ri,m_ci });
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					break;
				}
				Ps[ri][ci]->Move_Piece(m_ri, m_ci);
				Ps[m_ri][m_ci] = Ps[ri][ci];
				Ps[ri][ci] = nullptr;
				if (!My_King_check())
				{
					gotoRowCol(counter, (Dim + 15) * Dim);
					cout << (turn == WHITE ? "White" : "Black");
					gotoRowCol(counter++, (Dim + 20) * Dim);
					cout << char('A' + m_ci) << (Dim - m_ri);
					Location.CA.push_back({ m_ri,m_ci });
					break;
				}
				else
				{
					Location.CA.push_back({ m_ri,m_ci });
					Undo();

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
			}

			else
			{
				gotoRowCol(1, (Dim + 3) * Dim);
				cout << "                                                       ";
				gotoRowCol(1, (Dim + 3) * Dim);
				cout << "Invalid Move";

			}
		} while (true);

		if (Repitition())
		{
			gotoRowCol(0, (Dim + 3) * Dim);
			cout << "                                       ";
			gotoRowCol(0, (Dim + 4) * Dim);
			cout << "                                       ";
			gotoRowCol(0, (Dim + 3) * Dim);
			cout << "Draw by repitition";
			return;
		}
		Position P = King_cordinates();
		if (check(P))
		{
			flag = true;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			Highlight_box({ P.ri,P.ci }, Box_dim);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (checkmate(P))
			{
				gotoRowCol(0, (Dim + 3) * Dim);
				cout << "                                       ";
				gotoRowCol(0, (Dim + 4) * Dim);
				cout << "                                       ";
				gotoRowCol(0, (Dim + 3) * Dim);
				cout << (turn == 1 ? "WHITE" : "BLACK") << " WINS BY CHECKMATE" << endl;
				gotoRowCol(1, (Dim + 3) * Dim);
				cout << "Total moves: " << (counter - 1);
				Replaycheckmate();
				return;
			}

		}

		ChangeTurn();
		if (Stalemate())
		{
			gotoRowCol(0, (Dim + 3) * Dim);
			cout << "                                       ";
			gotoRowCol(0, (Dim + 4) * Dim);
			cout << "                                       ";
			gotoRowCol(0, (Dim + 3) * Dim);
			cout << (turn == 1 ? "WHITE" : "BLACK") << " DRAWS BY STALEMATE" << endl;
			Replaycheckmate();
			return;
		}
		else if (My_King_check())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			Highlight_box(P, Box_dim);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	} while (true);
}

void Board::LoadBoard()
{

	system("cls");
	ifstream fin("Board.txt");
	string ch;
	Ps = new Pieces * *[Dim] {};
	for (int ri = 0; ri < Dim; ri++)
	{
		Ps[ri] = new Pieces * [Dim] {};
		for (int ci = 0; ci < Dim; ci++)
		{

			fin >> ch;

			if (ch[0] != '-')
			{
				if (ch[0] == 'R')
				{
					Ps[ri][ci] = new Rook(Position{ ri, ci }, BLACK, this);
					Ps[ri][ci]->GetFirst() = (ch[1] == '1' ? true : false);
				}
				else if (ch[0] == 'r')
				{
					Ps[ri][ci] = new Rook(Position{ ri,ci }, WHITE, this);
					Ps[ri][ci]->GetFirst() = (ch[1] == '1' ? true : false);
				}

				if (ch[0] == 'H')
					Ps[ri][ci] = new Knight(Position{ ri,ci }, BLACK, this);
				else if (ch[0] == 'h')
					Ps[ri][ci] = new Knight(Position{ ri,ci }, WHITE, this);

				if (ch[0] == 'B')
					Ps[ri][ci] = new Bishop(Position{ ri,ci }, BLACK, this);
				else if (ch[0] == 'b')
					Ps[ri][ci] = new Bishop(Position{ ri,ci }, WHITE, this);

				if (ch[0] == 'Q')
					Ps[ri][ci] = new Queen(Position{ ri,ci }, BLACK, this);
				else if (ch[0] == 'q')
					Ps[ri][ci] = new Queen(Position{ ri,ci }, WHITE, this);

				if (ch[0] == 'K')
				{
					Ps[ri][ci] = new King(Position{ ri,ci }, BLACK, this);
					Ps[ri][ci]->GetFirst() = (ch[1] == '1' ? true : false);
				}

				else if (ch[0] == 'k')
				{
					Ps[ri][ci] = new King(Position{ ri,ci }, WHITE, this);
					Ps[ri][ci]->GetFirst() = (ch[1] == '1' ? true : false);
				}

				if (ch[0] == 'P')
				{
					Ps[ri][ci] = new Pawn(Position{ ri, ci }, BLACK, this);
					Ps[ri][ci]->GetFirst() = (ch[1] == '1' ? true : false);
				}
				else if (ch[0] == 'p')
				{
					Ps[ri][ci] = new Pawn(Position{ ri, ci }, WHITE, this);
					Ps[ri][ci]->GetFirst() = (ch[1] == '1' ? true : false);
				}

			}
			else if (ch[0] == '-')
			{
				Ps[ri][ci] = nullptr;
			}
		}
	}
	fin >> ch;
	turn = (ch[0] == '0' ? BLACK : WHITE);
	gotoRowCol(0, (Dim + 3) * Dim);
	if (turn == 1)
		cout << "White Turn";
	else if (turn == 0)
		cout << "Black Turn";

	Menu();
	counter = 1;
	Load_check = true;


}

void Board::NewGame()
{
	system("cls");
	char choice;
	cout << "N for new game or L for load" << endl;
	cin >> choice;

	if (choice == 'N' || choice == 'n')
	{
		system("cls");
		Init();
		Draw();
		Menu();
		turn = WHITE;
	}
	else
	{
		LoadBoard();
	}

}

void Board::SaveBoard()
{
	ofstream fout("Board.txt");
	King* K; Queen* Q; Pawn* P; Knight* H; Bishop* B; Rook* R;

	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{

			K = dynamic_cast<King*>(Ps[ri][ci]);
			Q = dynamic_cast<Queen*>(Ps[ri][ci]);
			P = dynamic_cast<Pawn*>(Ps[ri][ci]);
			H = dynamic_cast<Knight*>(Ps[ri][ci]);
			B = dynamic_cast<Bishop*>(Ps[ri][ci]);
			R = dynamic_cast<Rook*>(Ps[ri][ci]);

			if (Ps[ri][ci] != nullptr)
			{
				if (K != nullptr)
				{
					fout << (Ps[ri][ci]->Getcolour() == BLACK ? 'K' : 'k');
					fout << Ps[ri][ci]->GetFirst();
				}
				if (Q != nullptr)
				{
					fout << (Ps[ri][ci]->Getcolour() == BLACK ? 'Q' : 'q');
					fout << Ps[ri][ci]->GetFirst();
				}
				if (P != nullptr)
				{

					fout << (Ps[ri][ci]->Getcolour() == BLACK ? 'P' : 'p');
					fout << Ps[ri][ci]->GetFirst();
				}
				if (H != nullptr)
				{

					fout << (Ps[ri][ci]->Getcolour() == BLACK ? 'H' : 'h');
					fout << Ps[ri][ci]->GetFirst();
				}
				if (B != nullptr)
				{

					fout << (Ps[ri][ci]->Getcolour() == BLACK ? 'B' : 'b');
					fout << Ps[ri][ci]->GetFirst();
				}
				if (R != nullptr)
				{
					fout << (Ps[ri][ci]->Getcolour() == BLACK ? 'R' : 'r');
					fout << Ps[ri][ci]->GetFirst();
				}
			}
			else
			{
				fout << "-" << "-";
			}
			fout << " ";
		}
		fout << endl;
	}

	fout << (turn == BLACK ? 0 : 1);

}

void Board::Replay()
{
	system("cls");
	Draw();
	int ri, ci, mri, mci;

	for (int si = 0, pi = 0; si < Location.PA.size() && si < Location.CA.size(); si++)
	{

		gotoRowCol(Dim * 10, (Dim + 20) * Dim);
		system("pause");
		ri = Location.PA[si].ri;
		ci = Location.PA[si].ci;
		mri = Location.CA[si].ri;
		mci = Location.CA[si].ci;
		Pawn* P = dynamic_cast<Pawn*>(Ps[ri][ci]);

		if (P != nullptr && (ri == 1 && mri == 0) && Ps[ri][ci]->Getcolour() == turn)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(mri, mci));
			Ps[mri][mci]->Print_onebox({ mri,mci }, mri, mci, Box_dim);
			if (!Promotioncheck(Location.Promotion[pi], { mri,mci }, turn))
				break;
			Ps[mri][mci]->Draw_piece(mri, mci, 15);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
			Ps[ri][ci]->Print_onebox({ ri,ci }, ri, ci, Box_dim);
			Ps[ri][ci] = nullptr;
			pi++;
		}
		else if (P != nullptr && (ri == Dim - 2 && mri == Dim - 1) && Ps[ri][ci]->Getcolour() == turn)
		{

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(mri, mci));
			Ps[mri][mci]->Print_onebox({ mri,mci }, mri, mci, Box_dim);
			if (!Promotioncheck(Location.Promotion[pi], { mri,mci }, turn))
				break;
			Ps[mri][mci]->Draw_piece(mri, mci, 15);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
			Ps[ri][ci]->Print_onebox({ ri,ci }, ri, ci, Box_dim);
			Ps[ri][ci] = nullptr;
			pi++;
		}
		else
		{
			Ps[ri][ci]->Move_Piece(mri, mci);
			Ps[mri][mci] = Ps[ri][ci];
			Ps[ri][ci] = nullptr;
		}


		gotoRowCol(si, (Dim + 10) * Dim);
		cout << char('A' + ci) << (Dim - ri);

		gotoRowCol(si, (Dim + 20) * Dim);
		cout << char('A' + mci) << (Dim - mri);


		counter = si + 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		ChangeTurn();
	}

	gotoRowCol(Dim * 10, (Dim + 20) * Dim);
	cout << "                                  ";
	gotoRowCol(0, (Dim + 3) * Dim);
	cout << "                                      ";
	gotoRowCol(0, (Dim + 3) * Dim);
	if (turn == 1)
		cout << "White Turn";
	else if (turn == 0)
		cout << "Black Turn";
	gotoRowCol(counter, (Dim + 10) * Dim);



}

void Board::Select_Cordinates(int& ri, int& ci, int& m_ri, int& m_ci, bool& flag)
{
	char color;
	gotoRowCol(1, (Dim + 3) * Dim);
	cout << "                                                       ";
	gotoRowCol(1, (Dim + 3) * Dim);
	cout << "Select a piece ";
again: do
{

	getRowColbyLeftClick(ri, ci);
	gotoRowCol(1, (Dim + 3) * Dim);
	cout << "                                                       ";
	gotoRowCol(1, (Dim + 3) * Dim);



	ri /= Box_dim;
	ci /= Box_dim;

	if ((ri >= 0 && ri <= 1) && (ci * 10 >= 280 && ci * 10 <= 330))
	{
		if (!Load_check)
		{
			Init();
			turn = WHITE;
			Replay();
			Menu();
		}
		else if (Load_check)
		{
			LoadBoard();

			Replay();
			Menu();
		}



	}
	else if ((ri >= 2 && ri <= 3) && (ci * 10 >= 220 && ci * 10 <= 330))
	{
		if (Location.PA.size() < 1 && Location.CA.size() < 1)
			continue;
		ChangeTurn();
		Undo();
		gotoRowCol(0, (Dim + 3) * Dim);
		cout << "                                       ";
		gotoRowCol(0, (Dim + 3) * Dim);
		if (turn == 1)
			cout << "White Turn";
		else if (turn == 0)
			cout << "Black Turn";
		gotoRowCol(--counter, (Dim + 10) * Dim);
		cout << "                                       ";
		gotoRowCol(counter, (Dim + 15)* Dim);
		cout << "                                       ";
		gotoRowCol(counter, (Dim + 20) * Dim);
		cout << "                                       ";

	}
	else if ((ri >= 3 && ri <= 5) && (ci * 10 >= 220 && ci * 10 <= 330))
	{
		SaveBoard();
	}
	else if ((ri >= 6 && ri <= 7) && (ci * 10 >= 220 && ci * 10 <= 330))
	{
		NewGame();
		Draw();
		Location.CA.clear();
		Location.PA.clear();
		Location.IB.clear();
		Location.FB.clear();

	}
	else if (ri >= Dim || ci >= Dim)
		cout << "Enter valid co ordinates";
	else if (Ps[ri][ci] == nullptr)
		cout << "Enter valid location";
	else if (Ps[ri][ci]->Getcolour() != turn)
		cout << "Not your piece";
	else if (!Valid_Piece(ri, ci))
		cout << "Invalid Piece";


	else
	{

		gotoRowCol(counter, (Dim + 10) * Dim);
		cout << char('A' + ci) << (Dim - ri);
		break;
	}

} while (true);

if (turn == WHITE)
color = 15;
else
color = 8;
Highlight_path(ri, ci);
gotoRowCol(1, (Dim + 3) * Dim);
cout << "Select the destination ";

do
{

	getRowColbyLeftClick(m_ri, m_ci);

	gotoRowCol(1, (Dim + 3) * Dim);
	cout << "                                                       ";
	gotoRowCol(1, (Dim + 3) * Dim);

	m_ri /= Box_dim;
	m_ci /= Box_dim;
	if (m_ri >= Dim || m_ci >= Dim)
		cout << "Enter valid co ordinates";
	else if (m_ri == ri && m_ci == ci)
	{
		UnHighlight_path(ri, ci);
		goto again;
	}
	else if (Ps[m_ri][m_ci] != nullptr && Ps[m_ri][m_ci]->Getcolour() == turn)
		cout << "Your Piece already exists";
	else
	{
		UnHighlight_path(ri, ci);

		break;
	}

} while (true);


}

bool Board::Valid_Piece(int sri, int sci)
{

	Pawn* P = dynamic_cast<Pawn*>(Ps[sri][sci]);
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{

			if (Ps[ri][ci] == nullptr && Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }))
				return true;
			else if (Ps[ri][ci] != nullptr)
			{
				if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }) && turn != Ps[ri][ci]->Getcolour())
					return true;
			}
		}
	}
	return false;
}

bool Board::Valid_Move(int sri, int sci, Position KP)
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (sri == ri && sci == ci)
				continue;
			if (ri == KP.ri && ci == KP.ci)
				continue;
			if (Ps[ri][ci] == nullptr && Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }))
			{
				Location.IB.push_back(Ps[sri][sci]);
				Location.FB.push_back(Ps[ri][ci]);
				Location.CA.push_back({ ri,ci });
				Location.PA.push_back({ sri,sci });
				Ps[sri][sci]->Move_Piece(ri, ci,false);
				Ps[ri][ci] = Ps[sri][sci];
				Ps[sri][sci] = nullptr;
				if (!My_King_check())
				{
					Undo();

					return true;
				}
				Undo();
			}
			else if (Ps[ri][ci] != nullptr)
			{
				if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }) && Ps[sri][sci]->Getcolour() != Ps[ri][ci]->Getcolour())
				{
					Location.IB.push_back(Ps[sri][sci]);
					Location.FB.push_back(Ps[ri][ci]);
					Location.CA.push_back({ ri,ci });
					Location.PA.push_back({ sri,sci });
					Ps[sri][sci]->Move_Piece(ri, ci,false);
					Ps[ri][ci] = Ps[sri][sci];
					Ps[sri][sci] = nullptr;
					if (!My_King_check())
					{
						Undo();

						return true;
					}
					Undo();
				}
			}

		}
	}

	return false;
}

void Board::ChangeTurn()
{
	if (turn == WHITE)
		turn = BLACK;
	else if (turn == BLACK)
		turn = WHITE;
}

void Board::Highlight_box(Position S, int Box_dim)
{
	char ch = -37;

	for (int ci = S.ci * Box_dim; ci < S.ci * Box_dim + Box_dim; ci++)
	{
		gotoRowCol(S.ri * Box_dim, ci);
		cout << ch;
	}

	for (int ci = S.ci * Box_dim; ci < S.ci * Box_dim + Box_dim; ci++)
	{
		gotoRowCol(S.ri * Box_dim + Box_dim - 1, ci);
		cout << ch;
	}

	for (int ri = S.ri * Box_dim; ri < S.ri * Box_dim + Box_dim; ri++)
	{
		gotoRowCol(ri, S.ci * Box_dim);
		cout << ch;
	}

	for (int ri = S.ri * Box_dim; ri < S.ri * Box_dim + Box_dim; ri++)
	{
		gotoRowCol(ri, S.ci * Box_dim + Box_dim - 1);
		cout << ch;
	}
}

void Board::Kill_Highlight(Position S, int Box_dim)
{

	Ps[S.ri][S.ci]->Print_onebox(S, S.ri, S.ci, Box_dim);
	Ps[S.ri][S.ci]->Draw_piece(S.ri, S.ci, Get_Box_colour(S.ri, S.ci));

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}

void Board::Kill_UnHighlight(Position S, int Box_dim, char c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	Kill_Highlight(S, Box_dim);
}

void Board::Highlight_path(int sri, int sci)
{
	char c = 15;
	King* K = dynamic_cast<King*>(Ps[sri][sci]);
	ChangeTurn();
	Position P = King_cordinates();
	ChangeTurn();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{



			if (Ps[ri][ci] == nullptr)
			{
				if (K != nullptr)
				{
					if (Castlecheck({ sri,sci }, { ri,ci }))
					{
						Highlight_box({ ri,ci }, Box_dim);
					}
					else if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }) && !Selfcheck(P, { ri,ci }))
					{
						Highlight_box({ ri,ci }, Box_dim);
					}
				}
				else if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }))
				{
					Highlight_box({ ri,ci }, Box_dim);
				}
			}
			else if (turn != Ps[ri][ci]->Getcolour())
			{
				if (K != nullptr)
				{

					if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }) && !Selfcheck(P, { ri,ci }))
					{
						Highlight_box({ ri,ci }, Box_dim);
					}
				}
				else if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }))
				{
					Kill_Highlight({ ri,ci }, 10);
				}

			}

		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Board::UnHighlight_path(int sri, int sci)
{
	King* K = dynamic_cast<King*>(Ps[sri][sci]);
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{

			if (Ps[ri][ci] == nullptr)
			{

				if (K != nullptr && Castlecheck({ sri,sci }, { ri,ci }))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
					Ps[sri][sci]->Print_onebox({ ri,ci }, ri, ci, 10);
				}
				if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }))
				{

					if (Ps[ri][ci] == nullptr)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(ri, ci));
						Ps[sri][sci]->Print_onebox({ ri,ci }, ri, ci, 10);
					}
				}

			}
			else if (turn != Ps[ri][ci]->Getcolour())
			{

				if (Ps[sri][sci]->IsLegal({ sri,sci }, { ri,ci }))
				{
					Kill_UnHighlight({ ri,ci }, 10, Get_Box_colour(ri, ci));
				}
			}
		}
	}

}

int Board::GetDim()
{
	return Dim;
}

void Board::Undo()
{
	if (Location.PA.size() < 1 && Location.CA.size() < 1)
		return;

	char ch;
	int ri, ci, m_ri, m_ci;

	ri = Location.PA[Location.PA.size() - 1].ri;
	ci = Location.PA[Location.PA.size() - 1].ci;

	m_ri = Location.CA[Location.CA.size() - 1].ri;
	m_ci = Location.CA[Location.CA.size() - 1].ci;

	ch = (Ps[m_ri][m_ci]->Getcolour() == BLACK ? 6 : 8);

	Ps[m_ri][m_ci]->Move_Piece(ri, ci);
	Ps[ri][ci] = Location.IB[Location.IB.size() - 1];
	if (Location.FB[Location.FB.size() - 1] != nullptr)
	{
		Location.FB[Location.FB.size() - 1]->Draw_piece(m_ri, m_ci, ch);
		Ps[m_ri][m_ci] = Location.FB[Location.FB.size() - 1];

	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(m_ri, m_ci));
		Ps[m_ri][m_ci]->Print_onebox({ m_ri,m_ci }, m_ri, m_ci, Box_dim);
		Ps[m_ri][m_ci] = nullptr;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	Location.IB.pop_back();
	Location.FB.pop_back();
	Location.PA.pop_back();
	Location.CA.pop_back();


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

bool Board::check(Position P)
{


	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			Pawn* Pa = dynamic_cast<Pawn*>(Ps[ri][ci]);
			if (P.ri == ri && P.ci == ci)
				continue;
			if (Pa != nullptr && turn == Ps[ri][ci]->Getcolour())
			{
				if (Pa->Diagonalcheck({ ri,ci }, P))
				{
					return true;
				}
			}
			else if (Ps[ri][ci] != nullptr && Ps[ri][ci]->IsLegal({ ri,ci }, P) && turn == Ps[ri][ci]->Getcolour())
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::My_King_check()
{
	ChangeTurn();
	Position S = King_cordinates();

	if (check(S))
	{
		ChangeTurn();
		return true;
	}
	ChangeTurn();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(S.ri, S.ci));
	Ps[S.ri][S.ci]->Print_onebox(S, S.ri, S.ci, Box_dim);
	Ps[S.ri][S.ci]->Draw_piece(S.ri, S.ci, 15);

	return false;

}

bool Board::BlockPath(Position P)
{
	ChangeTurn();
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (ri == P.ri && ci == P.ci)
				continue;
			if (Ps[ri][ci] != nullptr && Ps[ri][ci]->Getcolour() == turn)
			{
				if (Check_everyPath({ ri,ci }, P))
				{
					ChangeTurn();
					return true;
				}
			}
		}
	}
	ChangeTurn();
	return false;
}

bool Board::Check_everyPath(Position S, Position P)
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (ri == S.ri && ci == S.ci)
				continue;

			if (Ps[ri][ci] == nullptr)
			{
				if (Ps[S.ri][S.ci]->IsLegal(S, { ri,ci }))
				{
					Location.IB.push_back(Ps[S.ri][S.ci]);
					Location.FB.push_back(Ps[ri][ci]);
					Location.CA.push_back({ ri,ci });
					Location.PA.push_back({ S.ri,S.ci });
					Ps[S.ri][S.ci]->Move_Piece(ri, ci,false);
					Ps[ri][ci] = Ps[S.ri][S.ci];
					Ps[S.ri][S.ci] = nullptr;


					ChangeTurn();
					if (!check(P))
					{
						/*Ps[ri][ci]->Move_Piece(S.ri, S.ci);
						Ps[S.ri][S.ci] = Ps[ri][ci];
						Ps[ri][ci] = nullptr;*/
						Undo();
						ChangeTurn();
						return true;
					}
					ChangeTurn();
					/*Ps[ri][ci]->Move_Piece(S.ri, S.ci);
					Ps[S.ri][S.ci] = Ps[ri][ci];
					Ps[ri][ci] = nullptr;*/
					Undo();

				}
			}
			else
			{
				if (Ps[ri][ci]->Getcolour() != turn && Ps[S.ri][S.ci]->IsLegal(S, { ri,ci }))
				{
					Location.IB.push_back(Ps[S.ri][S.ci]);
					Location.FB.push_back(Ps[ri][ci]);
					Location.CA.push_back({ ri,ci });
					Location.PA.push_back({ S.ri,S.ci });
					Ps[S.ri][S.ci]->Move_Piece(ri, ci,false);
					Ps[ri][ci] = Ps[S.ri][S.ci];
					Ps[S.ri][S.ci] = nullptr;

					ChangeTurn();
					if (!check(P))
					{
						/*Ps[ri][ci]->Move_Piece(S.ri, S.ci);
						Ps[S.ri][S.ci] = Ps[ri][ci];
						Ps[ri][ci] = nullptr;*/
						Undo();
						ChangeTurn();
						return true;
					}

					ChangeTurn();
					/*Ps[ri][ci]->Move_Piece(S.ri, S.ci);
					Ps[S.ri][S.ci] = Ps[ri][ci];
					Ps[ri][ci] = nullptr;*/
					Undo();

				}

			}
		}
	}
	return false;
}

bool Board::Selfcheck(Position S, Position P)
{
	King* K;
	K = dynamic_cast<King*>(Ps[S.ri][S.ci]);
	if (K == nullptr)
	{
		return false;
	}
	else
	{
		ChangeTurn();
		if (check(P))
		{
			ChangeTurn();
			return true;
		}
		ChangeTurn();
	}
	return false;
}

bool Board::checkmate(Position P)
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (Ps[ri][ci] != nullptr)
			{
				if (Ps[P.ri][P.ci]->IsLegal({ P.ri,P.ci }, { ri,ci }) && turn == Ps[ri][ci]->Getcolour())
				{
					ChangeTurn();
					if (!Selfcheck(P, { ri,ci }))
					{
						ChangeTurn();
						return false;
					}
					ChangeTurn();
				}
			}
			else
			{
				if (Ps[P.ri][P.ci]->IsLegal({ P.ri,P.ci }, { ri,ci }))
				{
					ChangeTurn();
					if (!Selfcheck(P, { ri,ci }))
					{
						ChangeTurn();
						return false;
					}
					ChangeTurn();

				}
			}


		}
	}

	if (BlockPath(P))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		return false;
	}
	else
		return true;

}

bool Board::Stalemate()
{


	ChangeTurn();
	Position KP = King_cordinates();
	ChangeTurn();
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (Ps[ri][ci] != nullptr && Ps[ri][ci]->Getcolour() == turn && Valid_Move(ri, ci, KP))
			{

				return false;
			}
		}
	}


	return true;
}

bool Board::Castlecheck(Position S, Position P)
{

	int ri = (turn == WHITE ? Dim - 1 : 0);
	if (!((P.ri == Dim - 1 || P.ri == 0) && (P.ci == Dim - 2 || P.ci == Dim - 6)))
		return false;
	King* K = dynamic_cast<King*>(Ps[S.ri][S.ci]);


	if (K != nullptr)
	{
		if (!Ps[S.ri][S.ci]->GetFirst())
			return false;
	}
	else
		return false;

	if (P.ci > S.ci && P.ri == ri)
	{
		Rook* R = dynamic_cast<Rook*>(Ps[S.ri][S.ci + 3]);
		if (R != nullptr)
		{
			if (!Ps[S.ri][S.ci + 3]->GetFirst())
				return false;

			if (!R->IsVerticalPathClear({ S.ri,S.ci + 3 }, S))
				return false;

		}
	}
	else if (P.ci < S.ci && P.ri == ri)
	{
		Rook* R = dynamic_cast<Rook*>(Ps[S.ri][S.ci - 4]);
		if (R != nullptr)
		{
			if (!Ps[S.ri][S.ci - 4]->GetFirst())
				return false;

			if (!R->IsVerticalPathClear({ S.ri,S.ci - 4 }, S))
				return false;

		}
	}
	else
		return false;
	return true;

}

void Board::ShortCastling(Position S, Position P)
{
	King* K = dynamic_cast<King*>(Ps[S.ri][S.ci]);
	Rook* R = dynamic_cast<Rook*>(Ps[S.ri][S.ci + 3]);

	if (Ps[S.ri][S.ci]->IsLegal(S, { S.ri,S.ci + 1 }) && !Selfcheck(S, { S.ri,S.ci + 1 }))
	{

		if (!Selfcheck(S, { S.ri,S.ci + 2 }))
		{

			Location.FB.push_back(Ps[S.ri][S.ci + 2]);
			Location.PA.push_back({ S.ri,S.ci });
			Location.CA.push_back({ S.ri,S.ci + 2 });
			K->Move_Piece(S.ri, S.ci + 2);
			Ps[S.ri][S.ci + 2] = Ps[S.ri][S.ci];
			Ps[S.ri][S.ci] = nullptr;


			Location.IB.push_back(Ps[S.ri][S.ci + 3]);
			Location.FB.push_back(Ps[S.ri][S.ci + 1]);

			Location.PA.push_back({ S.ri,S.ci + 3 });
			Location.CA.push_back({ S.ri,S.ci + 1 });
			R->Move_Piece(S.ri, S.ci + 1);
			Ps[S.ri][S.ci + 1] = Ps[S.ri][S.ci + 3];
			Ps[S.ri][S.ci + 3] = nullptr;

		}
		else
			ChangeTurn();

	}
	else
		ChangeTurn();

}

void Board::LongCastling(Position S, Position P)
{
	King* K = dynamic_cast<King*>(Ps[S.ri][S.ci]);
	Rook* R = dynamic_cast<Rook*>(Ps[S.ri][S.ci - 4]);

	if (Ps[S.ri][S.ci]->IsLegal(S, { S.ri,S.ci - 1 }) && !Selfcheck(S, { S.ri,S.ci - 1 }))
	{

		if (!Selfcheck(S, { S.ri,S.ci - 2 }))
		{

			Location.FB.push_back(Ps[S.ri][S.ci - 2]);
			Location.PA.push_back({ S.ri,S.ci });
			Location.CA.push_back({ S.ri,S.ci - 2 });
			K->Move_Piece(S.ri, S.ci - 2);
			Ps[S.ri][S.ci - 2] = Ps[S.ri][S.ci];
			Ps[S.ri][S.ci] = nullptr;


			Location.IB.push_back(Ps[S.ri][S.ci - 4]);
			Location.FB.push_back(Ps[S.ri][S.ci - 1]);

			Location.PA.push_back({ S.ri,S.ci - 4 });
			Location.CA.push_back({ S.ri,S.ci - 1 });
			R->Move_Piece(S.ri, S.ci - 1);
			Ps[S.ri][S.ci - 1] = Ps[S.ri][S.ci - 4];
			Ps[S.ri][S.ci - 4] = nullptr;

		}
		else
			ChangeTurn();

	}
	else
		ChangeTurn();

}

bool Board::Promotion(Position S, Position P)
{

	Pawn* Pa = dynamic_cast<Pawn*>(Ps[S.ri][S.ci]);
	if (Pa != nullptr)
	{
		if (Pa->Getcolour() == WHITE && P.ri == 0)
			Promote(P, 0, WHITE);
		else if (Pa->Getcolour() == BLACK && P.ri == Dim - 1)
			Promote(P, 7, BLACK);
		else
			return false;

		return true;
	}
	else
		return false;
}

void Board::Promote(Position S, int ri, COLOR C)
{
	char choice;
	if (S.ri == ri)
	{
		do
		{
			gotoRowCol(Dim * 10, Dim * 20);
			cout << "Enter Piece symbol to Promote";
			cin >> choice;
			gotoRowCol(Dim * 10, Dim * 20);
			cout << "                               ";
			if (!Promotioncheck(choice, S, C))
				continue;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Get_Box_colour(S.ri, S.ci));
			Ps[S.ri][S.ci]->Print_onebox(S, S.ri, S.ci, Box_dim);
			Ps[S.ri][S.ci]->Draw_piece(S.ri, S.ci, 15);
			break;
		} while (true);
	}
	Location.Promotion.push_back(choice);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

bool Board::Promotioncheck(char choice, Position S, COLOR C)
{
	if (choice == 'q' || choice == 'Q')
		Ps[S.ri][S.ci] = new Queen(Position{ S.ri,S.ci }, C, this);
	else if (choice == 'k' || choice == 'K')
		Ps[S.ri][S.ci] = new Knight(Position{ S.ri,S.ci }, C, this);
	else if (choice == 'b' || choice == 'B')
		Ps[S.ri][S.ci] = new Bishop(Position{ S.ri,S.ci }, C, this);
	else if (choice == 'r' || choice == 'R')
		Ps[S.ri][S.ci] = new Rook(Position{ S.ri,S.ci }, C, this);
	else
		return false;
	return true;
}

void Board::Replaycheckmate()
{


	char c;
	gotoRowCol(Dim * 10, Dim * 20);
	cout << "                               ";
	cout << "Press P to replay game or Q to quit" << endl;
	cin >> c;
	if (c == 'p' || c == 'P')
	{
		if (!Load_check)
		{
			Init();
			Replay();

		}
		else if (Load_check)
		{
			LoadBoard();
			Replay();
		}

	}
	return;
}

bool Board::Repitition()
{
	int count = 0;
	for (int i = 0; i + 2 < Location.PA.size(); i++)
	{
		if ((Location.CA[i + 2].ri == Location.PA[i].ri) && (Location.CA[i + 2].ci == Location.PA[i].ci))
			count++;
		else
			count = 0;
	}

	if (count == 6)
		return true;
	return false;
}

Position Board::King_cordinates()
{
	Position P{};
	King* K;
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (Ps[ri][ci] != nullptr && turn != Ps[ri][ci]->Getcolour())
			{

				K = dynamic_cast<King*>(Ps[ri][ci]);
				if (K != nullptr)
				{
					P.ri = ri;
					P.ci = ci;
					return P;
				}
			}
		}
	}
	return P;
}

Pieces* Board::Get(Position P)
{
	return Ps[P.ri][P.ci];
}

COLOR Board::GetTurn()
{
	return turn;
}

Board::~Board()
{

}
