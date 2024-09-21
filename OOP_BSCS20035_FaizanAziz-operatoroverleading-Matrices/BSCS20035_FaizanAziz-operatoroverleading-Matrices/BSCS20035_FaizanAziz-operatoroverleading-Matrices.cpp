#include "Matrix.h"
#include <iostream>
using namespace std;

void init_Matrix(Matrix*& M, int& NOM)
{
	ifstream fin("Input.txt");
	fin >> NOM;
	M = new Matrix[NOM];
	for (int i = 0; i < NOM; i++)
	{
		M[i].init(fin);
	}
}
void Print_All(Matrix* M, int NOM)
{
	for (int i = 0; i < NOM; i++)
	{
		cout << M[i] << endl;
	}
}
void menu()
{
	cout << "1. + for Add" << endl
		<< "2. - for Sub" << endl
		<< "3. * for Multi" << endl
		<< "4. pre increment" << endl
		<< "5. post increment" << endl
		<< "6. += for AddAccumulate" << endl
		<< "7. -= for SubAccumulate" << endl
		<< "8. *= for MultiAccumulate" << endl
		<< "9. for Scaler Subtraction" << endl
		<< "10. for Scalar Multiplication" << endl
		<< "11. == for equal matrix" << endl
		<< "12. - for Mimic" << endl
		<< "13. ~ for Transpose" << endl
		<< "14. ^ for Clockwise rotation" << endl
		<< "15. > for Anti-Clockwise rotation" << endl;
}
void Matrices(Matrix* M, int NOM)
{

	Print_All(M, NOM);

	char opr{}, dummy{}, cont;
	int rsi{}, loi{}, roi{};

	do
	{
		cout << "Example Format: F1 = F2 + F3" << endl;
		cout << "Example Format: F1 = F2 - F3" << endl;
		cout << "Example Format: F1 = F2 * F3" << endl;
		cout << "Input: ";
		cin >> dummy >> rsi >> dummy >> dummy >> loi >> opr >> dummy >> roi;
		rsi--; loi--; roi--;

		switch (opr)
		{
		case '+':
			M[rsi] = M[loi] + (M[roi]);
			break;

		case '-':
			M[rsi] = M[loi] - (M[roi]);
			break;

		case '*':
			M[rsi] = M[loi] * (M[roi]);
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y for yes): ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
	system("pause");

}
void AccumulateMatrices(Matrix* M, int NOM)
{

	Print_All(M, NOM);

	char opr{}, dummy{}, cont;
	int loi{}, roi{};

	do
	{
	
		cout << "Example Format: F1 + F2" << endl;
		cout << "Example Format: F1 - F2" << endl;
		cout << "Example Format: F1 * F2" << endl;
		cout << "Example Format: F1 = F2" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		loi--; roi--;

		switch (opr)
		{
		case '+':
			M[loi] += (M[roi]);
			break;

		case '-':
			M[loi] -= (M[roi]);
			break;

		case '*':
			M[loi] *= (M[roi]);
			break;
		case '=':
			if (M[loi] == M[roi])
				cout << "Matrix are equal" << endl;
			else;
			cout << "Matrix are not equal" << endl;
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y): ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
	system("pause");

}
void SingleMatrix(Matrix* M, int NOM)
{
	Print_All(M, NOM);

	int ind;
	char d, op, cont;

	do
	{
		
		cout << "Format: -M1 (Mimic)" << endl;
		cout << "Format: ~M1 (transpose)" << endl;
		cout << "Format: pM1 (pre increment)" << endl;
		cout << "Format: oM1 (post increment) "<< endl;
		cout << "Format: cM1 (clockwise rotation) " << endl;
		cout << "Format: aM1 (anticlockwise rotation) " << endl;
		cout << "Input: ";
		cin >> op >> d >> ind;
		ind--;
		int rotation;

		switch (op)
		{
		case '-':
			M[ind] = -M[ind];
			break;

		case '~':
			M[ind] = ~M[ind];
			break;
		case'p':
			M[ind]++;
			break;
		case 'o':
			++M[ind];
			break;
		case 'c':
			cout << "Enter clockwise rotation degree: ";
			cin >> rotation;
			M[ind] = (M[ind] ^ rotation/90);
			break;
		case 'a':
			cout << "Enter anti clockwise rotation degree: ";
			cin >> rotation;
			M[ind] = (M[ind] > rotation/90);
			break;
		}
		Print_All(M, NOM);
		
		cout << endl << " Do You Want To Continue?(Y for yes): ";
		cin >> cont;
		system("cls");

	} while (cont == 'Y' || cont == 'y');
	system("pause");
}
void ScalarMatrix(Matrix* M,int NOM)
{
	Print_All(M, NOM);

	char opr{}, dummy{}, cont;
	int rsi, ind, scalar;

	do
	{
		cout << "Example Format: F1 = F2 - 5" << endl;
		cout << "Example Format: F1 = F2 * 5" << endl;
		cout << "Input: ";
		cin >> dummy >> rsi >> dummy >> dummy >> ind >> opr >> scalar;
		ind--;

		switch (opr)
		{
		case '-':
			M[rsi] = M[ind] - scalar;
			break;

		case '*':
			M[rsi] = M[ind] * scalar;
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y for yes) ";
		cin >> cont;

		system("cls");

	} while (cont == 'Y' || cont == 'y');
	system("pause");

}

int main()
{
	int input, cont;
	Matrix* M{};
	int NOM = 0;
	init_Matrix(M, NOM);

	do
	{
		system("cls");
		cout << "Enter task number: " << endl
			<< "1. Multiple Matrix Operations" << endl
			<< "2. Single Matrix Operations" << endl
			<< "3. Accumulate Matrix Operations" << endl
			<< "4. Scaler Matrix Operations" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			Matrices(M, NOM);
			break;

		case 2:
			SingleMatrix(M, NOM);
			break;
		case 3:
			AccumulateMatrices(M, NOM);
			break;
		case 4:
			ScalarMatrix(M, NOM);
			break;
		}

		cout << "Do you want to continue(Y for yes)";
		cin >> cont;

	} while (cont == 'Y' || cont == 'y');
}
