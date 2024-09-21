#pragma once
#include<string>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<iostream>
using namespace std;

void gotoRowCol(int rpos, int cpos);

struct position
{
	int cr = 0;
	int cc = 0;
};
struct position2
{
	int si = 0;
	int ei = 0;
	int ri = 0;
};
class Line
{
	friend class TextEditor;
	friend class Document;
	int Size;
	char* Cs;
public:
	Line()
	{
		Size = 0;
		Cs = new char[1]{};

	}
	Line(const Line& AL)
	{
		Cs = new char[AL.Size + 1]{};
		Size = AL.Size;
		for (int i = 0; i < AL.Size; i++)
		{
			Cs[i] = AL.Cs[i];
		}
	}
	void backspace(int i)
	{
		int si = 0;


		char* heap = new char[Size] {};
		for (int ci = 0; ci < Size; ci++)
		{
			if (ci != i)
				heap[si++] = Cs[ci];
			else
				continue;
		}
		delete[] Cs;
		Cs = heap;
		Size--;
	}
	void InsertCharAt(int i, char ch)
	{
		char* heap = new char[Size + 2]{};
		for (int si = 0; si < i; si++)
		{
			heap[si] = Cs[si];
		}
		heap[i] = ch;
		for (int si = i; si < Size; si++)
		{
			heap[si + 1] = Cs[si];
		}
		delete[] Cs;
		Cs = heap;
		Size++;
	}
	void ReplaceCharAt(int i, char ch)
	{
		char* heap = new char[Size + 2]{};
		for (int si = 0; si < i; si++)
		{
			heap[si] = Cs[si];
		}
		heap[i] = ch;
		for (int si = i; si < Size; si++)
		{
			heap[si + 1] = Cs[si + 1];
		}
		delete[] Cs;
		Cs = heap;
		Size++;
	}
	void Uppercase(int ci)
	{
		int size1 = ci;
		int size2 = ci;
		while (Cs[size1 - 1] != ' ' && size1 > 0)
			size1--;
		while (Cs[size2 + 1] != ' ' && size2 < Size - 1)
			size2++;
		for (int i = size1; i <= size2; i++)
		{
			if (Cs[i] >= 97 && Cs[i] <= 123)
				Cs[i] -= 32;
		}

	}
	void Lowercase(int ci)
	{
		int size1 = ci;
		int size2 = ci;
		while (Cs[size1 - 1] != ' ' && size1 > 0)
			size1--;
		while (Cs[size2 + 1] != ' ' && size2 < Size - 1)
			size2++;
		for (int i = size1; i <= size2; i++)
		{
			if (Cs[i] >= 65 && Cs[i] <= 90)
				Cs[i] += 32;
		}

	}
	void encode(ofstream& fout)
	{
		char ch;
		for (int i = 0; i < Size; i++)
		{
			ch = Cs[i] + 32;
			fout << ch;
		}
	}
	void decode(ofstream& fout)
	{
		char ch;
		for (int i = 0; i < Size; i++)
		{
			ch = Cs[i] - 32;
			fout << ch;
		}
	}

	~Line()
	{
		delete[] Cs;
		Cs = nullptr;
	}
};

class Document
{
	friend class TextEditor;
	friend class Line;
	Line* Ls;
	int NOLS;
	string password;
	string Dname;
	bool flag;
	
public:

	Document(string name)
	{

		NOLS = 0;
		Load(name);

	}
	Document()
	{
		NOLS = 0;
		Ls = nullptr;
	}
	void check_password(string password)
	{
		system("cls");
		string input;
		do
		{
			cout << "Enter password: ";
			cin >> input;
		} while (input != password);

		if (input == password)
		{
			cout << "Access granted" << endl;

		}
		system("pause");
		system("cls");
	}
	void Load(string name)
	{
		Dname = name;
		ifstream fin(Dname);
		fin >> NOLS;
		fin >> flag;
		if (flag == 1)
		{
			fin >> password;
			check_password(password);
		}

		fin.ignore();
		Ls = new Line[NOLS];
		int ri = 0, ci = 0;
		char ch;
		while (fin)
		{
			ch = fin.get();
			if (!fin)
				break;
			if (ch == '\n')
			{
				ri++;
				ci = 0;
			}
			else
			{
				InsertAcharacter(ri, ci, ch);
				ci++;
			}
		}
	}
	void Spacecheck(int i, int& k)
	{
		while ((Ls[i].Cs[k] == ' ' || Ls[i].Cs[k] == ',' || Ls[i].Cs[k] == '.' || Ls[i].Cs[k] == '?' || Ls[i].Cs[k] == '!' || Ls[i].Cs[k] == '\t') && k < Ls[i].Size)
		{
			k++;
		}
	}
	void Input(char*& data, int& size)
	{
		char input;
		do
		{
			input = _getch();
			if ((input == 13 || input == ' ') && size > 0)
				break;
			else if ((input == 13 || input == ' ') && size == 0)
			{
				cout << endl << "Enter atleast 1 character" << endl;
			}
			else
			{
				cout << input;
				heap(size, data, input);
			}
		} while (true);
	}
	void Inputsubstring(char*& data, int& size)
	{
		char input;
		do
		{
			input = _getch();
			if (input == 13 && size > 0)
				break;
			else if (input == 13 && size == 0)
			{
				cout << endl << "Enter atleast 1 word" << endl;
			}
			else
			{
				cout << input;
				heap(size, data, input);
			}
		} while (true);
	}
	void Inputsentence(char*& name, int& size)
	{
		char ch;
		name;
		int inputi = 0;
		size = 0;
		int count = 0;
		bool flag = true;
		cout << "Enter a sentence ";
		do
		{
			ch = _getch();
			if (ch == ' ' && inputi > 0)
				flag = false;
			if (ch == 13 && flag == false)
				break;
			else if (ch == 13 && flag == true)
			{
				cout << endl << "Enter a sentence ";
				inputi = 0;
				continue;
			}
			cout << ch;
			inputi++;
			heap(size, name, ch);
		} while (true);
	}
	void InsertAcharacter(int ri, int ci, int ch)
	{
		Ls[ri].InsertCharAt(ci, ch);
	}
	void InsertLine(int ri, int ci)
	{
		Line L1, L2;
		int L1i = 0, L2i = 0;
		for (int si = 0; si < ci; si++)
		{
			L1.InsertCharAt(L1i, Ls[ri].Cs[si]);
			L1i++;
		}
		for (int si = ci; si < Ls[ri].Size; si++)
		{
			L2.InsertCharAt(L2i, Ls[ri].Cs[si]);
			L2i++;
		}

		Line* heap = new Line[NOLS + 1];
		for (int i = 0, si = 0; i < NOLS; i++)
		{
			if (i != ri)
				/*heap[si++] = Ls[i];*/
			{
				for (int j = 0; j < Ls[i].Size; j++)
				{
					heap[si].InsertCharAt(j, Ls[i].Cs[j]);
				}
				si++;

			}
			else
			{
				for (int j = 0; j < L1.Size; j++)
				{
					heap[si].InsertCharAt(j, L1.Cs[j]);
				}
				/*heap[si] = L1;*/
				si++;
				for (int j = 0; j < L2.Size; j++)
				{
					heap[si].InsertCharAt(j, L2.Cs[j]);
				}
				/*heap[si] = L2;*/
				si++;
			}
		}

		delete[] Ls;
		Ls = heap;
		NOLS++;

	}
	void Merge(int ri, int ci)
	{
		Line L;
		for (int i = 0; i < Ls[ri].Size + Ls[ri - 1].Size; i++)
		{
			if (i < Ls[ri - 1].Size)
				L.InsertCharAt(i, Ls[ri - 1].Cs[i]);
			else
			{
				L.InsertCharAt(i, Ls[ri].Cs[ci]);
				ci++;
			}
		}

		Line* heap = new Line[NOLS - 1];
		for (int i = 0, j = 0, si = 0; i < NOLS - 1; i++)
		{
			if (i != ri - 1)
				/*heap[si++] = Ls[j++];*/
			{
				for (int x = 0; x < Ls[j].Size; x++)
				{
					heap[si].InsertCharAt(x, Ls[j].Cs[x]);
				}
				si++;
				j++;
			}
			else
			{
				for (int x = 0; x < L.Size; x++)
				{
					heap[si].InsertCharAt(x, L.Cs[x]);
				}
				si++;
				/*heap[si++] = L;*/
				j = j + 2;
			}
		}

		delete[] Ls;
		Ls = heap;
		NOLS--;

	}
	char casecheck(char ch)
	{
		if (ch >= 65 && ch <= 90)
			ch += 32;
		return ch;
	}
	void splitcheck(int i, int& li)
	{
		while (Ls[i].Cs[li] != ' ' && Ls[i].Cs[li] != ',' && Ls[i].Cs[li] != '.' && Ls[i].Cs[li] != '?' && Ls[i].Cs[li] != '!' && li < Ls[i].Size)
			li++;
	}
	void FindSubstringCaseSensitive(int& cr, int& cc)
	{
		system("cls");
		char* ch{};
		int ch_size = 0;
		cout << "Enter the sub string ";
		Inputsubstring(ch, ch_size);
		cout << endl;

		position* pos{};
		int count = 0, findcount = 0, li = 0;
		int pos_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				if (ch[0] == Ls[i].Cs[k])
				{
					for (int j = 0, si = k, li = i; j < ch_size; j++)
					{
						if (si == Ls[li].Size)
						{
							si = 0;
							li++;
							count++;
							continue;
						}
						if (ch[j] == Ls[i].Cs[si++])
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == ch_size)
					{
						cr = i;
						cc = k;
						pos_heap(pos, pos_size, cr, cc);
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						findcount++;
					}
				}
			}

		}

		if (findcount != 0)
			Find_next(pos, pos_size, cr, cc);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}

	}
	void FindSubstringInCaseSensitive(int& cr, int& cc)
	{
		system("cls");
		char* ch{};
		int ch_size = 0;
		cout << "Enter the sub string ";
		Inputsubstring(ch, ch_size);
		cout << endl;

		position* pos{};
		int count = 0, findcount = 0, li = 0;
		int pos_size = 0;
		int si = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				if (casecheck(ch[0]) == casecheck(Ls[i].Cs[k]))
				{
					for (int j = 0, si = k, li = i; j < ch_size; j++)
					{
						if (si == Ls[li].Size)
						{
							si = 0;
							li++;
							count++;
							continue;
						}
						if (casecheck(ch[j]) == casecheck(Ls[li].Cs[si++]))
						{
							count++;
						}
						else
							break;

					}
					if (count == ch_size)
					{
						cr = i;
						cc = k;
						pos_heap(pos, pos_size, cr, cc);
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						findcount++;
					}
				}
			}

		}

		if (findcount != 0)
			Find_next(pos, pos_size, cr, cc);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}

	}
	void FindwordCaseSensitive(int& cr, int& cc)
	{

		system("cls");
		char* ch{};
		int ch_size = 0;
		cout << "Enter the word ";
		Input(ch, ch_size);
		cout << endl;

		position* pos{};
		int count = 0, findcount = 0, li = 0, word_size;
		int pos_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (ch[0] == Ls[i].Cs[k])
				{

					li = k;

					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (ch[j] == Ls[i].Cs[si++])
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == word_size && count == ch_size)
					{
						cr = i;
						cc = k;
						pos_heap(pos, pos_size, cr, cc);
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						findcount++;
					}
				}
				splitcheck(i, k);
			}

		}
		cout << "There are total " << findcount << " " << ch << " in file" << endl;
		if (findcount != 0)
			Find_next(pos, pos_size, cr, cc);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}
	}
	void FindwordInCaseSensitive(int& cr, int& cc)
	{
		system("cls");
		char* ch{};
		int ch_size = 0;
		cout << "Enter the word ";
		Input(ch, ch_size);
		cout << endl;
		position* pos{};
		int count = 0, findcount = 0, li = 0, word_size;
		int pos_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (casecheck(ch[0]) == casecheck(Ls[i].Cs[k]))
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (casecheck(ch[j]) == casecheck(Ls[i].Cs[si++]))
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == word_size && count == ch_size)
					{
						cr = i;
						cc = k;
						pos_heap(pos, pos_size, cr, cc);
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						findcount++;
					}
				}
				while (Ls[i].Cs[k] != ' ' && k < Ls[i].Size)
					k++;
			}

		}
		cout << "There are total " << findcount << " " << ch << " in file" << endl;

		if (findcount != 0)
			Find_next(pos, pos_size, cr, cc);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}


	}
	void FindAsentence(int& cr, int& cc)
	{
		system("cls");
		char* name{};
		int size = 0;
		Inputsentence(name, size);
		cout << endl;

		position* pos{};
		int findcount = 0, count = 0, pos_size = 0;
		for (int i = 0; i < NOLS; i++)
		{

			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (name[0] == Ls[i].Cs[k])
				{
					for (int j = 0, si = k, li = i; j < size; j++)
					{
						if (si == Ls[li].Size)
						{
							si = 0;
							li++;
							count++;
							continue;
						}
						if (name[j] == Ls[li].Cs[si++])
							count++;
						else
							break;
					}
					if (count == size)
					{
						cr = i;
						cc = k;
						pos_heap(pos, pos_size, cr, cc);
						cout << "Sentence is located at line " << i + 1 << endl;
						findcount++;
					}
				}

			}

		}

		if (findcount != 0)
			Find_next(pos, pos_size, cr, cc);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}

	}
	void Replace_check(int replace_size, int word_size, int li, int si, char* replace)
	{
		for (int i = 0, j = li; i < replace_size || i < word_size; i++)
		{
			if (i >= replace_size)
				Ls[si].backspace(j);
			else if (i >= word_size)
				Ls[si].InsertCharAt(j++, replace[i]);
			else
				Ls[si].ReplaceCharAt(j++, replace[i]);
		}
	}
	void prefix_check(int replace_size, int li, int si, char* replace, int& cr)
	{
		cr = 0;
		for (int i = replace_size - 1, j = li; i >= 0; i--)
		{
			Ls[si].InsertCharAt(j, replace[i]);
			cr++;
		}
	}
	void postfix_check(int replace_size, int si, char* replace, int& cr, int ei)
	{
		cr = 0;
		for (int i = 0, j = ei; i < replace_size; i++)
		{
			Ls[si].InsertCharAt(j++, replace[i]);
			cr++;
		}

	}
	void Replaceword(int& cr, int& cc)
	{
		system("cls");
		char* ch{}; char* replace{};
		int ch_size = 0, replace_size = 0;
		cout << "Enter the word to find ";
		Input(ch, ch_size);
		cout << endl;

		cout << "Enter the word to replace ";
		Input(replace, replace_size);
		cout << endl;

		position* pos{};
		position* size{};

		int pos_size = 0, findcount = 0, sizearray_size = 0;
		int count = 0;
		int li = 0, si = 0;
		int word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;

				if (casecheck(ch[0]) == casecheck(Ls[i].Cs[k]))
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (casecheck(ch[j]) == casecheck(Ls[i].Cs[si++]))
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == word_size && count == ch_size)
					{
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;

						cr = i;
						cc = k;
						pos_heap(pos, pos_size, cr, cc);
						pos_heap(size, sizearray_size, word_size, cc);
						findcount++;
					}
				}
				while (Ls[i].Cs[k] != ' ' && k < Ls[i].Size)
					k++;
			}

		}
		cout << "There are total " << findcount << " " << ch << " in file" << endl;
		if (findcount != 0)
			Replace_next(pos, pos_size, cr, cc, size, sizearray_size, replace, replace_size);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}

	}
	void Replaceeveryword(int& cr, int& cc)
	{
		system("cls");
		char* ch{}; char* replace{};
		int ch_size = 0, replace_size = 0;
		cout << "Enter the word to find ";
		Input(ch, ch_size);
		cout << endl;

		cout << "Enter the word to replace ";
		Input(replace, replace_size);
		cout << endl;

		int count = 0;
		int li = 0, si = 0;
		int word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (casecheck(ch[0]) == casecheck(Ls[i].Cs[k]))
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (casecheck(ch[j]) == casecheck(Ls[i].Cs[si++]))
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == word_size && count == ch_size)
					{
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;

						cr = i;
						cc = k;
						Replace_check(replace_size, word_size, li, si, replace);
					}
				}
				while (Ls[i].Cs[k] != ' ' && k < Ls[i].Size)
					k++;
			}

		}

		system("pause");
		system("cls");
	}
	void Addprefix(int& cr, int& cc)
	{
		//incase sensitive
		system("cls");
		char* ch{}; char* replace{};
		int ch_size = 0, replace_size = 0;
		cout << "Enter the word to find ";
		Input(ch, ch_size);
		cout << endl;

		cout << "Enter the word to add as prefix ";
		Input(replace, replace_size);
		cout << endl;

		int count = 0;
		int li = 0, si = 0;
		int word_size = 0;

		position* pos{};
		int findcount = 0, pos_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (ch[0] == Ls[i].Cs[k])
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (ch[j] == Ls[i].Cs[si++])
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == word_size && count == ch_size)
					{

						li = k;
						si = i;

						pos_heap(pos, pos_size, i, k);
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						findcount++;

					}
				}
				splitcheck(i, k);
			}

		}

		cout << "There are total " << findcount << " " << ch << " in file" << endl;
		if (findcount != 0)
			Replace_nextprefix(pos, pos_size, cr, cc, replace, replace_size);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}
	}
	void Addpostfix(int& cr, int& cc)
	{
		//incase sensitive
		system("cls");
		char* ch{}; char* replace{};
		int ch_size = 0, replace_size = 0;
		cout << "Enter the word to find ";
		Input(ch, ch_size);
		cout << endl;

		cout << "Enter the word to add as postfix ";
		Input(replace, replace_size);
		cout << endl;

		position2* pos{};

		int findcount = 0, pos_size = 0;
		int count = 0;
		int li = 0, si = 0, ei = 0;
		int word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (ch[0] == Ls[i].Cs[k])
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (ch[j] == Ls[i].Cs[si++])
						{
							count++;
						}
						else
						{
							break;
						}
						ei = si;
					}
					if (count == word_size && count == ch_size)
					{
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;

						pos_heap2(pos, pos_size, li, ei, i);
						findcount++;

					}
				}
				splitcheck(i, k);
			}

		}

		cout << "There are total " << findcount << " " << ch << " in file" << endl;
		if (findcount != 0)
			Replace_nextpostfix(pos, pos_size, cr, cc, replace, replace_size);
		else
		{
			system("pause");
			system("cls");
			PrintDocument();
		}

	}
	void Average()
	{
		system("cls");

		float count = 0;
		int li = 0;
		float word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				Spacecheck(i, k);
				while ((Ls[i].Cs[k] != ' ' && Ls[i].Cs[k] != ',' && Ls[i].Cs[k] != '.' && Ls[i].Cs[k] != '?' && Ls[i].Cs[k] != '!') && k < Ls[i].Size)
				{
					k++;
					count++;
				}
				word_size++;
				splitcheck(i, k);
			}

		}
		cout << "Average word length is " << float(count / word_size) << endl;
		system("pause");
		system("cls");

	}
	void Substringcount()
	{

		system("cls");
		char* ch{};
		int ch_size = 0;
		cout << "Enter the substring : " << endl;
		Inputsubstring(ch, ch_size);
		cout << endl;

		int si = 0;
		int count = 0, subcount = 0;;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				Spacecheck(i, k);
				count = 0;
				if (casecheck(ch[0]) == casecheck(Ls[i].Cs[k]))
				{
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (casecheck(ch[j]) == casecheck(Ls[i].Cs[si++]))
						{
							count++;
						}
						else
							break;

					}
					if (count == ch_size)
					{

						cout << "substring exists on index " << k << " and line " << i + 1 << endl;
						subcount++;

					}
				}
			}

		}

		cout << "Substring count is " << subcount << endl;
		system("pause");
		system("cls");
	}
	bool Specialcharacter_check(char ch)
	{
		if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) || ch == ' ')
			return false;
		else
			return true;

	}
	void Specialcharacter_count()
	{
		system("cls");
		int count = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int j = 0; j < Ls[i].Size; j++)
			{
				if (Specialcharacter_check(Ls[i].Cs[j]))
					count++;
			}
		}

		cout << "Total number of special characters are: " << count << endl;
		system("pause");
		system("cls");
	}
	void Number_of_sentences()
	{
		system("cls");
		int count = 0, paracount = 0;

		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				if (k == 0 && (Ls[i].Cs[k] == ' ' || k == '\t'))
					paracount++;
				if (Ls[i].Cs[k] == '.' || Ls[i].Cs[k] == '!' || Ls[i].Cs[k] == '?')
					count++;
			}
		}

		cout << "Total sentences : " << count << endl;
		cout << "Total paragraphs: " << paracount << endl;

		system("pause");
		system("cls");
	}
	void LargestWord_Length(int& cr, int& cc)
	{
		system("cls");

		int count = 0, max = 0, max_index = 0;
		int li, ln = 0;
		int word_size;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				Spacecheck(i, k);
				count = 0;
				li = k;
				splitcheck(i, li);
				word_size = li - k;
				if (word_size > max)
				{
					cr = i;
					cc = k;
					max = word_size;
					max_index = k;
					ln = i;
				}
				splitcheck(i, k);
			}
		}

		cout << "max word size is " << max << " at index " << max_index << " at line " << ln + 1 << endl;
		system("pause");
		system("cls");
	}
	void SmallestWord_Length(int& cr, int& cc)
	{
		system("cls");

		int count = 0, min = 2, min_index = 0;
		int li, ln = 0;
		int word_size;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				Spacecheck(i, k);
				count = 0;
				li = k;
				splitcheck(i, li);
				word_size = li - k;
				if (word_size < min)
				{
					cr = i;
					cc = k;
					min = word_size;
					min_index = k;
					ln = i;
				}
				splitcheck(i, k);
			}
		}

		cout << "min word size is " << min << " at index " << min_index << " at line " << ln + 1 << endl;
		system("pause");
	}
	void Find_next(position* data, int size, int& cr, int& cc)
	{
		char input;
		cout << "Press F to find next or E to exit" << endl;
		for (int i = 0; i < size; i)
		{
			input = _getch();

			if (input == 'F' || input == 'f')
			{
				cr = data[i].cr;
				cc = data[i].cc;
				system("cls");
				PrintDocument();
				gotoRowCol(data[i].cr, data[i].cc);
				i++;

			}
			else if (input == 'E' || input == 'e')
			{
				PrintDocument();
				break;
			}

		}
	}
	void Replace_next(position* data, int size, int& cr, int& cc, position* data2, int sizearray_size, char* replace, int replace_size)
	{
		char input, input2;
		cout << "Press F to find next or E to exit" << endl;
		for (int i = 0; i < size; i)
		{
			input = _getch();

		jump:
			if (input == 'F' || input == 'f')
			{
				cr = data[i].cr;
				cc = data[i].cc;
				system("cls");
				PrintDocument();
				gotoRowCol(data[i].cr, data[i].cc);
				input2 = _getch();
				if (input2 == 'r' || input2 == 'R')
				{
					Replace_check(replace_size, data2[i].cr, cc, cr, replace);
					system("cls");
					PrintDocument();
				}
				else
				{
					i++;
					goto jump;
				}

				i++;

			}
			else if (input == 'E' || input == 'e')
			{
				PrintDocument();
				break;
			}

		}
	}
	void Replace_nextprefix(position* data, int size, int& cr, int& cc, char* replace, int replace_size)
	{
		char input, input2;
		int si = 0, line = 0;
		cout << "Press F to find next or E to exit" << endl;
		for (int i = 0; i < size; i)
		{
			input = _getch();

		jump:
			if (input == 'F' || input == 'f')
			{
				cr = data[i].cr;
				line = data[i].cr;
				cc = data[i].cc;
				system("cls");
				PrintDocument();
				gotoRowCol(data[i].cr, data[i].cc + si);
				input2 = _getch();
				if (input2 == 'r' || input2 == 'R')
				{
					prefix_check(replace_size, cc + si, cr, replace, si);
					system("cls");
					PrintDocument();
				}
				else if (input == 'f' || input == 'F')
				{
					input = 'f';
					if (i < size - 1)
						i++;
					else
						break;
					goto jump;
				}
				else if (input2 == 'e' || input2 == 'e')
					break;

				i++;

			}
			else if (input == 'E' || input == 'e')
			{
				PrintDocument();
				break;
			}
			if (line != data[i].cr)
			{
				si = 0;
				line = data[i].cr;
			}
		}
	}
	void Replace_nextpostfix(position2* data, int size, int& cr, int& cc, char* replace, int replace_size)
	{
		char input, input2;
		int si = 0, line = 0;
		cout << "Press F to find next or E to exit" << endl;
		for (int i = 0; i < size; i)
		{
			input = _getch();

		jump:
			if (input == 'F' || input == 'f')
			{
				cr = data[i].ri;
				line = data[i].ri;
				cc = data[i].si;
				system("cls");
				PrintDocument();
				gotoRowCol(data[i].ri, data[i].si + si);
				input2 = _getch();
				if (input2 == 'r' || input2 == 'R')
				{
					postfix_check(replace_size, cr, replace, si, data[i].ei + si);
					system("cls");
					PrintDocument();
				}
				else if (input2 == 'e' || input2 == 'e')
					break;
				else
				{
					if (i < size - 1)
						i++;
					else
						break;
					goto jump;
				}

				i++;

			}
			else if (input == 'E' || input == 'e')
			{
				PrintDocument();
				break;
			}
			if (line != data[i].ri)
			{
				si = 0;
				line = data[i].ri;
			}
		}
	}
	bool check_dupliate(int* data, int data_size, int check_index)
	{
		for (int i = 0; i < data_size; i++)
		{
			if (check_index == data[i])
				return false;
		}
		return true;
	}
	void word_check(int& count, int word1_si, int word1_ei, int word2_si, int word2_ei, int ri, int word2_ri, position2*& data, int& data_size)
	{

		int* DA{};
		int check = 0, DA_size = 0;
		bool flag = false;

		for (int i = word2_si; i < word2_ei; i++)
		{
			flag = false;
			for (int j = word1_si; j < word1_ei; j++)
			{
				if (Ls[word2_ri].Cs[i] == Ls[ri].Cs[j])
				{


					if (check > 0)
					{
						if (check_dupliate(DA, DA_size, j))
						{
							flag = true;
							check++;
							heapint(DA_size, DA, j);
							break;
						}
						else
							continue;
					}
					else
					{
						heapint(DA_size, DA, j);
						flag = true;
						check++;
						break;
					}



				}
			}
			if (flag == false)
				break;
		}

		if (check == (word2_ei - word2_si) && flag == true)
		{
			pos_heap2(data, data_size, word2_si, word2_ei, word2_ri);
			count++;

		}

	}
	int Scramble_check(int word1_si, int word1_ei, int ri, position2*& pos, int& pos_size)
	{
		pos;
		pos_size = 0;
		int li = 0;
		int count = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int j = 0; j < Ls[i].Size; j++)
			{
				Spacecheck(i, j);
				li = j;
				splitcheck(i, li);
				int wordsize_2 = li - j;
				word_check(count, word1_si, word1_ei, j, li, ri, i, pos, pos_size);

				splitcheck(i, li);
				j = li;
			}
		}
		return count;

	}
	void Scramble(int& cr, int& cc)
	{
		system("cls");
		position2* pos{};
		position2* pos2{};
		int pos_size = 0;
		int pos2_size = 0;

		int maxcount = 0, count = 0, maxsi = 0, maxei = 0, maxri = 0;
		int li = 0;
		int word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int j = 0; j < Ls[i].Size; j++)
			{
				Spacecheck(i, j);;
				li = j;

				splitcheck(i, li);
				word_size = li - j;
				count = Scramble_check(j, li, i, pos, pos_size);
				if (count > maxcount)
				{
					cr = i, cc = j;
					maxcount = count;
					maxri = i;
					maxsi = j;
					maxei = li;
					pos2 = new position2[pos_size]{};
					for (int k = 0; k < pos_size; k++)
					{
						pos2[k].ri = pos[k].ri;
						pos2[k].si = pos[k].si;
						pos2[k].ei = pos[k].ei;
					}
					pos2_size = pos_size;
				}
				j = li;

			}
		}

		cout << "word containing most number of other words is ";
		for (int si = maxsi; si < maxei; si++)
		{
			cout << Ls[maxri].Cs[si];
		}
		cout << " at index " << maxsi << " with total words " << maxcount << endl;

		cout << "words are: " << endl;
		for (int i = 0; i < pos2_size; i++)
		{
			for (int j = pos2[i].si; j < pos2[i].ei; j++)
			{
				cout << Ls[pos2[i].ri].Cs[j];
			}
			cout << endl;
		}

		system("pause");
		system("cls");
	}
	void choice(int ci, int& cr, int& cc)
	{
		cout << "1. Replace next all" << endl
			<< "2. Replace previous all" << endl
			<< "3. Find and replace" << endl;

		int choice;
		cout << "Enter task number: ";
		cin >> choice;
		if (choice == 1)
			replace_nextall(ci, cr, cc);
		else if (choice == 2)
			replace_previousall(ci, cr, cc);
		else if (choice == 3)
			find_replace(cc, cr, cc);

	}
	int word_size(int ci, int cr, int& size1, int& size2)
	{
		int given_size;
		size1 = ci;
		size2 = ci + 1;
		int x = 0, y = 0;
		while (Ls[cr].Cs[size1] != ' ' && Ls[cr].Cs[size1] != ',' && Ls[cr].Cs[size1] != '!' && Ls[cr].Cs[size1] != '?' && size1 >= 0)
		{
			x++;
			size1--;
		}
		while (Ls[cr].Cs[size2] != ' ' && Ls[cr].Cs[size2] != ',' && Ls[cr].Cs[size2] != '!' && Ls[cr].Cs[size2] != '?' && size2 < Ls[cr].Size - 1)
		{
			y++; size2++;
		}
		given_size = y + x;
		return given_size;
	}
	void make_string(char*& data, int& data_size, int size1, int size2, int cr)
	{
		for (int i = size1 + 1; i < size2; i++)
		{
			heap(data_size, data, Ls[cr].Cs[i]);
		}
	}
	void find_replace(int& ci, int& cr, int& cc)
	{
		int size1, size2;
		int given_size = word_size(ci, cr, size1, size2);

		char* replace{};
		int replace_size = 0;
		cout << "Enter the word to replace ";
		Input(replace, replace_size);
		cout << endl;

		position2* pos{};

		int pos_size = 0, findcount = 0, count = 0, li = 0, si = 0, word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (Ls[cr].Cs[size1 + 1] == Ls[i].Cs[k])
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = size1 + 1, si = k; j < size2; j++)
					{
						if (Ls[cr].Cs[j] == Ls[i].Cs[si++])
						{
							count++;
						}
						else
						{
							break;
						}
					}
					if (count == word_size && count == given_size)
					{
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;


						pos_heap2(pos, pos_size, k, word_size, i);
						findcount++;
						if (size1 + 1 == li && i == cr)
						{
							ci = pos_size;
						}
					}
				}
				splitcheck(i, k);
			}

		}

		find_replacenext(pos, pos_size, cr, cc, replace, replace_size, ci);
	}
	void replace_nextall(int ci, int& cr, int& cc)
	{
		system("cls");
		int size1 = 0, size2 = 0;
		int given_size = word_size(ci, cr, size1, size2);
		char* replace{};
		char* input{};
		int replace_size = 0, ch_size = 0;
		make_string(input, ch_size, size1, size2, cr);
		cout << endl;

		cout << "Enter the word to replace ";
		Input(replace, replace_size);
		cout << endl;

		int count = 0, li = 0, si = 0, word_size = 0, k;
		for (int i = cr; i < NOLS; i++)
		{
			k = (i > cr) ? 0 : size2;
			for (k; k < Ls[i].Size; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (input[0] == Ls[i].Cs[k])
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (input[j] == Ls[i].Cs[si++])
							count++;
						else
							break;
					}
					if (count == word_size && count == ch_size)
					{
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;

						Replace_check(replace_size, word_size, li, si, replace);
					}
				}
				splitcheck(i, k);
			}

		}
		system("pause");
		system("cls");
	}
	void replace_previousall(int ci, int& cr, int& cc)
	{
		system("cls");
		int size1 = 0, size2 = 0;
		int given_size = word_size(ci, cr, size1, size2);
		char* replace{};
		char* input{};
		int replace_size = 0, ch_size = 0;
		make_string(input, ch_size, size1, size2, cr);
		cout << endl;

		cout << "Enter the word to replace ";
		Input(replace, replace_size);
		cout << endl;

		int count = 0, li = 0, si = 0, word_size = 0, temp;
		for (int i = 0; i < cr + 1; i++)
		{
			temp = (i == cr) ? size1 : Ls[i].Size;
			for (int k = 0; k < temp; k++)
			{
				count = 0;
				Spacecheck(i, k);
				if (input[0] == Ls[i].Cs[k])
				{
					li = k;
					splitcheck(i, li);
					word_size = li - k;
					for (int j = 0, si = k; j < ch_size; j++)
					{
						if (input[j] == Ls[i].Cs[si++])
							count++;
						else
							break;
					}
					if (count == word_size && count == ch_size)
					{
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;

						Replace_check(replace_size, word_size, li, si, replace);
					}
				}
				splitcheck(i, k);
			}

		}

		system("pause");
		system("cls");
	}
	void find_replacenext(position2* data, int size, int& cr, int& cc, char* replace, int replace_size, int given_index)
	{
		if (given_index != 0)
			given_index--;

		char input, input2;
		cout << "Press F to find next or E to exit" << endl;
		for (int i = given_index; i < size; i)
		{
			input = _getch();

		jump:
			if (input == 'F' || input == 'f')
			{
				cr = data[i].ri;
				cc = data[i].si;
				system("cls");
				PrintDocument();
				gotoRowCol(data[i].ri, data[i].si);
				input2 = _getch();
				if (input2 == 'r' || input2 == 'R')
				{
					Replace_check(replace_size, data[i].ei, cc, cr, replace);
					system("cls");
					PrintDocument();
				}
				else if (input2 == 'F' || input2 == 'f')
				{
					input = 'f';
					if (i < size - 1)
						i++;
					goto jump;
				}
				else if (input2 == 'P' || input2 == 'p')
				{
					input = 'p';
					i--;

					goto jump;
				}
				else  if (input == 'E' || input == 'e')
				{
					PrintDocument();
					break;
				}

				i++;

			}

			else if (input == 'P' || input == 'p')
			{
				cr = data[i].ri;
				cc = data[i].si;
				system("cls");
				PrintDocument();
				gotoRowCol(data[i].ri, data[i].si);
				input2 = _getch();
				if (input2 == 'r' || input2 == 'R')
				{
					Replace_check(replace_size, data[i].ei, cc, cr, replace);
					system("cls");
					PrintDocument();
				}
				else if (input2 == 'f' || input2 == 'F')
				{
					input = 'f';
					i++;
					goto jump;
				}
				else if (input2 == 'P' || input2 == 'p')
				{
					if (i > 0)
						i--;
					goto jump;
				}
				else  if (input == 'E' || input == 'e')
				{
					PrintDocument();
					break;
				}


				i--;

			}
			else if (input == 'E' || input == 'e')
			{
				PrintDocument();
				break;
			}

		}
	}
	float wordlength(int si, int& Now, int size)
	{
		system("cls");

		float count = 0, avg = 0;
		int word_size = 0;
		for (int i = si; i < size; i++)
		{

			for (int k = 0; k < Ls[i].Size; k++)
			{

				Spacecheck(i, k);
				while ((Ls[i].Cs[k] != ' ' && Ls[i].Cs[k] != ',' && Ls[i].Cs[k] != '.' && Ls[i].Cs[k] != '?' && Ls[i].Cs[k] != '!') && k < Ls[i].Size)
				{
					k++;
					count++;
				}
				word_size++;
				splitcheck(i, k);

			}
		}
		Now = word_size;
		avg = count / word_size;
		return avg;
	}
	void para_length()
	{
		system("cls");
		int count = 0, max = 0, Now, maxNow = 0, si = 0;
		float word_length = 0, maxword_length = 0;
		for (int i = 0; i < NOLS - 1; i++)
		{
			count = 0;
			if ((Ls[i].Cs[0] == ' ' || Ls[i].Cs[0] == '\t') && i < NOLS - 1)
			{
				si = i;
				while (Ls[i + 1].Cs[0] != ' ' && Ls[i + 1].Cs[0] != '\t')
				{
					count++;
					if (i < NOLS - 2)
						i++;
					else
					{
						i++;
						count++;
						break;
					}
				}
				word_length = wordlength(si, Now, i + 1);

				if (count > max)
				{
					maxword_length = word_length;
					max = count;
					maxNow = Now;
				}
			}
		}

		cout << "Max paragraph length is " << max << " with avg word length " << maxword_length << " and " << maxNow << " words " << endl;
		system("pause");
		system("cls");
	}
	void PrintAddress()
	{
		cout << NOLS << "( " << &NOLS << " )" << endl;
		cout << Ls << "( " << &Ls << ") -->" << endl;
		for (int i = 0; i < NOLS; i++)
		{
			cout << &Ls[i].Size << "( " << Ls[i].Size << "): " << endl;
			cout << (void*)&Ls[i].Cs << "( " << Ls[i].Cs << ") --->" << endl;
			for (int j = 0; j < Ls[i].Size; j++)
			{
				cout << Ls[i].Cs[j] << " (" << (void*)&Ls[i].Cs[j] << ")  ";
			}
			cout << endl;
		}
	}
	void PrintDocument()
	{
		gotoRowCol(0, 0);
		for (int i = 0; i < NOLS; i++)
		{
			cout << Ls[i].Cs << endl;
		}
	}
	void WriteDocument()
	{
		gotoRowCol(0, 0);
		ofstream fout(Dname);
		fout << NOLS << endl;
		fout << flag;
		if (flag == 1)
		{
			fout << " " << password << endl;
		}
		for (int i = 0; i < NOLS; i++)
		{
			fout << Ls[i].Cs << endl;
			cout << Ls[i].Cs << endl;
		}
	}
	void heap(int& size, char*& data, char T)
	{
		char* heap = new char[size + 2]{};
		for (int i = 0; i < size; i++)
		{
			heap[i] = data[i];
		}
		heap[size] = T;
		delete[] data;
		data = heap;
		size++;

	}
	void heapint(int& size, int*& data, int T)
	{
		int* heap = new int[size + 1]{};
		for (int i = 0; i < size; i++)
		{
			heap[i] = data[i];
		}
		heap[size] = T;
		delete[] data;
		data = heap;
		size++;

	}
	void pos_heap(position*& data, int& size, int ri, int ci)
	{
		position* heap = new position[size + 1]{};
		for (int i = 0; i < size; i++)
		{
			heap[i].cc = data[i].cc;
			heap[i].cr = data[i].cr;
		}
		heap[size].cc = ci;
		heap[size].cr = ri;
		delete[] data;
		data = heap;
		size++;

	}
	void pos_heap2(position2*& data, int& size, int si, int ei, int ri)
	{
		position2* heap = new position2[size + 1]{};
		for (int i = 0; i < size; i++)
		{
			heap[i].si = data[i].si;
			heap[i].ei = data[i].ei;
			heap[i].ri = data[i].ri;
		}
		heap[size].si = si;
		heap[size].ei = ei;
		heap[size].ri = ri;
		delete[] data;
		data = heap;
		size++;

	}
	void Back(int ri, int i)
	{
		Ls[ri].backspace(i - 1);
	}
	void copy_Document(Document*& newfile, Document*& heap)
	{
		for (int i = 0; i < NOLS; i++)
		{
			for (int j = 0; j < Ls[i].Size; j++)
			{
				newfile->InsertAcharacter(i, j, Ls[i].Cs[j]);
			}

		}

		for (int i = 0, k = NOLS; i < heap->NOLS; i++, k++)
		{
			for (int j = 0; j < heap->Ls[i].Size; j++)
			{
				newfile->InsertAcharacter(k, j, heap->Ls[i].Cs[j]);
			}
		}
	}
	void merge_files()
	{
		system("cls");
		string name;
		cout << "Enter the file name ";
		cin >> name;

		Document* heap = new Document(name);

		Document* file = new Document;
		file->NOLS = NOLS + heap->NOLS;
		file->Ls = new Line[file->NOLS]{};

		copy_Document(file, heap);

		delete[] Ls;
		Ls = file->Ls;
		NOLS = file->NOLS;
	}
	void Encode_file(bool& check)
	{
		system("cls");
		ofstream fout("ProcessedFileEcoded.txt");
		char ch;
		cout << "E for Encode or D for Decode: ";
		cin >> ch;
		if (ch == 'e' || ch == 'E')
		{
			for (int i = 0; i < NOLS; i++)
			{
				Ls[i].encode(fout);
				fout << endl;
			}
			check = true;
		}
		else if ((ch == 'd' || ch == 'D') && check)
		{
			for (int i = 0; i < NOLS; i++)
			{
				Ls[i].decode(fout);
				fout << endl;
			}
		}
		else
		{
			cout << "File is not encoded" << endl;
			system("pause");
		}
		system("cls");


	}
};

class TextEditor
{
	int cr = 0, cc = 0;
	int NOD = 1;
	Document** ADocument;

public:
	TextEditor(string name);
	void Editing();
	void Add_Document();
	static void menu();
	void Print_Documents();
};

