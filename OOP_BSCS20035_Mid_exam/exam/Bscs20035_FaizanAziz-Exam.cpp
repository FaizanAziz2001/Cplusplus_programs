#include<fstream>
#include<iostream>
#include<string>
using namespace std;

struct Mcode
{
	char S;
	char Code[6];
};

struct DynamicArray
{
	float* data;
	int size;
};

void init(Mcode S[])
{
	ifstream fin("Text.txt");
	for (int i = 0; i < 27; i++)
	{
		if (i != 26)
		{
			fin >> S[i].S;
			for (int j = 0; j < 5; j++)
			{
				fin >> S[i].Code[j];
			}
			S[i].Code[5] = 0;
		}
		else
		{
			S[i].S = ' ';
			for (int j = 0; j < 5; j++)
			{
				fin >> S[i].Code[j];
			}
			S[i].Code[5] = 0;
		}

	}
}

void print(DynamicArray D)
{
	for (int i = 0; i < D.size; i++)
	{
		cout << D.data[i] << "(" << &D.data[i] << ")";
		if (i != D.size - 1)
		{
			cout << ",  ";
		}

		
	}
}

void InsertinSortedArray(DynamicArray& D,float T)
{
	bool flag = true;
	float* heap = new float[D.size+1];
	
	if (D.size != 0)
	{
		for (int i = D.size, j=D.size-1; i >= 0; i--)
		{
			if (T > D.data[j] && flag==true)
			{
				heap[i]=T;
				flag = false;
			}
			else
				heap[i] = D.data[j--];
		}
		
	}
	else
		heap[D.size] = T;
	delete [] D.data;
	D.data = heap;
	D.size++;

	print(D);
	cout << endl;
}

void initalize(DynamicArray& D)
{
	ifstream fin("Input.txt");
	float input = 0;
	do
	{
		fin >> input;
		InsertinSortedArray(D, input);
		
	} while (input != -99);
}

void compare(Mcode G[], Mcode S[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			if (strncmp(G[i].Code, S[j].Code, 5) == 0)
				cout << S[j].S;
		}
	}
}

void compareAlpha(Mcode G[], Mcode S[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < 27; k++)
		{
			if (G[i].S == S[k].S)
			{
				for (int j = 0; j < 5; j++)
				{

					cout << S[k].Code[j];
				}
			}
		}
	}
}

void task1()
{
	Mcode S[27]{};
	Mcode G[100]{};
	string M;
	cout << "Enter input: ";
	cin.ignore();
	getline(cin, M);
	init(S);
	int i = 0, size = 0;

	while (M[i] != 0)
	{
		for (int j = 0; j < 5; j++)
		{
			if (M[i] != 0)
				G[size].Code[j] = M[i++];
		}
		size++;
	}
	compare(G, S, size);
}

void task2()
{
	Mcode S[27]{};
	Mcode G[100]{};
	string M;
	cin.ignore();
	cout << "Enter input: ";
	getline(cin, M);
	init(S);
	int i = 0, size = 0;

	while (M[i] != 0)
	{
		G[size].S = M[i++];
		size++;
	}
	compareAlpha(G, S, size);
}

void task3()
{
	DynamicArray DA{};
	initalize(DA);
}

void menu()
{
	system("cls");
	cout << "1. Convert Morse into Text " << endl
		<< "2. Convert Text into Morse" << endl
		<< "3. Store data in sorted array " << endl;
}

int main()
{
	int choice;
	char cont;
	do
	{
		menu();
		cout << "Enter task number: ";
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
		case 3:
			task3();
			break;
		}
		cout << endl << endl;
		cout << "Do you want to continue?(Y for yes)";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');

}

