#pragma once

struct Position
{
	int ri{};
	int ci{};
};


enum COLOR
{
	BLACK,WHITE
};

int Get_Box_colour(int ri, int ci);


void gotoRowCol(int rpos, int cpos);

void getRowColbyLeftClick(int& rpos, int& cpos);





