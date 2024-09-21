#include <iostream>
#include<fstream>
using namespace std;

string Decimal_to_Binary(int num, int nob)
{

	string s, bin;
	int n;
	while (num >= 1)
	{
		n = num % 2;												//converts to binary in reverse
		s.push_back(n + 48);
		num = num / 2;
	}

	if (s.size() < nob)
	{
		while (s.size() != nob)													//append 0's to make fill given bits
		{
			s.push_back('0');
		}
	}

	while (!s.empty())
	{
		bin.push_back(s.back());												//reverse the string to make it in original format
		s.pop_back();
	}
	return bin;
}

int BinaryToDecimal(string s)
{
	int sum = 0;
	int num;
	for (int i = 0; i < s.size(); i++)
	{
		num = s[s.size() - 1 - i] - 48;
		sum = sum + (pow(2, i) * num);
	}
	return sum;
}

int binary_to_decimal(string in)
{
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}


void Write_File(int nob)
{
	ofstream fout("Data.txt");
	int mult;
	for (int i = 0; i < pow(2, nob); i++)
	{
		for (int j = 0; j < pow(2, nob); j++)
		{
			mult = i * j;
			fout << Decimal_to_Binary(i, nob) << " " << Decimal_to_Binary(j, nob) << " " << Decimal_to_Binary(mult, nob * 2) << endl;				//Write the conversion
		}
	}
}


string Read_File(string A, string B)
{
	ifstream fin("Data.txt");
	string input1, input2, output;
	while (fin.good())
	{
		fin >> input1;
		fin >> input2;
		fin >> output;

		if (fin.eof())
			break;
		if (input1 == A && input2 == B)												//if the combination matches,return the output
			return output;
	}
	return " ";
}


int main()
{
	binary_to_decimal("1000");
	Write_File(4);																	//Write all 4 bit multiplication combinations in a file
	string input1, input2;
	cout << "Enter two 4 bit binary numbers to multiply: " << endl;
	cin >> input1;																	//Tke 2 4 bit numbers from user
	cin >> input2;
	string output = Read_File(input1, input2);										//Search the file for given combination

	cout << "Output: ";
	cout << input1 << "(" << BinaryToDecimal(input1) << ") * ";
	cout << input2 << "(" << BinaryToDecimal(input2) << ") = ";
	cout << output << "( " << BinaryToDecimal(output) << " )" << endl;			//Display the output
}
