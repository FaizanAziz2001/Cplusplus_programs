#include <iostream>
#include<math.h>
#include<vector>
using namespace std;

#pragma region part1

int sum1(int n)
{
	if (n == 1)
		return 1;
	return n + sum1(n - 1);
}

int sum_odd(int n)
{
	if (n == 1)
		return 1;
	return n + sum_odd(n - 2);
}

long long sum_geomatric_series(int n, int b)
{
	if (b == 0)
		return 1;
	return pow(n, b) + sum_geomatric_series(n, b - 1);
}

int sum5(int n)
{
	if (n == 1)
		return 1;
	return n + sum5(n / 3);
}

int sum6(int n)
{
	if (n == 1)
		return 1;
	return n + sum5(n / 2);
}

#pragma endregion part1


#pragma region part2

char Digit_to_char(int n)
{
	if (n <= 9)
	{
		return '0' + n;
	}
	else
		return 'A' + n - 10;
}

int binary_to_decimal(int n)
{
	if (n == 0)
		return 0;
	return binary_to_decimal(n / 2) * 10 + (n % 2);

}

string itoa(int n)
{
	if (n == 0)
		return "";
	return itoa(n / 10) + Digit_to_char(n % 10);

}

long long GCD(long long A, long long B)
{
	if (A % B == 0)
		return B;
	return GCD(B, A % B);

}

#pragma endregion part2


#pragma region part3

int SearchFirstEntry(int A[], int si, int size, int number)
{
	if (A[si] == size)
		return -1;
	if (A[si] == number)
		return si;
	return SearchFirstEntry(A, si + 1, size, number);

}

int SearchLastEntry(int A[], int size, int number)
{
	if (size <= 0)
		return -1;
	if (A[size] == number)
		return size;
	return SearchLastEntry(A, size - 1, number);

}

int BinarySearch(int A[], int si, int ei, int number)
{
	int midpoint = si + (ei - si) / 2;
	if (si > ei)
		return -1;
	if (A[midpoint] == number)
		return midpoint;
	else if (A[midpoint] < number)
		BinarySearch(A, midpoint + 1, ei, number);
	else
		BinarySearch(A, si, midpoint - 1, number);
}

#pragma endregion part3


#pragma region part4

void array_generator(int A[], int size)
{
	for (int i = 0; i < size; i++)
	{
		A[i] = i;
	}
}

int power(int A, int B, int M)
{
	if (B == 0)
		return 1;
	return (A * power(A, B - 1, M)) % M;
}

int Fast_power(int A, int B, int M)
{
	if (B == 0)
		return 1;
	int R = Fast_power(A, B / 2, M);
	if (B % 2 == 0)
		return (R * R) % M;
	else
		return (A * R * R) % M;
}

#pragma endregion part4


#pragma region part5 and 6

long long Slow_MULT(long long A, long long B)
{
	if (B == 0)
		return 0;
	return A + Slow_MULT(A, B - 1);
}

long long Slow_Division(long long A, long long B)
{
	if (A < B)
		return 0;
	if (A == 0 || B == 0)
		return 0;
	else if (A < 0)
		return -1;
	int count = 1;
	return count + Slow_Division(A - B, B);
}

long long Slow_Mod(long long A, long long B)
{
	if (A < B)
		return A;
	if (A == 0)
		return 0;
	return Slow_Mod(A - B, B);
}

long long Fast_MULT(long long A, long long B)
{
	if (B == 0)
		return 0;
	int Total = A, C = 1;
	while (C + C <= B)
	{
		Total += Total;
		C += C;
	}

	return Total + Fast_MULT(A, B - C);
}

long long Fast_division(long long A, long long B)
{
	if (A < B)
		return 0;
	if (A == 0 || B == 0)
		return 0;
	else if (A < 0)
		return -1;
	int Total = B, C = 1;
	while (Total + Total <= A)
	{
		Total += Total;
		C += C;
	}
	return C + Fast_division(A - Total, B);
}

long long Fast_mod(long long A, long long B)
{
	if (A < B)
		return A;
	if (A == 0 || B == 0)
		return 0;
	else if (A < 0)
		return -1;
	int Total = B, C = 1;
	while (Total + Total <= A)
	{
		Total += Total;
		C += C;
	}
	return Fast_mod(A - Total, B);
}

#pragma endregion part5 and 6


#pragma region part7

long long fib(long long n)
{
	if (n == 0 || n == 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

long long Fast_fib(vector<long>& Fs, long long n)
{
	if (Fs[n] != -1)
		return Fs[n];
	return Fs[n] = Fast_fib(Fs, n - 1) + Fast_fib(Fs, n - 2);

}

long long fib_loop(long long n)
{
	long long* Fib = new long long[n + 1];
	Fib[0] = 0;
	Fib[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		Fib[i] = Fib[i - 1] + Fib[i - 2];
	}
	return Fib[n];
}

long long Memory_Based_fib(long long n)
{
	vector<long> Fs(n + 1, { -1 });
	Fs[0] = 0;
	Fs[1] = 1;
	return Fast_fib(Fs, n);
}

#pragma endregion part7


#pragma region part8

long long Trisum(long long n)
{
	if (n == 0 || n == 1 || n == 2 || n == 3)
		return n;
	return Trisum(n - 1) + Trisum(n - 2) + Trisum(n - 3);
}

long long Trisum_loop(long long n)
{
	long long* Tr = new long long[n + 1];
	Tr[0] = 0;
	Tr[1] = 1;
	Tr[2] = 2;
	Tr[3] = 3;
	for (int i = 4; i <= n; i++)
	{
		Tr[i] = Trisum(i - 1) + Trisum(i - 2) + Trisum(i - 3);
	}
	return Tr[n];
}

long long Fast_Trisum(vector<long>& Ts, long long n)
{
	if (Ts[n] != -1)
		return Ts[n];
	return Ts[n] = Fast_Trisum(Ts, n - 1) + Fast_Trisum(Ts, n - 2) + Fast_Trisum(Ts, n - 3);
}

long long Memory_Based_Trisum(long long n)
{
	vector<long> Fs(n + 4, { -1 });
	Fs[0] = 0;
	Fs[1] = 1;
	Fs[2] = 2;
	Fs[3] = 3;
	return Fast_Trisum(Fs, n);
}

int Trisum_Generator(long long n)
{
	if (n == 0)
		return 1;
	Trisum_Generator(n - 1);
	cout << Trisum(n) << " ";
	return 0;
}

#pragma endregion part8


int main()
{

	cout << sum5(9);

}

