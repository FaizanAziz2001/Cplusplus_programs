
#include <iostream>
#include"Double_Link.h"
using namespace std;

int main()
{
	Double_Link<int> L;
	Double_Link<int> Splice;


	L.InsertAtFront(50);
	L.InsertAtFront(100);

	auto t = L.Begin()+1;
	L.InsertAtBefore(t, 999);
	L.InsertAtFront(150);
	L.InsertAtFront(200);
	L.InsertAtFront(250);
	Splice.InsertAtTail(-500);
	Splice.InsertAtTail(-400);
	Splice.InsertAtTail(-300);
	Splice.InsertAtTail(-200);


	cout << "Linked List 1: ";
	for (auto t = L.Begin(); t != L.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl;

	cout << "Linked List 2: ";
	for (auto t = Splice.Begin(); t != Splice.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl << endl;


	t=L.Begin() + 2;

	L.Splice(t, Splice.Begin(), Splice.Tail());
	cout << "Starting point: " << *t << endl;
	cout << "Ending point: " << *(L.Tail()) << endl << endl;


	cout << "Spliced List: ";
	for (auto t = L.Begin(); t != L.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl;
}

