#pragma once

class Mystring
{
	int size;
	char* Cs;
	static int Str_length(const char*);
	void Deepcopy(const char*);

public:
	static int Atoi(const Mystring&);
	Mystring();
	Mystring(const char*);
	static Mystring itoa(int);
	Mystring(const Mystring&);
	void Print() const;
	int Length() const;
	bool equal(const Mystring& string) const;
	void ReplaceFirstC(char ch) const;
	int CMP(const Mystring& string) const;
	const char CharCopy(int i);
	char& CharRefAt(int);
	void Trim();
	Mystring str_cat(Mystring);
	int find_first(char ch);
	int find_last(char ch);
	int* find_all(char ch, int& Count);
	void remove_first(char ch);
	void remove_last(char ch);
	void remove_all(char ch);
	void remove_at(int i);
	void insert_at(int i, char ch);
	void insert_at(int i, const Mystring& sub);
	void clear();
	int* AllSubStrings(const char*, int&);
	void regrow(int*& data, int& size, int T);
	void regrowcharacter(char T);
	Mystring* Split(char c, int& count) const;
	Mystring* Tokenization(const char* c, int& count) const;


	~Mystring();
};




#include "Mystring.h"
#include<iostream>
using namespace std;

void Mystring::ReplaceFirstC(char ch) const
{
	this->Cs[0] = ch;
}

Mystring::Mystring()
{
	size = 0;
	Cs = {};
}

Mystring::Mystring(const char* string)
{
	Deepcopy(string);
}

void Mystring::Deepcopy(const char* string)
{
	size = Str_length(string);
	Cs = new char[size + 1]{};

	for (int i = 0; i < size; i++)
	{
		Cs[i] = string[i];
	}
}

Mystring::Mystring(const Mystring& string)
{
	Deepcopy(string.Cs);
}

int Mystring::Str_length(const char* string)
{
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}

void Mystring::Print() const
{
	cout << Cs;
}

int Mystring::Length() const
{
	return size;
}

bool Mystring::equal(const Mystring& string)const
{
	if (this->size != string.size)
		return false;

	for (int i = 0; i < this->size; i++)
	{
		if (this->Cs[i] != string.Cs[i])
			return false;
	}
	return true;
}

int Mystring::CMP(const Mystring& string) const
{

	if (this->equal(string))
		return 0;

	for (int i = 0; i != this->size && i != string.size; i++)
	{
		if (this->Cs[i] < string.Cs[i])
			return -1;
		if (this->Cs[i] > string.Cs[i])
			return 1;
	}

	if (this->size < string.size)
		return -1;
	if (this->size > string.size)
		return 1;
}

void Mystring::Trim()
{
	int count = 0;
	int size = Str_length(this->Cs);
	for (int i = 0; Cs[i] == ' ' || Cs[i] == '\t' || Cs[i] == '\n'; i++)
	{
		count++;
	}

	int si = count;

	for (int i = size - 1; Cs[i] == ' ' || Cs[i] == '\t' || Cs[i] == '\n'; i--)
	{
		count++;
	}

	int heapsize = size - count;
	char* heap = new char[heapsize + 1]{};

	for (int i = si, j = 0; j < heapsize; i++, j++)
	{
		heap[j] = Cs[i];
	}

	delete[] Cs;
	Cs = heap;
}

const char Mystring::CharCopy(int i)
{
	if (i >= size)
	{
		return NULL;
	}

	return Cs[i];
}

char& Mystring::CharRefAt(int i)
{

	if (i >= size)
	{
		char s = 0;
		cout << "Index is greater then string length" << endl;
		return s;
	}

	return Cs[i];
}

Mystring Mystring::str_cat(Mystring string)
{
	Mystring R;
	R.size = this->size + string.size;
	R.Cs = new char[R.size + 1]{};

	int Ri = 0;
	int i = 0, j = 0;
	while (Ri < R.size)
	{
		if (i < this->size)
		{
			R.Cs[Ri] = this->Cs[i++];
			Ri++;
		}
		else
		{
			R.Cs[Ri] = string.Cs[j++];
			Ri++;
		}
	}
	return R;
}

int Mystring::find_first(char ch)
{
	for (int i = 0; i < size; i++)
	{
		if (Cs[i] == ch)
			return i;
	}
}

int Mystring::find_last(char ch)
{
	for (int i = size - 1; i >= 0; i--)
	{
		if (Cs[i] == ch)
			return i;
	}
}

int* Mystring::find_all(char ch, int& count)
{
	count = 0;
	int si = 0;

	for (int i = 0; i < size; i++)
	{
		if (Cs[i] == ch)
			count++;;
	}

	int* heap = new int[count] {};

	for (int i = 0; i < size; i++)
	{
		if (Cs[i] == ch)
		{
			heap[si++] = i;
		}
	}
	return heap;
}

void Mystring::remove_first(char ch)
{
	int si = 0;
	bool flag = true;
	char* heap = new char[size] {};
	for (int i = 0; i < size; i++)
	{
		if (Cs[i] == ch && flag == true)
		{
			flag = false;
		}
		else
			heap[si++] = Cs[i];
	}
	delete[] Cs;
	Cs = heap;
}

void Mystring::remove_last(char ch)
{
	int count = 0;
	char* heap = new char[size] {};
	for (int i = size - 1; i >= 0; i--)
	{
		if (Cs[i] == ch)
		{
			count = i;
			break;
		}
	}

	int si = 0;
	for (int i = 0; i < size; i++)
	{
		if (i != count)
			heap[si++] = Cs[i];
	}

	delete[] Cs;
	Cs = heap;
}

void Mystring::remove_all(char ch)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (Cs[i] == ch)
			count++;
	}

	char* heap = new char[size - count + 1]{};
	int si = 0;
	for (int i = 0; i < size; i++)
	{
		if (Cs[i] != ch)
		{
			heap[si] = Cs[i];
			si++;
		}
	}

	delete[] Cs;
	Cs = heap;
}

void Mystring::remove_at(int x)
{
	if (x >= size)
	{
		cout << "Index is greater then size" << endl;
		return;
	}

	char* heap = new char[size] {};
	int si = 0;
	for (int i = 0; i < size; i++)
	{
		if (i != x)
			heap[si++] = Cs[i];
	}
	delete[] Cs;
	Cs = heap;
}

void Mystring::insert_at(int x, char ch)
{
	if (x > size)
	{
		cout << "Index is greater then size" << endl;
		return;
	}



	char* heap = new char[size + 2]{};
	int si = 0;
	int ci = 0;
	for (int i = 0; i < size + 1; i++)
	{
		if (i == x)
		{
			heap[si++] = ch;
		}
		else
			heap[si++] = Cs[ci++];
	}
	delete[] Cs;
	Cs = heap;
}

void Mystring::insert_at(int x, const Mystring& sub)
{
	int hi = 0;
	int ci = 0;
	char* heap = new char[this->size + sub.size + 1]{};
	for (int i = 0; i < size + 1; i++)
	{
		if (i == x)
		{
			for (int j = 0; j < sub.size; j++)
			{
				heap[hi++] = sub.Cs[j];
			}
		}
		else
			heap[hi++] = this->Cs[ci++];
	}
	delete[] Cs;
	Cs = heap;
}

void Mystring::clear()
{
	delete[] Cs;
	Cs = {};
}

int* Mystring::AllSubStrings(const char* string, int& count)
{
	int* heap{};
	int heapsize = 0;
	int length = Str_length(string);
	for (int i = 0; i < size; i++)
	{
		bool flag = true;
		if (Cs[i] == string[0])
		{
			for (int j = i, x = 0; x < length; x++, j++)
			{
				if (Cs[j] != string[x])
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				regrow(heap, heapsize, i);
				count++;
			}
		}
	}

	return heap;
}

void Mystring::regrow(int*& data, int& size, int T)
{
	int* heap = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		heap[i] = data[i];
	}
	heap[size] = T;
	delete[]data;
	data = heap;
	size++;
}

void Mystring::regrowcharacter(char T)
{
	char* heap = new char[size + 2]{};
	for (int i = 0; i < size; i++)
	{
		heap[i] = Cs[i];
	}
	heap[size] = T;
	delete[]Cs;
	Cs = heap;
	size++;
}

void splitcount(int& count, char c, char Cs[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (Cs[i] == c)
		{
			if (Cs[i + 1] == c && i == 0)
			{
				while (Cs[i] == c)
					i++;

			}
			else if (Cs[i + 1] == c)
			{
				while (Cs[i] == c)
					i++;
				if (i != size)
					count++;
			}

			else if (i != 0 && i != size - 1)
				count++;
		}


	}
}

Mystring* Mystring::Split(char c, int& count) const
{
	Mystring* p{};
	count = 1;
	splitcount(count, c, this->Cs, this->size);

	p = new Mystring[count]{};

	int si = 0;

	for (int i = 0; i < count; i)
	{
		if (Cs[si] == c)
			if (Cs[si + 1] == c)
			{
				while (Cs[si] == c)
					si++;
				continue;
			}
			else
				si++;
		while (Cs[si] != c && si < size)
			p[i].regrowcharacter(Cs[si++]);

		i++;
	}
	return p;
}

bool check(char data, const char* c, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (data == c[i])
			return true;
	}
	return false;
}

void tokencount(int& count, const char ch[], char Cs[], int size, int length)
{
	int si = 0;
	for (si; si < size; si++)
	{
		if (check(Cs[si], ch, length))
		{
			if (check(Cs[si + 1], ch, length))
			{
				if (si == 0)
				{
					while (check(Cs[si], ch, length))
						si++;
					continue;
				}
				else
				{
					while (check(Cs[si], ch, length))
						si++;
					if (si != size)
						count++;
				}
			}

			else
			{
				if (si != 0 && si != size - 1)
					count++;
				si++;

			}
		}

	}

}

Mystring* Mystring::Tokenization(const char* ch, int& count) const
{
	Mystring* p{};
	count = 1;
	int length = Str_length(ch);
	tokencount(count, ch, this->Cs, this->size, length);

	p = new Mystring[count]{};

	int si = 0;
	for (int i = 0; i < count; i++)
	{
		while (si < size)
		{
			if (check(Cs[si], ch, length))
			{
				if (check(Cs[si + 1], ch, length) && si == 0)
				{
					while (check(Cs[si], ch, length))
						si++;
					continue;

				}
				else if (check(Cs[si + 1], ch, length))
				{
					while (check(Cs[si], ch, length))
						si++;
					break;
				}
				else
				{
					if (si == 0)
					{
						si++;
						continue;
					}
					else
					{
						si++;
						break;
					}

				}
			}

			p[i].regrowcharacter(Cs[si]);
			si++;
		}
	}

	return p;
}

int Mystring::Atoi(const Mystring& string)
{
	int x = 0;
	for (int i = 0; i < string.size; i++)
	{
		x *= 10;
		x = (string.Cs[i] - 48) + x;
	}
	return x;
}

Mystring Mystring::itoa(int num)
{
	Mystring R;
	int temp = num;
	int count = 0;
	int i = 1;
	while (num > 0)
	{
		num = num / 10;
		i = i * 10;
		count++;
	}
	R.size = count;
	R.Cs = new char[R.size + 1]{};
	int si = 0;
	while (temp > 0)
	{
		i = i / 10;
		R.Cs[si++] = (temp / i) + 48;
		temp %= i;

	}

	return R;

}

Mystring::~Mystring()
{
	delete[] Cs;
	Cs = {};
}




#include <iostream>
#include "Mystring.h"
using namespace std;




void task1()
{
	//length
	Mystring s = "This is Pakistan";
	cout << "string: "; s.Print(); cout << endl;
	cout << s.Length();
}

void task2()
{
	//equal strings
	Mystring s1 = "abcde";
	Mystring s2 = "abcde";
	cout << "string s1: "; s1.Print(); cout << endl;
	cout << "string s2: "; s2.Print(); cout << endl;
	cout << s1.equal(s2);

}

void task3()
{
	//comparison
	Mystring s = "this is pakistan", s2 = "meer", s3 = "This is pakistan";
	cout << "string s1: "; s.Print(); cout << endl;
	cout << "string s2: "; s2.Print(); cout << endl;

	cout << s.CMP(s2);
}

void task4()
{
	//deepcopy
	Mystring s1 = "Sara";
	Mystring s2(s1);
	s1.ReplaceFirstC('z');
	s1.Print(); cout << endl;
	s2.Print(); cout << endl;
}

void task5()
{
	//Trim
	Mystring s1 = "   \t Pakistan   ";
	cout << "Before trim: "; s1.Print(); cout << endl;
	s1.Trim();
	cout << "After trim: "; s1.Print(); cout << endl;

}

void task6()
{
	//Char copy
	Mystring s1 = "Hello";
	cout << "string: "; s1.Print(); cout << endl;
	int x = 0;
	char ch = s1.CharCopy(x);
	s1.Print(); cout << endl;
	cout << "character at index " << x << " :" << ch;
}

void task7()
{
	//CharAtreference
	Mystring s1 = "This is Pakistan";
	cout << "String : "; s1.Print(); cout << endl;
	int x = 0;
	s1.CharRefAt(x) = 't';
	cout << "String after replacing character at reference : " << endl;
	s1.Print();

}

void task8()
{
	//string concatenation
	Mystring s1 = "Usama ", s2 = "is great";
	cout << "string s1: "; s1.Print(); cout << endl;
	cout << "string s2: "; s2.Print(); cout << endl;
	Mystring s3 = s1.str_cat(s2);
	cout << "String concatenation: ";
	s3.Print();
}

void task9()
{
	//find

	Mystring s = "Pakistan";
	cout << "String: "; s.Print(); cout << endl;
	int ind1, ind2, count = 0;
	int* ind3;
	ind1 = s.find_first('a');
	ind2 = s.find_last('a');
	ind3 = s.find_all('a', count);

	cout << "First index: " << ind1 << endl;
	cout << "Last index: " << ind2 << endl;
	cout << "All indexes: " << endl;
	for (int i = 0; i < count; i++)
	{
		cout << ind3[i] << endl;
	}

}

void task10()
{
	//remove character

	Mystring s1 = "Banana";
	Mystring s2 = "Banana";
	Mystring s3 = "Banana";
	cout << "String: "; s1.Print(); cout << endl;

	s1.remove_first('a');
	s2.remove_last('a');
	s3.remove_all('a');

	cout << "First character remove: "; s1.Print(); cout << endl;
	cout << "Last character remove: "; s2.Print(); cout << endl;
	cout << "All character remove: "; s3.Print(); cout << endl;


}

void task11()
{
	//remove at index
	Mystring s1 = "apple";
	cout << "String: "; s1.Print(); cout << endl;
	int x = 2;
	s1.remove_at(x);
	cout << "String after removing index " << x << " :"; s1.Print(); cout << endl;


}

void task12()
{
	// add at index
	Mystring s1 = "aple";
	cout << "String: "; s1.Print(); cout << endl;
	char ch = 'p';
	int x = 2;
	s1.insert_at(x, ch);
	cout << "String After inserting " << ch << " at " << x << " :"; s1.Print(); cout << endl;
}

void task13()
{
	//insert at index
	Mystring s1 = "is Great";
	Mystring s2 = "Usama";
	cout << "String s1: "; s1.Print(); cout << endl;
	cout << "String s2: "; s2.Print(); cout << endl;
	char ch = 'p';
	int x = 3;
	s1.insert_at(x, s2);
	cout << "String After inserting " << ch << " at " << x << " :"; s1.Print(); cout << endl;
}

void task14()
{
	Mystring s = "sarfaraz";
	cout << "String: "; s.Print(); cout << endl;
	s.clear();
	cout << "String has been cleared" << endl;
}

void task15()
{
	//substring
	Mystring s("This is pakistan");
	cout << "String: "; s.Print(); cout << endl;
	int count = 0;
	const char* ch = "is";
	int* All = s.AllSubStrings(ch, count);
	cout << "Substring : " << ch << endl;
	cout << "ALL's : " << endl;

	for (int i = 0; i < count; i++)
	{
		cout << "[" << i << "] " << All[i] << endl;
	}

}

void task16()
{
	//split
	Mystring s("This is   pakistan");
	cout << "String: "; s.Print(); cout << endl << endl;
	int count = 0;
	char ch = ' ';
	Mystring* split = s.Split(ch, count);

	cout << "Character : " << "'" << ch << "'" << endl;
	cout << "Split " << split << ": -->" << endl << endl;
	for (int i = 0; i < count; i++)
	{
		cout << &split[i] << " "; split[i].Print(); cout << endl;
	}

	cout << endl << "count: " << count << endl;
}

void task17()
{
	//Tokenization
	Mystring s("]]]]]]][[[[[[[[This,,,,[[[[ is!!!!!pakistan,,,,,,,,,,,");
	cout << "String: "; s.Print(); cout << endl << endl;
	int count = 0;
	const char* ch = "],[!";
	Mystring* split = s.Tokenization(ch, count);

	cout << "Characters : " << "'" << ch << "'" << endl;
	cout << "Split " << split << ": -->" << endl << endl;
	for (int i = 0; i < count; i++)
	{
		cout << &split[i] << " "; split[i].Print(); cout << endl;
	}

	cout << endl << "count: " << count << endl;
}

void task18()
{
	//Alphabet to integer
	Mystring s = "99";
	int val = Mystring::Atoi(s);
	cout << "String : "; s.Print(); cout << endl;
	cout << "Integer : " << val << endl;
	cout << "Integer+1 : " << val + 1 << endl;
}

void task19()
{
	//Integer to alphabet
	int x = 123;
	Mystring s = Mystring::itoa(x);
	cout << "Integer : " << x << endl;
	cout << "String : "; s.Print(); cout << endl;
}

void menu()
{
	system("cls");
	cout << "1. Display length" << endl
		<< "2. Equal strings" << endl
		<< "3. Comparing strings" << endl
		<< "4. Deep copy " << endl
		<< "5.Trim a string" << endl
		<< "6. Char copy" << endl
		<< "7. Char at reference" << endl
		<< "8. String concatenation" << endl
		<< "9. Find string" << endl
		<< "10. Remove charatcer" << endl
		<< "11. Remove at index" << endl
		<< "12. Add a character at index" << endl
		<< "13. Add a string at index" << endl
		<< "14. Clear a string" << endl
		<< "15. Check substring" << endl
		<< "16. Split a string" << endl
		<< "17. Tokenize a string" << endl
		<< "18. Convert string to integer" << endl
		<< "19. Convert integer to string" << endl;

}

int main()
{

	int n;
	char cont;
	do
	{
		menu();
		cout << "Enter a task number: ";
		cin >> n;
		system("cls");
		switch (n)
		{
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
		case 4:
			task4();
			break;
		case 5:
			task5();
			break;
		case 6:
			task6();
			break;
		case 7:
			task7();
			break;
		case 8:
			task8();
			break;
		case 9:
			task9();
			break;
		case 10:
			task10();
			break;
		case 11:
			task11();
			break;
		case 12:
			task12();
			break;
		case 13:
			task13();
			break;
		case 14:
			task14();
			break;
		case 15:
			task15();
			break;
		case 16:
			task16();
			break;
		case 17:
			task17();
			break;
		case 18:
			task18();
			break;
		case 19:
			task19();
			break;
		}

		cout << endl << endl << "Do you want to continue?(y for yes)";
		cin >> cont;

	} while (cont == 'y' || cont == 'Y');
}

