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

