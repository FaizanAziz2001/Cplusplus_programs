
#include <iostream>
#include<fstream>
using namespace std;

#define capacity 100

struct matrix
{
	int Matrix[capacity][capacity] = {};
	int row = 0;
	int column = 0;
	int dim = 0;
};

struct pos
{
	int ri = 0;
	int ci = 0;
};

void init(matrix& M, string name)
{
	ifstream fin(name);
	fin >> M.row >> M.column;
	fin >> M.dim;
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			fin >> M.Matrix[ri][ci];
		}
	}
}

void init2(matrix& M, string name)
{
	ifstream fin(name);
	fin >> M.row >> M.column;
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			fin >> M.Matrix[ri][ci];
		}
	}
}

void calculator_input(ifstream& fin, matrix& M)
{
	fin >> M.row >> M.column;
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			fin >> M.Matrix[ri][ci];
		}
	}
}

int WindowSum(matrix M, int ri, int ci)
{
	int sum = 0;
	for (int r = 0; r < M.dim; r++)
	{
		for (int c = 0; c < M.dim; c++)
		{
			sum += M.Matrix[r + ri][c + ci];
		}
	}
	return sum;
}

void FindMaxMatrix(matrix M, int& mri, int& mci)
{
	int MaxWindowSum = WindowSum(M, 0, 0);
	mri = 0, mci = 0;
	for (int ri = 0; ri <= M.dim; ri++)
	{
		for (int ci = 0; ci <= M.dim; ci++)
		{
			int WS = WindowSum(M, ri, ci);
			if (WS > MaxWindowSum)
			{
				MaxWindowSum = WS;
				mri = ri;
				mci = ci;
			}
		}
	}
}

void display(matrix M)
{
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			cout << M.Matrix[ri][ci] << " ";
		}
		cout << endl;
	}
}

void displayarray(int M[][capacity], int row, int column)
{
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < column; ci++)
		{
			cout << M[ri][ci] << " ";
		}
		cout << endl;
	}
}

void Copywindow(int Max[][capacity], matrix M, int mri, int mci)
{
	for (int r = 0; r < M.dim; r++)
	{
		for (int c = 0; c < M.dim; c++)
		{
			Max[r][c] = M.Matrix[mri + r][mci + c];
		}
	}
}

void CRotation(matrix M, int CM[][capacity])
{
	int CMri = M.column;
	int CMci = M.row;
	for (int ri = 0; ri < CMri; ri++)
	{

		for (int ci = 0; ci < CMci; ci++)
		{
			CM[ri][CMci - (ci + 1)] = M.Matrix[ci][ri];
		}
	}
}

void AntiCRotation(matrix M, int CM[][capacity])
{
	int CMri = M.column;
	int CMci = M.row;
	for (int ri = 0; ri < CMri; ri++)
	{
		for (int ci = 0; ci < CMci; ci++)
		{
			CM[CMri - (ri + 1)][ci] = M.Matrix[ci][ri];
		}
	}
}

void Prisoner_location(matrix M, pos& P)
{
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			if (M.Matrix[ri][ci] == 2)
			{
				P.ri = ri;
				P.ci = ci;
				return;
			}
		}
	}
}

void PrisonToplocation(matrix M, pos& P)
{
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			if (M.Matrix[ri][ci] == 1)
			{
				P.ri = ri;
				P.ci = ci;
				return;
			}
		}
	}

}

void PrisonBottomlocation(matrix M, pos& P)
{
	for (int ri = M.row - 1; ri >= 0; ri--)
	{
		for (int ci = M.column - 1; ci >= 0; ci--)
		{
			if (M.Matrix[ri][ci] == 1)
			{
				P.ri = ri;
				P.ci = ci;
				return;
			}
		}
	}

}

bool H_check(matrix M, pos P1, pos P2)
{
	for (int ci = P1.ci; ci <= P2.ci; ci++)
	{
		if (M.Matrix[P1.ri][ci] == 0)
			return true;
	}

	for (int ci = P1.ci; ci <= P2.ci; ci++)
	{
		if (M.Matrix[P2.ri][ci] == 0)
			return true;
	}
	return false;
}

bool V_check(matrix M,pos P1,pos P2)
{
	for (int ri = P1.ri; ri <= P2.ri; ri++)
	{
		if (M.Matrix[ri][P1.ci] == 0)
			return true;
	}

	for (int ri = P1.ri; ri<= P2.ri; ri++)
	{
		if (M.Matrix[ri][P1.ci] == 0)
			return true;
	}
	return false;
}

void Prisoner_condition(matrix M, pos P1, pos P2, pos P)
{
	Prisoner_location(M, P);
	PrisonToplocation(M, P1);
	PrisonBottomlocation(M, P2);

	if (H_check(M, P1, P2) == false && V_check(M, P1, P2) == false)
	{
		cout << "Prisoner cannot escape";
		return;
	}

	if (P.ri > P1.ri && P.ci > P1.ci && P.ri < P2.ri && P.ci < P2.ci)
	{
		cout << "Priosner can escape but is inside";
	}
	else
		cout << "Prionser is already outside";
}

void TRAPPED_BreakAble_Free(matrix M, string name,pos P1,pos P2,pos P)
{
	init2(M, name);
	display(M);
	Prisoner_condition(M, P1, P2, P);
	

	
}

void task1()
{
	string name = "TASK1 matrix.txt";
	matrix M;
	int MaxM[capacity][capacity], mri, mci;
	init(M, name);
	display(M);
	FindMaxMatrix(M, mri, mci);
	Copywindow(MaxM, M, mri, mci);

	cout << "Largest sum window: " << endl;
	displayarray(MaxM, M.dim, M.dim);
}

void task2()
{
	string name = "prison.txt";
	matrix M;
	pos TopP, BottomP, P;
	TRAPPED_BreakAble_Free(M, name,TopP,BottomP,P);
}

void task3()
{
	string name = "Task3 input.txt";
	matrix M;
	int CM[capacity][capacity];
	init2(M, name);
	cout << "Input matrix:" << endl;
	display(M); cout << endl;
	CRotation(M, CM);
	cout << "Output matrix:" << endl;
	displayarray(CM, M.column, M.row);
}

void task4()
{
	string name = "Task4 input.txt";
	matrix M;
	int CM[capacity][capacity];
	init2(M, name);
	cout << "Input matrix:" << endl;
	display(M); cout << endl;
	AntiCRotation(M, CM);
	cout << "Output matrix:" << endl;
	displayarray(CM, M.column, M.row);
}

bool Matrix_addition(matrix M1, matrix M2, matrix& A)
{
	if (M1.row != M2.row && M1.column != M2.column)
	{
		return false;
	}
	A.row = M1.row;
	A.column = M1.column;
	for (int ri = 0; ri < A.row; ri++)
	{
		for (int ci = 0; ci < A.column; ci++)
			A.Matrix[ri][ci] = M1.Matrix[ri][ci] + M2.Matrix[ri][ci];
	}

	return true;
}

bool Matrix_subtraction(matrix M1, matrix M2, matrix& A)
{
	if (M1.row != M2.column && M1.column != M2.column)
	{
		return false;
	}
	A.row = M1.row;
	A.column = M1.column;
	for (int ri = 0; ri < A.row; ri++)
	{
		for (int ci = 0; ci < A.column; ci++)
			A.Matrix[ri][ci] = M1.Matrix[ri][ci] - M2.Matrix[ri][ci];
	}
	return true;
}

bool Matrix_multiplication(matrix M1, matrix M2, matrix& A)
{
	int sum = 0;
	if (M1.column != M2.row)
	{
		return false;
	}
	A.row = M1.row;
	A.column = M2.column;
	for (int ri = 0; ri < M1.row; ri++)
	{
		for (int r = 0; r < M2.column; r++)
		{
			sum = 0;
			for (int ci = 0; ci < M2.row; ci++)
			{
				sum = sum + (M1.Matrix[ri][ci] * M2.Matrix[ci][r]);
			}
			A.Matrix[ri][r] = sum;
		}

	}

	return true;
}

void Scalar_multiplication(matrix M, matrix& A, int num)
{
	A.row = M.row;
	A.column = M.column;
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			A.Matrix[ri][ci] = (num * M.Matrix[ri][ci]);
		}
	}
}

void Scalar_Subtraction(matrix M, matrix& A, int num)
{
	A.row = M.row;
	A.column = M.column;
	for (int ri = 0; ri < M.row; ri++)
	{
		for (int ci = 0; ci < M.column; ci++)
		{
			A.Matrix[ri][ci] = num - M.Matrix[ri][ci];
		}
	}
}

bool Equal_Matrices(matrix M1, matrix M2)
{
	bool flag = true;
	int count = 0;
	if (M1.row != M2.row && M1.column != M2.column)
	{
		return false;
	}

	for (int ri = 0; ri < M1.row; ri++)
	{
		for (int ci = 0; ci < M2.row; ci++)
		{
			if (M1.Matrix[ri][ci] != M2.Matrix[ri][ci])
				flag = false;
		}
	}

	return flag;
}

void Transpose_Matrices(matrix M, matrix& A)
{
	A.row = M.column;
	A.column = M.row;

	for (int ci = 0; ci < A.column; ci++)
	{
		for (int ri = 0; ri < A.row; ri++)
		{
			A.Matrix[ri][ci] = M.Matrix[ci][ri];
		}
	}
}

void calculator_menu(matrix M1, matrix M2, matrix R)
{
	char expression;
	cout << "Enter the symbol of operation: ";
	cin >> expression;

	cout << "Input array 1: " << endl;
	display(M1);
	cout << "Input array 2: " << endl;
	display(M2); cout << endl << endl;
	if (expression == '+')
	{

		if (Matrix_addition(M1, M2, R))
		{
			cout << "Output Array: " << endl;
			display(R);
		}
		else
			cout << "Rows and Columns are not equal" << endl;
	}
	else if (expression == '-')
	{

		if (Matrix_subtraction(M1, M2, R))
		{
			cout << "Output Array: " << endl;
			display(R);
		}
		else
			cout << "Rows and Columns are not equal" << endl;
	}
	else if (expression == '*')
	{
		int num, choice;
		cout << "1. Scalar Multiplication" << endl
			<< "2. Multiplication of Matrices" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter the scalar number:";
			cin >> num;
			int num2;
			cout << "Do you want to multiply K with M1 or M2(1 for M1 or 2 for M2): " << endl;
			cin >> num2;
			if (num2 == 1)
			{
				Scalar_multiplication(M1, R, num);
				cout << "Output array:" << endl;
				display(R);
			}
			else if (num2 == 2)
			{
				Scalar_multiplication(M2, R, num);
				cout << "Output array:" << endl;
				display(R);
			}
			break;
		case 2:
			if (Matrix_multiplication(M1, M2, R))
			{
				cout << "Output Array: " << endl;
				display(R);
			}
			else
				cout << "Rows and Columns are not equal" << endl;
			break;

		}

	}
	else if (expression == '$')
	{
		int num, choice;
		cout << "Enter the scalar number:";
		cin >> num;
		cout << "1. Scalar subtraction with Matrix 1" << endl
			<< "2. Scaler subtraction with Matrix 2" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Output array: " << endl;
			Scalar_Subtraction(M1, R, num);
			display(R);
			break;
		case 2:
			cout << "Output array: " << endl;
			Scalar_Subtraction(M2, R, num);
			display(R);
			break;
		}
	}
	else if (expression == '=')
	{
		if (Equal_Matrices(M1, M2) == true)
			cout << "Matrices are equal" << endl;
		else
			cout << "Matrices are not equal" << endl;
	}
	else if (expression == '^')
	{
		int num;
		cout << "1 for M1 or 2 for M2: ";
		cin >> num;
		if (num == 1)
		{
			cout << "Output array: " << endl;
			Transpose_Matrices(M1, R);
			display(R);
		}
		else if (num == 2)
		{
			cout << "Output array: " << endl;
			Transpose_Matrices(M2, R);
			display(R);
		}
	}


}

void Calculator()
{
	char cont;
	ifstream fin("Calculator.txt");
	matrix M1, M2, R;
	calculator_input(fin, M1);
	calculator_input(fin, M2);
	do
	{
		system("cls");
		calculator_menu(M1, M2, R);

		cout << endl;
		cout << "Do you want to exit the calculator?(Y of yes): ";
		cin >> cont;
	} while (cont != 'y' && cont != 'Y');

}

void menu()
{
	system("cls");
	cout << "1. Window searching problem (Task1)" << endl
		<< "2. Prison break (Task2)" << endl
		<< "3. Clockwise rotation of matrix (Task3)" << endl
		<< "4. Anti-Clockwise rotation of matrix (Task4)" << endl
		<< "5. Matrix Calculator (Task5)" << endl;
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
		case 4:
			task4();
			break;
		case 5:
			Calculator();
			break;
		}

		cout << endl << endl;
		cout << "Do you want to exit the program?(Y for yes)";
		cin >> cont;
	} while (cont != 'y' && cont != 'Y');
}

