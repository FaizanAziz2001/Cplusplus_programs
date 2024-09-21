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
	hour = (TZ1 == "PM") ? hour + 12:hour;
	

}

void Clock::systemtime(Clock& S)
{

	tm currtime;
	time_t timet = time(0);
	localtime_s(&currtime, &timet);

	S.hour = currtime.tm_hour;
	S.min = currtime.tm_min;
	S.sec = currtime.tm_sec;
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
	cout << setfill(' ');
	(pos.col > 50)? cout << right << setw(13) << TZ: cout << TZ;
	gotoRowCol(pos.row + 1, pos.col);
	cout << setfill('0') << setw(2) << hour << " :" << setw(2) << min << " :" << setw(2) << sec << " " << TZ1;
}

void Clock::Display24()
{
	gotoRowCol(pos.row, pos.col);
	cout << setfill(' ');
	(pos.col > 50) ? cout << right << setw(10) << TZ : cout << TZ;
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



