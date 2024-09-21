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



