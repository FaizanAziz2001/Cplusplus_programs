
#include <iostream>
#include<string>
#include<vector>
#include<math.h>
#include<fstream>
using namespace std;

void binary_conversion(int input, vector <int>& binary)
{
	int total = 0;
	int temp = input;
	vector<int> temp2;
	do
	{
		temp2.push_back(temp % 2);
		temp = temp / 2;
	} while (temp > 0);

	for (int i = temp2.size() - 1; i >= 0; i--)
	{
		binary.push_back(temp2[i]);
	}

}

void convert_to_binary(string input, vector <int>& binary)
{

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ')
			binary_conversion(int(input[i]), binary);
	}
}

void convert_to_decimal(vector <int>& binary, vector<int>& decimal)
{
	int count = 0;
	int total = 0;
	for (int i = binary.size() - 1; i >= 0; i--)
	{
		if (count == 5)
		{
			count = 0;
			decimal.push_back(total);
			total = 0;
		}
		
		total = total + (binary[i] * pow(2, count));
		count++;
	}

	if (count != 5 && total!=0)
	{
		decimal.push_back(total);
	}
}

void read_data(vector<char>& system)
{
	char input;
	ifstream fin("number_system.txt");
	while (fin)
	{
		fin >> input;
		if (fin)
			system.push_back(input);
	}
}

void comparison(vector<char> system, vector<int> decimal)
{
	for (int i = decimal.size() - 1; i >= 0; i--)
	{
		cout << system[decimal[i]] << " ";
	}
}

void task()
{
	string input{};
	vector <int> binary;
	vector<int> decimal;
	vector <char> system;
	cout << "Enter a string: ";
	getline(cin, input);
	convert_to_binary(input, binary);
	convert_to_decimal(binary, decimal);
	read_data(system);
	comparison(system, decimal);
}

int main()
{
	task();
	return 0;

}

