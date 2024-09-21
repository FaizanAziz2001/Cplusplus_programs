#include"Set.h"
#include <iostream>
#include<fstream>
using namespace std;

void Load(Set**& S,int& NOS)
{
    ifstream fin("Set.txt");
    fin >> NOS;
    S = new Set * [NOS];
    for (int i = 0; i < NOS; i++)
    {
        S[i] = new Set(fin);
    }
}

void Printall(Set** S, const int NOS)
{
	for (int i = 0; i < NOS; i++)
	{
		cout <<  "Set " << i+1 << ": " << *S[i] ;
	}
}

void Binary(Set**S, int NOS)
{
	char opr{}, dummy{}, cont;
	int rsi{}, loi{}, roi{};
	
	do
	{
		Printall(S, NOS);
		cout << "Example Format: F1 = F2 + F3" << endl;
		cout << "Example Format: F1 = F2 - F3" << endl;
		cout << "Example Format: F1 = F2 ^ F3" << endl;
		cout << "Input: ";
		cin >> dummy >> rsi >> dummy >> dummy >> loi >> opr >> dummy >> roi;
		rsi--; loi--; roi--;

		switch (opr)
		{
		case '+':
			*S[rsi] = *S[loi] + (*S[roi]);
			break;

		case '-':
			*S[rsi] = *S[loi] - (*S[roi]);
			break;

		case '^':
			*S[rsi] = *S[loi]^ (*S[roi]);
			break;
		}
		
		Printall(S, NOS);
		cout << endl << " Do You Want To Continue?(Y for yes): ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
}

void AccumulateSet(Set** S, int NOS)
{

	char opr{}, dummy{}, cont;
	int loi{}, roi{};

	do
	{
		Printall(S, NOS);
		cout << "Example Format: F1 + F2 (for +=)" << endl;
		cout << "Example Format: F1 - F2 (for+-)"<< endl;
		cout << "Example Format: F1 * F2 (Cartesian product)"<< endl;
		cout << "Example Format: F1 = F2 (check equal sets)" << endl;
		cout << "Example Format: F1 | F2 (check Disjoint sets)" << endl;
		cout << "Example Format: F1 ~ F2 (store F2 complement)" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		loi--; roi--;

		switch (opr)
		{
		case '+':
			*S[loi] += (*S[roi]);
			break;

		case '-':
			*S[loi] -= (*S[roi]);
			break;
		case '~':
			*S[loi] = ~(*S[roi]);
			break;

		case '*':
			*S[loi] * (*S[roi]); cout << endl;
			break;
		case '|':
			if (*S[loi] | *S[roi])
				cout << "Sets are Disjoint" << endl;
			else;
			cout << "Sets are not Disjoint" << endl;
			break;
		case '=':
			if (*S[loi] == *S[roi])
				cout << "Matrix are equal" << endl;
			else;
			cout << "Matrix are not equal" << endl;
			break;
		}
	
		Printall(S, NOS);
		cout << endl << " Do You Want To Continue?(Y): ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');

}

void ScalarSet(Set** S, int NOS)
{
	char opr{}, dummy{}, cont;
	int loi,input,input2;


	do
	{
		Printall(S, NOS);
		cout << "Example Format: F1 + 5 (for +=5)" << endl;
		cout << "Example Format: F1 - 5 (for -=5)" << endl;
		cout << "Example Format: F1 [ 5 (for value on 5 index)" << endl;
		cout << "Example Format: F1 ] 5 (for storing value on 5 index)" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> input;
		loi--; 

		switch (opr)
		{
		case '+':
			*S[loi] += input;
			break;

		case '-':
			*S[loi] -= input;
			break;
		case '[':
			cout << S[loi][0][input];
			break;
		case ']':
			cout << "Enter the number to store: ";
			cin >> input2;
			S[loi][0][input]=input2;
			break;
		}
		Printall(S, NOS);

		cout << endl << " Do You Want To Continue?(Y for yes) ";
		cin >> cont;

		system("cls");

	} while (cont == 'Y' || cont == 'y');

}

int main()
{
    int NOS = 0,input=0;
	char cont;
    Set** S{};
    Load(S, NOS); 

	do
	{
		system("cls");
		cout << "Enter task number: " << endl
			<< "1. Multiple Set Operations" << endl
			<< "2. Accumulate Set Operations" << endl
			<< "3. Scaler Set Operations" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			Binary(S, NOS);
			break;

		case 2:
			AccumulateSet(S, NOS);
			break;
		case 3:
			ScalarSet(S, NOS);
			break;
		}

		cout << "Do you want to continue(Y for yes)";
		cin >> cont;

	} while (cont == 'Y' || cont == 'y');
}

    

