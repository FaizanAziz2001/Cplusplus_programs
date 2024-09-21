#include <iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

struct Student
{
	string name{};
	string roll_number{};
	string department{};
	int age{};
	float gpa{};
	char Gender{};
};

void init(int& NOS, vector<Student>& S)
{

	ifstream fin("Input.txt");
	fin >> NOS;
	S.resize(NOS);

	for (int i = 0; i < NOS; i++)
	{

		fin.ignore();
		getline(fin, S[i].name);
		fin >> S[i].roll_number;
		fin >> S[i].department;
		fin >> S[i].age;
		fin >> S[i].gpa;
		fin >> S[i].Gender;
		fin.ignore();
	}
}

bool Asc_name(Student A, Student B)
{
	return (A.name > B.name);
}
bool Dsc_name(Student A, Student B)
{
	return (A.name < B.name);
}
bool Asc_roll(Student A, Student B)
{
	return (A.roll_number > B.roll_number);
}
bool Dsc_roll(Student A, Student B)
{
	return (A.roll_number < B.roll_number);
}
bool Asc_depart(Student A, Student B)
{
	return (A.department > B.department);
}
bool Dsc_depart(Student A, Student B)
{
	return (A.department < B.department);
}
bool Asc_Age(Student A, Student B)
{
	return (A.age > B.age);
}
bool Dsc_Age(Student A, Student B)
{
	return (A.age < B.age);
}
bool Asc_Gender(Student A, Student B)
{
	return (A.Gender > B.Gender);
}
bool Dsc_Gender(Student A, Student B)
{
	return (A.Gender < B.Gender);
}
bool Asc_gpa(Student A, Student B)
{
	return (A.gpa > B.gpa);
}
bool Dsc_gpa(Student A, Student B)
{
	return (A.gpa < B.gpa);
}


void Sort(vector<Student>& S, bool(fptr(Student, Student)))
{
	for (int i = 1; i < S.size(); i++)
	{
		for (int i = 0; i + 1 < S.size(); i++)
		{
			if (fptr(S[i], S[i + 1]))
				swap(S[i], S[i + 1]);
		}
	}
}

void printall(const vector<Student>& S)
{

	for (int i = 0; i < S.size(); i++)
	{
		cout << "Student # " << i + 1 << endl;
		cout << S[i].name << endl
			<< S[i].roll_number << endl
			<< S[i].department << endl
			<< S[i].age << endl
			<< S[i].gpa << endl
			<< S[i].Gender << endl;

		cout << endl;
	}
}

void menu()
{
	cout << "1 for ascending to names" << endl
		<< "2 for ascending to roll number" << endl
		<< "3 for ascending to department " << endl
		<< "4 for ascending to age " << endl
		<< "5 for ascending to gpa " << endl
		<< "6 for ascending to gender" << endl << endl
		<< "7 for descending to names" << endl
		<< "8 for descending to roll number" << endl
		<< "9 for descending to department " << endl
		<< "10 for descending to age " << endl
		<< "11 for descending to gpa " << endl
		<< "12 for descending to gender" << endl << endl;
}

void switchmenu(vector<Student>& S)
{
	bool (*fptr) (Student, Student) = nullptr;
	int choice;
	char cont;

	do
	{
		menu();
		cout << "Enter the task number to sort: ";
		cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1:
			fptr = Asc_name;
			break;
		case 2:
			fptr = Asc_roll;
			break;
		case 3:
			fptr = Asc_depart;
			break;
		case 4:
			fptr = Asc_Age;
			break;
		case 5:
			fptr = Asc_gpa;
			break;
		case 6:
			fptr = Asc_Gender;
			break;
		case 7:
			fptr = Dsc_name;
			break;
		case 8:
			fptr = Dsc_roll;
			break;
		case 9:
			fptr = Dsc_depart;
			break;
		case 10:
			fptr = Dsc_Age;
			break;
		case 11:
			fptr = Dsc_gpa;
			break;
		case 12:fptr = Dsc_Gender;
			break;
		}

		cout << "Before sort : \n\n";
		printall(S);

		cout << endl;
		cout << "After sort :\n\n";
		Sort(S, fptr);
		printall(S);


		cout << "\n\nDo you want to continue(Y for yes)\n";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
}

int main()
{

	int NOS, choice;
	char cont;
	vector<Student> S;

	init(NOS, S);
	switchmenu(S);

	return 0;



}

