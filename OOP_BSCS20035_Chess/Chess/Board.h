#pragma once
#include"Pieces.h"
#include"Header.h"
#include<vector>
#include<iostream>
using namespace std;


class Pieces;

struct Position_vector
{
	vector<Pieces*> IB{};
	vector<Pieces*> FB{};
	vector<Position> PA{};
	vector<Position> CA{};
	vector<char> Promotion{};
};
class Board
{
	int Dim;
	int Box_dim = 10;
	int counter;
	Pieces*** Ps;
	COLOR turn = WHITE;
	bool Load_check;
	Position_vector Location{};
public:
	Board();
	int GetDim();
	void Init();
	void Print_Board(char ch, int sri, int sci, char c);
	void Draw();
	void Play();
	void SaveBoard();
	void LoadBoard();
	void Replay();
	void Select_Cordinates(int& ri, int& ci, int& m_ri, int& m_ci,bool&);
	void Move();
	void Highlight_box(Position S, int Box_dim);
	void Kill_Highlight(Position S, int Box_dim);
	void Kill_UnHighlight(Position S, int Box_dim,char c);
	void Highlight_path(int ri,int si);
	void UnHighlight_path(int ri, int si);
	void ChangeTurn();
	void Undo();
	bool BlockPath(Position);
	bool Check_everyPath(Position S,Position);
	bool Valid_Piece(int sri, int sci);
	bool Valid_Move(int sri, int sci,Position P);
	bool check(Position);
	bool checkmate(Position);
	bool Stalemate();
	bool Castlecheck(Position, Position);
	void ShortCastling(Position,Position);
	void LongCastling(Position, Position);
	bool Selfcheck(Position,Position);
	bool My_King_check();
	void Menu();
	void NewGame();
	bool Promotion(Position S, Position P);
	void Promote(Position, int,COLOR);
	bool Promotioncheck(char,Position,COLOR);
	void Replaycheckmate();
	bool Repitition();
	Position King_cordinates();
	Pieces* Get(Position P);
	COLOR GetTurn();
	~Board();
};

