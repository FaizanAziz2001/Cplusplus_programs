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
