#include <iostream>
#include"SkipList.h"
using namespace std;

void menu()
{
	cout << "1. Insert" << endl
		<< "2. Search" << endl
		<< "3. Delete" << endl;
}

int main()
{
	SkipList T;								//Randomized Skip List
	T.Insert(5);
	T.Insert(15);
	T.Insert(35);
	T.Insert(7);
	T.Insert(-65);
	T.Insert(40);
	T.Insert(-100);
	T.Print();

	if (T.Search(100))
		cout << 100 << " Found";
	else
		cout << 100 << " Not found";

	cout << endl << endl;

	if (T.Delete(5))
		cout << 5 << " Deleted";
	else
		cout << 5 << " Not deleted";
	cout << endl << endl;
	T.Print();

	/*int choice;
	while (true)
	{
		menu(), cout << endl;
		cout << "Enter task number: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter number to insert: ";
			cin >> choice;
			T.Insert(choice);
			break;
		case 2:
			cout << "Enter number to search: ";
			cin >> choice;
			if (T.Search(choice))
				cout << choice << " Found";
			else
				cout << choice << " not Found";
			break;
		case 3:
			cout << "Enter number to delete: ";
			cin >> choice;
			if (T.Delete(choice))
				cout << choice << " is deleted";
			else
				cout << choice << " is not deleted";
		case 4:
			break;
		}

		cout << endl << endl;
		T.Print();
	}*/
}

