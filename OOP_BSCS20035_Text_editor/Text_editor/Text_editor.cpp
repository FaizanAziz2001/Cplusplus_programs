#include<conio.h>
#include<iostream>
using namespace std;
#include "TextEditor.h"




int main()
{
	char cont;

	do
	{

		TextEditor::menu();
		system("pause");
		system("cls");
		TextEditor TE("input.txt");
		TE.Editing();
		

		system("cls");
		cout << "Do you want to continue?(Y for yes)" << endl;
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');

	return 0;
}