#include <iostream>
#include<fstream>
using namespace std;


int binary_to_decimal(string in)
{
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}

string decimal_to_binary(int in,int n=0)
{
	string temp = "";
	string result = "";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	if(n==1)
	result.append(8 - temp.size(), '0');
	else
		result.append(4 - temp.size(), '0');
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}


void write_File()
{
	ofstream fout;
	fout.open("File.txt");
	int result;
	for (int i = 0; i < pow(2, 4); i++)
	{
		for (int j = 0; j < pow(2, 4); j++)
		{
			result = i * j;
			fout << decimal_to_binary(i) << " " << decimal_to_binary(j) << " " << decimal_to_binary(result,1) << endl;
		}
	}
}


string read_File(string A1, string B1)
{
	ifstream fin;
	fin.open("File.txt");
	string input1, input2, output;
	while (!fin.eof())
	{
		fin >> input1 >> input2 >> output;
		if (input1 == A1 && input2 == B1)												
			return output;
	}
	return " ";
}


int main()
{
	write_File();																
	string input1;
	string input2;
	cout << "Enter two 4 bit binary numbers->  " << endl << endl;
	cin >> input1;																	
	cin >> input2;
	string output;
	output = read_File(input1, input2);										

	cout << "Output is: ";
	cout << output << "   [" << binary_to_decimal(output) << "] " << endl;
}
