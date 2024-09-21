//Text-Editor.h
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
};

class Document
{
	friend class TextEditor;
	friend class Line;
	Line* Ls;
	int NOLS;
	string Dname;
public:

	Document(string name)
	{

		NOLS = 0;
		Load(name);

	}
	void Load(string name)
	{
		Dname = name;
		ifstream fin(Dname);
		fin >> NOLS;
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
				heap[si++] = Ls[i];
			else
			{
				heap[si] = L1;
				si++;
				heap[si] = L2;
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
				heap[si++] = Ls[j++];
			else
			{
				heap[si++] = L;
				j = j + 2;
			}
		}

		delete[] Ls;
		Ls = heap;
		NOLS--;

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
	char casecheck(char ch)
	{
		if (ch >= 65 && ch <= 90)
			ch += 32;
		return ch;
	}
	void splitcheck(int i, int& li)
	{
		while (Ls[i].Cs[li] != ' ' && Ls[i].Cs[li] != ',' && Ls[i].Cs[li] != '.' && Ls[i].Cs[li] != '!' && li < Ls[i].Size)
			li++;
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
		char input;
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
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;

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
						cout << "word exists on index " << k << " and line " << i + 1 << endl;
						li = k;
						si = i;

						cr = i;
						cc = k;
						for (int i = replace_size - 1, j = li; i >= 0; i--)
						{
							Ls[si].InsertCharAt(j, replace[i]);
						}
						system("pause");
						system("cls");
						return;
					}
				}
				while (Ls[i].Cs[k] != ' ' && k < Ls[i].Size)
					k++;
			}

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

		int count = 0;
		int li = 0, si = 0, ei = 0;
		int word_size = 0;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;

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

						cr = i;
						cc = li;
						for (int i = 0, j = ei; i < replace_size; i++)
						{
							Ls[si].InsertCharAt(j++, replace[i]);
						}
						system("pause");
						system("cls");
						return;
					}
				}
				splitcheck(i, k);
			}

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
				li = k;
				while (Ls[i].Cs[k] != ' ' && k < Ls[i].Size)
				{
					k++;
					count++;
				}
				word_size++;

				while (Ls[i].Cs[li] == ' ' && li < Ls[i].Size)
					li++;

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

						cout << "largest word  exists on index " << k << " and line " << i + 1 << endl;
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
				if (k == 0 && Ls[i].Cs[k] == ' ')
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

		int count = 0, min = 0, min_index = 0;
		int li, ln = 0;
		int word_size;
		for (int i = 0; i < NOLS; i++)
		{
			for (int k = 0; k < Ls[i].Size; k++)
			{
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
	void FindAsentence(int& cr, int& cc)
	{
		system("cls");
		char ch;
		char* name{};
		int size = 0;
		int count = 0;
		bool flag = true;
		cout << "Enter a sentence ";
		do
		{
			ch = _getch();
			if (ch == ' ')
				flag = false;
			if (ch == 13 && flag == false)
				break;
			else if (ch == 13 && flag == true)
			{
				cout << endl << "Enter a sentence";
				continue;
			}
			cout << ch;
			heap(size, name, ch);
		} while (true);

		position* pos{};
		int findcount = 0;
		int pos_size = 0;
		for (int i = 0; i < NOLS; i++)
		{

			for (int k = 0; k < Ls[i].Size; k++)
			{
				count = 0;
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
						cout << endl << "Sentence is located at line " << i + 1 << endl;
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
	void PrintDocument()
	{
		gotoRowCol(0, 0);
		ofstream fout(Dname);
		fout << NOLS << endl;
		for (int i = 0; i < NOLS; i++)
		{
			fout << Ls[i].Cs << endl;
			cout << Ls[i].Cs << endl;
		}
	}
	void Back(int ri, int i)
	{
		Ls[ri].backspace(i - 1);
	}
};

class TextEditor
{
	int cr = 0, cc = 0;
	Document* ADocument;

public:
	TextEditor(string name);
	void Editing();
	static void menu();

};







//Text-editor.cpp


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
		<< "Press Control O to open menu at anytime" << endl
		<< "Press Control g to exit" << endl;

}
TextEditor::TextEditor(string name)
{
	ADocument = new Document(name);
	ADocument->PrintDocument();
}

void TextEditor::Editing()
{
	int d;
	char ch;
	char input;
	cr = 0, cc = 0;
	bool IsFirst = true;
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
					if (ADocument->Ls[cr].Size < cc)
						cc = ADocument->Ls[cr].Size;
				}
				else if (d == 80)
				{
					if (ADocument->NOLS - 1 != cr)
						cr++;
					if (ADocument->Ls[cr].Size < cc)
						cc = ADocument->Ls[cr].Size;
				}
				else if (d == 77)
				{
					if (cc != ADocument->Ls[cr].Size)
						cc++;
					if (cc == ADocument->Ls[cr].Size && ADocument->NOLS - 1 != cr)
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
						cc = ADocument->Ls[cr].Size;
					}
				}
			}
			else if (d == 13)
			{

				ADocument->InsertLine(cr, cc);
				system("cls");
				ADocument->PrintDocument();
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

					ADocument->Back(cr, cc);
					system("cls");
					ADocument->PrintDocument();
					cc--;
				}
				else if (cc < 1 && cr >= 1)
				{
					ADocument->Merge(cr, cc);
					system("cls");
					ADocument->PrintDocument();
					cc = ADocument->Ls[cr - 1].Size;
					cr--;
				}


			}


			else if (d == 7)
			{
				return;
			}
			else if (d == 21)
			{
				ADocument->Ls[cr].Uppercase(cc);
				ADocument->PrintDocument();
			}
			else if (d == 12)
			{
				ADocument->Ls[cr].Lowercase(cc);
				ADocument->PrintDocument();
			}
			else if (d == 23)
			{
				system("cls");
				cout << "Do you want to find case sensitive or insensitive?(C or I)" << endl;
				cin >> ch;
				if (ch == 'c' || ch == 'C')
					ADocument->FindwordCaseSensitive(cr, cc);
				else if (ch == 'i' || ch == 'I')
					ADocument->FindwordInCaseSensitive(cr, cc);

			}
			else if (d == 19)
			{
				ADocument->FindAsentence(cr, cc);
				ADocument->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 5)
			{
				system("cls");
				cout << "Do you want to find case sensitive or insensitive?(C or I)" << endl;
				cin >> ch;
				if (ch == 'c' || ch == 'C')
					ADocument->FindSubstringCaseSensitive(cr, cc);
				else if (ch == 'i' || ch == 'I')
					ADocument->FindSubstringInCaseSensitive(cr, cc);

			}
			else if (d == 18)
			{
				system("cls");
				cout << "Do you want to replace first or ALL?(F or A)" << endl;
				cin >> ch;
				if (ch == 'f' || ch == 'F')
					ADocument->Replaceword(cr, cc);
				else if (ch == 'a' || ch == 'A')
					ADocument->Replaceeveryword(cr, cc);


				ADocument->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 16)
			{

				system("cls");
				cout << "Do you want to add prefix or postfix?(e or o)" << endl;
				cin >> ch;
				if (ch == 'e' || ch == 'E')
					ADocument->Addprefix(cr, cc);
				else if (ch == 'o' || ch == 'O')
					ADocument->Addpostfix(cr, cc);

				ADocument->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 9)
			{
				ADocument->Average();
				ADocument->PrintDocument();
			}
			else if (d == 20)
			{
				ADocument->Substringcount();
				ADocument->PrintDocument();
			}
			else if (d == 11)
			{
				ADocument->Specialcharacter_count();
				ADocument->PrintDocument();
			}
			else if (d == 14)
			{
				ADocument->Number_of_sentences();
				ADocument->PrintDocument();
			}
			else if (d == 2)
			{
				ADocument->LargestWord_Length(cr, cc);
				ADocument->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 26)
			{
				ADocument->SmallestWord_Length(cr, cc);
				ADocument->PrintDocument();
				gotoRowCol(cr, cc);
			}
			else if (d == 15)
			{
				system("cls");
				menu();
				system("pause");
				system("cls");
				ADocument->PrintDocument();
			}
			else
			{
				ch = char(d);
				ADocument->InsertAcharacter(cr, cc, ch);
				ADocument->PrintDocument();
				cc++;

			}

			gotoRowCol(cr, cc);

		}
	}
}



//source




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