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
	void init(int h, int m, int s, string TZ, string TZ1, position pos);
	void init24();
	void increment();
	void increment24();
	void Display();
	void Display24();
	void systemtime(Clock& S);
	void systemtimeinit(int timezone, string TZ, position pos);
	void systemtimeinit12(int t, string TZ, position pos);
	static void gotoRowCol(int rpos, int cpos);
	static void wait(float sec);
};




#include "Clock.h"
#include<iomanip>
#include<Windows.h>
using namespace std;

Clock::Clock(int h, int m, int s, string TZ, string TZ1, position pos)
{
	init(h, m, s, TZ, TZ1, pos);
}

void Clock::init(int h, int m, int s, string TZ, string TZ1, position pos)
{
	hour = h;
	min = m;
	sec = s;
	this->TZ = TZ;
	this->TZ1 = TZ1;
	this->pos = pos;

}

void Clock::init24()
{
	this->TZ = TZ;
	this->TZ1 = TZ1;
	this->pos = pos;
	hour = (TZ1 == "PM") ? hour + 12 : hour;


}

void Clock::systemtime(Clock& S)
{
	char systemtime[26];
	time_t currenttime = time(NULL);
	ctime_s(systemtime, sizeof systemtime, &currenttime);
	int sum1 = 0, sum2 = 0, sum3 = 0;
	for (int i = 0, j = 11, k = 14, l = 17; i < 2; j++, k++, l++, i++)
	{

		sum1 = systemtime[j] - 48;
		sum2 = systemtime[k] - 48;
		sum3 = systemtime[l] - 48;
		S.hour = S.hour * 10 + sum1;
		S.min = S.min * 10 + sum2;
		S.sec = S.sec * 10 + sum3;
	}
}

void Clock::systemtimeinit(int t, string TZ, position pos)
{
	Clock system;
	this->pos = pos;
	this->timezone = t;
	this->TZ = TZ;

	systemtime(system);

	hour = system.hour - timezone;
	hour = (hour < 0) ? hour + 24 : hour;
	min = system.min;
	sec = system.sec;

}

void Clock::systemtimeinit12(int t, string TZ, position pos)
{
	Clock system;
	this->pos = pos;
	this->timezone = t;
	this->TZ = TZ;

	systemtime(system);

	this->TZ1 = (system.hour > 12) ? "PM" : "AM";
	hour = (system.hour % 12) - timezone;
	if (hour < 0)
	{
		hour = hour + 12;
		this->TZ1 = "AM";
	}
	min = system.min;
	sec = system.sec;

}

void Clock::increment()
{
	sec++;
	if (sec == 60)
	{
		sec = 0;
		min++;
		if (min == 60)
		{
			min = 0;
			hour++;

			if (hour == 12)
			{
				TZ1 = (TZ1 == "AM") ? "PM" : "AM";
			}
			if (hour == 13)
				hour = 1;
		}
	}

}

void Clock::increment24()
{
	sec++;
	if (sec == 60)
	{
		sec = 0;
		min++;
		if (min == 60)
		{
			min = 0;
			hour++;

			if (hour == 24)
				hour = 0;

		}
	}

}

void Clock::Display()
{
	gotoRowCol(pos.row, pos.col);
	cout << TZ;
	gotoRowCol(pos.row + 1, pos.col);
	cout << setfill('0') << setw(2) << hour << " :" << setw(2) << min << " :" << setw(2) << sec << " " << TZ1;
}

void Clock::Display24()
{
	gotoRowCol(pos.row, pos.col);
	cout << TZ;
	gotoRowCol(pos.row + 1, pos.col);
	cout << setfill('0') << setw(2) << hour << " :" << setw(2) << min << " :" << setw(2) << sec;
}

void Clock::gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Clock::wait(float sec)
{
	long long prevtime = time(0);
	long long currtime = time(0);
	while (currtime - prevtime <= sec)
	{
		currtime = time(0);
	}

}



/*

5
2 30 55 AM PK 0 0
5 26 23 PM Italy 0 88
11 30 59 AM US 20 48
10 15 5 AM UK 38 0
7 4 8 PM Spain 38 88


*/

/*

5
0 PK 0 0
3 Italy 0 88
9 US 20 48
4 UK 38 0
3 Spain 38 88

*/




#include<fstream>
#include <iostream>
#include<time.h>
#include"Clock.h"
#include<conio.h>
using namespace std;


void init(Clock*& data, int& size)
{
	ifstream fin("Clock.txt");
	fin >> size;
	data = new Clock[size];
	int h, m, s;
	position pos;
	string TZ, TZ1;
	for (int i = 0; i < size; i++)
	{
		fin >> h >> m >> s >> TZ1 >> TZ >> pos.row >> pos.col;
		data[i].init(h, m, s, TZ, TZ1, pos);
	}
}

void convertTo24(Clock* data, int& size)
{
	for (int i = 0; i < size; i++)
	{
		data[i].init24();
	}
}

void systeminit(Clock*& data, int& size)
{
	ifstream fin("Timezone.txt");
	fin >> size;
	data = new Clock[size];
	int Timezone;
	position pos;
	string TZ;
	for (int i = 0; i < size; i++)
	{
		fin >> Timezone >> TZ >> pos.row >> pos.col;
		data[i].systemtimeinit(Timezone, TZ, pos);

	}
}

void systeminit12(Clock*& data, int& size)
{
	ifstream fin("Timezone.txt");
	fin >> size;
	data = new Clock[size];
	int Timezone;
	position pos;
	string TZ;
	for (int i = 0; i < size; i++)
	{
		fin >> Timezone >> TZ >> pos.row >> pos.col;
		data[i].systemtimeinit12(Timezone, TZ, pos);

	}
}

void DisplayAllClocks(Clock* data, int size, int choice)
{
	if (choice == 1)
		for (int i = 0; i < size; i++)
		{
			data[i].Display();
		}
	else if (choice == 2)
		for (int i = 0; i < size; i++)
		{
			data[i].Display24();
		}
}

void IncrementAllClocks(Clock* data, int size, int choice)
{
	if (choice == 1)
		for (int i = 0; i < size; i++)
		{
			data[i].increment();
		}
	else if (choice == 2)
	{
		for (int i = 0; i < size; i++)
		{
			data[i].increment24();
		}
	}
}

void menu()
{
	system("cls");
	cout << "1. Display clock in 12 hour format" << endl;
	cout << "2. Display clock in 24 hour format" << endl;
}

void menu2()
{
	system("cls");
	cout << "1. Read time from file" << endl;
	cout << "2. Read System time" << endl;
}

void clock(Clock*& data, int size)
{
	init(data, size);
	int choice;
	char cont;
	do
	{
		menu();
		cout << "Enter Clock format: ";
		cin >> choice;
		system("cls");
		if (choice == 2)
			convertTo24(data, size);
		while (!_kbhit())
		{
			DisplayAllClocks(data, size, choice);
			Clock::wait(0.5);
			IncrementAllClocks(data, size, choice);

		}
		system("cls");
		cout << endl << endl << "Do you want to continue?(y for yes)";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
}

void systemclock(Clock*& data, int size)
{
	int choice;
	char cont;
	do
	{
		menu();
		cout << "Enter Clock format: ";
		cin >> choice;
		system("cls");
		if (choice == 1)
			systeminit12(data, size);
		else if (choice == 2)
			systeminit(data, size);

		while (!_kbhit())
		{
			DisplayAllClocks(data, size, choice);
			Clock::wait(0.5);
			IncrementAllClocks(data, size, choice);

		}

		system("cls");
		cout << endl << endl << "Do you want to continue?(y for yes)";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
}

void clockmenu(Clock* data, int size)
{
	char cont;
	int choice;
	do
	{
		menu2();
		cout << "Enter task number: ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			clock(data, size);
			break;
		case 2:
			systemclock(data, size);
			break;
		}

		delete[] data;
		cout << endl << endl << "Do you want to continue program?(y for yes)";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');

}

int main()
{
	Clock* data{};
	int size = 0;
	clockmenu(data, size);

	return 0;
}



/*

				Sample output:

1. Read time from file
2. Read System time
Enter task number :2


1. Display clock in 12 hour format
2. Display clock in 24 hour format
Enter Clock format : 1


PK                                                                                      Italy
07 : 52 : 40 PM                                                                          04 : 52 : 40 PM


















										US
										10 :52 : 40 AM
















UK                                                                                      Spain
03 :52 : 40 PM                                                                          04 : 52 : 40 PM

Do you want to continue ? (y for yes)
n


Do you want to continue program ? (y for yes)n

*/