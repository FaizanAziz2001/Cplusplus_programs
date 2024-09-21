#pragma once
#include<iostream>
using namespace std;


class Hashstring
{
	int p = 51;
	long long mod = 1e9 + 9;

public:
	
	long long HashFunction(string s)
	{
		long long power = 1;
		long long sum=0;
		for (int i = 0; i < s.length(); i++)
		{
			sum = (sum + (s[i] - 48 + 1) * power) % mod;
			power = (power * p) % mod;
		}

		cout << "Hash value of " << sum << " is: " << sum;
		return sum % mod;
	}

	
};