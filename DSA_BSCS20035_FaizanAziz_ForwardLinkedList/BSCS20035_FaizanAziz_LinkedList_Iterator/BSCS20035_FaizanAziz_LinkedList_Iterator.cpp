
#include <iostream>
#include"ForwardList.h"
#include"Queue.h"
#include"Stack.h"
using namespace std;

int main()
{

	forwardlist<int> F;
	F.InsertAtEnd(50);
	F.InsertAtEnd(100);
	F.InsertAtEnd(700);
	F.InsertAtEnd(200);

	for (auto t = F.Begin(); t != F.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl; 
	auto p = F.Begin()+2;

	
	F.Insertbefore(p, 999);

	for (auto t = F.Begin(); t != F.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl;

	p++;


	F.InsertAfter(p, 999);

	for (auto t = F.Begin(); t != F.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl;

	F.RemoveAt(p);

	for (auto t = F.Begin(); t != F.End(); t++)
	{
		cout << *t << " ";
	}



}
