#include "TextEditor.h"
#include<windows.h>
#include<conio.h>
#include<iostream>
#include<string>
using namespace std;



void gotoRowCol(int rpos, int cpos)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int xpos = cpos, ypos = rpos;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void TextEditor::menu()
{
	cout << "Press Control u to uppercase" << endl
		<< "Press Control l to lowercase" << endl
		<< "Press Control w to find a word" << endl
		<< "Press Control s to find a sentence" << endl
		<< "Press Control e to find a substring" << endl
		<< "Press Control r to replace" << endl
		<< "Press Control p for prefix and postfix" << endl
		<< "Press Control i for average word length" << endl
		<< "Press Control t for substring count" << endl
		<< "Press Control k for Special character count" << endl
		<< "Press Control n for number of sentences" << endl
		<< "Press Control b for Biggest word length" << endl
		<< "Press Control z for smallest word length" << endl
		<< "Press Control a for word with most number of other words" << endl
		<< "Press Control q for find and replace" << endl
		<< "Press Control y for largest para word length" << endl
		<< "Press Control v for merging a file" << endl
		<< "Press Shift   u for encoding/decoding" << endl
		<< "Press Control x for opening a different file" << endl
		<< "Press Control O to open menu at anytime" << endl
		<< "Press Control g to exit" << endl;

}
TextEditor::TextEditor(string name)
{
	ADocument = new Document * [NOD];
	ADocument[0] = new Document(name);
	ADocument[0]->PrintDocument();
}

void TextEditor::Add_Document()
{
	system("cls");
	char input;
	string name, password;
	cout << "Enter file name: ";
	cin >> name;
	cout << "Do you want create a new file? ";
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		ofstream fout(name);
		fout << 1 << endl;
		cout << "Do you want to add a password?(Y for yes)" << endl;
		cin >> input;
		if (input == 'y' || input == 'Y')
		{
			cout << "Enter password: ";
			cin >> password;
			fout << 1 << " " << password;
		}
		else
			fout << 0;

	}

	Document** heap = new Document * [NOD + 1];
	for (int i = 0; i < NOD; i++)
	{
		heap[i] = ADocument[i];
	}
	heap[NOD] = new Document(name);
	delete[] ADocument;
	ADocument = heap;
	NOD++;

	system("cls");
}
void TextEditor::Print_Documents()
{
	system("cls");
	cout << "Number of documents: " << endl;
	for (int i = 0; i < NOD; i++)
	{
		cout << i + 1 << "." << ADocument[i]->Dname << endl;
	}
	system("pause");
	system("cls");
}
void TextEditor::Editing()
{
	int d, index = 0;
	char ch;
	cr = 0, cc = 0;
	bool IsFirst = false;
	gotoRowCol(cr, cc);
	while (true)
	{

		if (_kbhit())
		{
			d = _getch();

			if (d == 224)
			{
				d = _getch();
				if (d == 72)
				{
					if (cr > 0)
						cr--;
					if (ADocument[index]->Ls[cr].Size < cc)
						cc = ADocument[index]->Ls[cr].Size;
				}
				else if (d == 80)
				{

					if (ADocument[index]->NOLS - 1 != cr)
						cr++;
					if (ADocument[index]->Ls[cr].Size < cc)
						cc = ADocument[index]->Ls[cr].Size;
					while (ADocument[index]->Ls[cr].Cs[cc] == ' ')
					{
						cc++;
					}
				}
				else if (d == 77)
				{
					if (cc != ADocument[index]->Ls[cr].Size)
						cc++;
					if (cc == ADocument[index]->Ls[cr].Size && ADocument[index]->NOLS - 1 != cr)
					{

						cc = 0;
						cr++;

					}
				}
				else if (d == 75)
				{

					cc--;
					if (cc < 0)
					{
						cr--;
						cc = ADocument[index]->Ls[cr].Size;
					}
				}
			}
			else if (d == 13)
			{

				ADocument[index]->InsertLine(cr, cc);
				system("cls");
				ADocument[index]->PrintDocument();
				cc = 0;
				cr++;
				/*if(cr!=ADocument->NOLS-1)
				cr++;
				cc = 0;*/
			}
			else if (d == 8)
			{

				if (cc >= 1 && cr >= 0)
				{

					ADocument[index]->Back(cr, cc);
					system("cls");
					ADocument[index]->PrintDocument();
					cc--;
				}
				else if (cc < 1 && cr >= 1)
				{
					ADocument[index]->Merge(cr, cc);
					system("cls");
					ADocument[index]->PrintDocument();
					cc = ADocument[index]->Ls[cr - 1].Size;
					cr--;
				}


			}


			else if (d == 7)
			{
				char ch;
				system("cls");
				cout << "Do you want to save?(Y for yes)" << endl;
				cin >> ch;
				if (ch == 'Y' || ch == 'y')
				{
					for (int i = 0; i < NOD; i++)
						ADocument[index]->WriteDocument();
				}

				return;


			}
			else if (d == 1)
			{
				ADocument[index]->Scramble(cr, cc);
				ADocument[index]->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 21)
			{
				system("cls");
				ADocument[index]->Ls[cr].Uppercase(cc);
				ADocument[index]->PrintDocument();
			}
			else if (d == 85)
			{
				ADocument[index]->Encode_file(IsFirst);
				ADocument[index]->PrintDocument();
			}
			else if (d == 22)
			{
				ADocument[index]->merge_files();
				ADocument[index]->PrintDocument();
			}
			else if (d == 25)
			{
				ADocument[index]->para_length();
				ADocument[index]->PrintDocument();
			}
			else if (d == 17)
			{
				system("cls");
				ADocument[index]->choice(cc, cr, cc);
				ADocument[index]->PrintDocument();
			}
			else if (d == 12)
			{
				ADocument[index]->Ls[cr].Lowercase(cc);
				ADocument[index]->PrintDocument();
			}
			else if (d == 23)
			{
				system("cls");
				cout << "Do you want to find case sensitive or insensitive?(C or I)" << endl;
				cin >> ch;
				if (ch == 'c' || ch == 'C')
					ADocument[index]->FindwordCaseSensitive(cr, cc);
				else if (ch == 'i' || ch == 'I')
					ADocument[index]->FindwordInCaseSensitive(cr, cc);

			}
			else if (d == 19)
			{
				ADocument[index]->FindAsentence(cr, cc);
				ADocument[index]->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 5)
			{
				system("cls");
				cout << "Do you want to find case sensitive or insensitive?(C or I)" << endl;
				cin >> ch;
				if (ch == 'c' || ch == 'C')
					ADocument[index]->FindSubstringCaseSensitive(cr, cc);
				else if (ch == 'i' || ch == 'I')
					ADocument[index]->FindSubstringInCaseSensitive(cr, cc);

			}
			else if (d == 18)
			{
				system("cls");
				cout << "Do you want to replace first or ALL?(F or A)" << endl;
				cin >> ch;
				if (ch == 'f' || ch == 'F')
					ADocument[index]->Replaceword(cr, cc);
				else if (ch == 'a' || ch == 'A')
					ADocument[index]->Replaceeveryword(cr, cc);


				ADocument[index]->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 16)
			{

				system("cls");
				cout << "Do you want to add prefix or postfix?(e or o)" << endl;
				cin >> ch;
				if (ch == 'e' || ch == 'E')
					ADocument[index]->Addprefix(cr, cc);
				else if (ch == 'o' || ch == 'O')
					ADocument[index]->Addpostfix(cr, cc);

				ADocument[index]->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 9)
			{
				ADocument[index]->Average();
				ADocument[index]->PrintDocument();
			}
			else if (d == 20)
			{
				ADocument[index]->Substringcount();
				ADocument[index]->PrintDocument();
			}
			else if (d == 11)
			{
				ADocument[index]->Specialcharacter_count();
				ADocument[index]->PrintDocument();
			}
			else if (d == 14)
			{
				ADocument[index]->Number_of_sentences();
				ADocument[index]->PrintDocument();
			}
			else if (d == 2)
			{
				ADocument[index]->LargestWord_Length(cr, cc);
				ADocument[index]->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 26)
			{
				ADocument[index]->SmallestWord_Length(cr, cc);
				ADocument[index]->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 15)
			{
				system("cls");
				menu();
				system("pause");
				system("cls");
				ADocument[index]->PrintDocument();
			}
			else if (d == 24)
			{
				Print_Documents();
				int check;
				cout << "Enter file number or 0 for new file: ";
				cin >> check;
				if (check > 0 && check <= NOD)
					index = check - 1;
				else if (check == 0)
				{
					Add_Document();
					index = NOD - 1;

				}

				system("cls");
				ADocument[index]->PrintDocument();
				cr = 0;
				cc = 0;
			}
			else
			{
				ch = char(d);
				ADocument[index]->InsertAcharacter(cr, cc, ch);
				ADocument[index]->PrintDocument();
				cc++;

			}

			gotoRowCol(cr, cc);

		}
	}
}



