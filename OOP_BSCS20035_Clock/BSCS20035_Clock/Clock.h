#include<iostream>
#include<fstream>
#include<string>
using namespace std;


#pragma once

struct position
{
	int row;
	int col;
};

class Clock
{
private:
	int hour;
	int min;
	int sec;
	string TZ;
	string TZ1;
	position pos;
	int timezone;

public:
	Clock(int hour = 0, int min = 0, int sec = 0, string TZ = " ", string TZ1 = " ", position pos = {});
	void init(int h, int m, int s, string TZ,string TZ1, position pos);
	void init24();
	void increment();
	void increment24();
	void Display();
	void Display24();
	void systemtimeinit12(int t, string TZ, position pos);
	void systemtime(Clock& S);
	void systemtimeinit(int timezone, string TZ, position pos);
	static void gotoRowCol(int rpos, int cpos);
	static void wait(float sec);
};

