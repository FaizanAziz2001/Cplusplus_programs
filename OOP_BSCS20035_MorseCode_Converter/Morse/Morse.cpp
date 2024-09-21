#include <fstream>
#include <iostream>
#include<conio.h>
using namespace std;

struct Mcode
{
	char S;
	char Code[6];
};

void init(Mcode*& data, int& size)
{
	ifstream fin("Text.txt");
	fin >> size;
	size++;
	data = new Mcode[size];
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1)
		{
			fin >> data[i].S;
			fin >> data[i].Code;
		}
		else
		{
			data[i].S = ' ';
			fin >> data[i].Code;
		}
	}
}

char* MorseToEnglish(const char* inputchar,int inputsize,Mcode* data,int size)
{
	int length = inputsize / 5;
	char* ES = new char[length + 1]{};
	char sym=' ';
	int si =0;
	for (int i = 0; i < length; i++)
	{
		char* temp = new char[6]{};
		for (int j = 0; j < 5; j++)
		{
			temp[j] = inputchar[si++];
		}

		for (int k = 0; k < size; k++)
		{
			int count = 0;
			for (int i = 0; i < 5; i++)
			{
				if (temp[i] == data[k].Code[i])
					count++;
			}
			if (count == 5)
			{
				sym=data[k].S;
				break;
			}
		}
		ES[i] = sym;
	}
	return ES;
}

void Printall(Mcode* data,int size)
{
	cout << &data << " address in data (" << data << ")" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << &data[i] << " ==> \t";
		cout << data[i].S << "("<<(void*)&data[i].S << ") and " << data[i].Code << "( "<<  &data[i].Code << ")";
		cout << endl;
	}
}

void InsertAtEnd(char*& data,int& size,char T )
{
	char* heap = new char[size + 2]{};
	for (int i = 0; i < size; i++)
	{
		heap[i] = data[i];
	}
	heap[size] = T;
	delete data;
	data = heap;
	size++;
}
char* Load(int&size)
{
	char* data = new char[1]{};
	do
	{
		char sym = getchar();
		if (sym != '\n' && sym != '\t' && sym != '\0')
		{
			InsertAtEnd(data, size, sym);
		}
		else
			break;
	} while (true);
	return data;
}

char* EnglishToMorse(const char* inputchar,int inputsize,Mcode* data,int size)
{
	int length = inputsize*5;
	char* Morse = new char[length+1] {};
	int si = 0;

	for (int i = 0; i < inputsize; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (inputchar[i] == data[j].S)
			{
				for (int i = 0; i < 5; i++)
				{
					Morse[si] = data[j].Code[i];
					si++;
				}
			}
		}
	}
	return Morse;
}

void task1()
{
	Mcode* data{};
	int size = 0;
	init(data, size);
	Printall(data,size);
	cout << endl;

	cout << "Enter cypher text: ";
	cin.ignore();
	char* English{};
	int inputsize=0;
	char* inputchar = Load(inputsize);
	
	English=MorseToEnglish(inputchar,inputsize,data,size);
	cout << English;


}

void task2()
{
	Mcode* data{};
	int size = 0;
	init(data, size);
	Printall(data, size);
	cout << endl;
	int inputsize = 0;

	cout << "Enter cypher text:";
	cin.ignore();
	char* inputchar = Load(inputsize);

	char* Morse = EnglishToMorse(inputchar, inputsize, data, size);
	cout << Morse;
}

void menu()
{
	system("cls");
	cout << "1. Morse to English" << endl << "2. English to Morse" << endl;
				
}
int main()
{
	int choice;
	char cont;
	do
	{
		menu();
		cout << "Enter task number:";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			task1();
			break;
		case 2:	
			task2();
				break;
		}

		cout << endl << endl << "Do you want to continue (Y for yes)?" << endl;
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
}
