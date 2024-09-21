

#include <iostream>
#include<stack>
#include<string>
#include "HugeInt.h"
using namespace std;

int precedence(char c)
{
	// To find out precedence of character

	if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;

}

void reverse_string(string& k, string s)
{
	// to reverse the entire string
	char temp;
	while (!s.empty())
	{
		temp = s.back();
		k.push_back(temp);
		s.pop_back();
	}
}


string invert_numbers(string s)
{
	// To invert only the numbers while operators remain the same
	string k;
	int si = 0, size = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
		{
			si = i;
			size++;
		}
		else if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-')
			k = k + s[i];
		else if (s[i] == ' ')
		{

			while (size != 0)
			{
				k = k + s[si];
				si--;
				size--;
			}
			size = 0;
			si = 0;
			k = k + s[i];
		}

	}

	while (size != 0)
	{
		k = k + s[si];
		si--;
		size--;
	}

	return k;
}

string convert_to_postfix(string s) {

	string res;
	stack<char> d;
	bool check = true; // for negative
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
		{
			res = res + s[i];
			check = false; // for negative
		}
		else if (s[i] == ' ')
		{
			if (!res.empty() && res.back() == ' ')	// Add spacing the post fix string
				res.pop_back();
			res = res + s[i];

		}
		else if (s[i] == '(')
		{
			d.push(s[i]);
			check = true;	// for negative
		}
		else if (s[i] == ')')
		{
			while (d.top() != '(')
			{
				res = res + d.top();
				res = res + " ";
				d.pop();
			}
			d.pop();
		}
		else if (!isdigit(s[i]))
		{
			if (check && d.empty() && s[i] == '-' || check && d.size() != 0 && d.top() == '(' && s[i] == '-') // for negative
			{
				res = res + s[i];
				i++;
				check = false;
				continue;
			} // till here
			if (d.empty())
			{
				d.push(s[i]);
				continue;
			}
			else if (precedence(s[i]) == precedence(d.top()))
			{
				while (!d.empty() && precedence(s[i]) == precedence(d.top()))
				{
					res = res + d.top();
					d.pop();
				}
			}
			else if (precedence(s[i]) > precedence(d.top()))
			{
				d.push(s[i]);
				continue;
			}
			else if (precedence(s[i]) < precedence(d.top()))
			{
				while (!d.empty() && precedence(s[i]) <= precedence(d.top()))
				{
					res = res + d.top();
					d.pop();
				}
			}
			d.push(s[i]);


		}
	}
	while (!d.empty())
	{
		if (res.back() == ' ')
			res.pop_back();
		res = res + ' ';
		res = res + d.top();

		d.pop();
	}
	return res;
}

string convert_to_prefix(string k) {

	string res;
	reverse_string(res, k);
	string s = invert_numbers(res);
	res = "";
	stack<char> d;
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
			res = res + s[i];
		else if (s[i] == ' ')
		{
			if (!res.empty() && res.back() == ' ')		// add spacing in prefix
				res.pop_back();
			res = res + s[i];
		}
		else if (s[i] == ')')
			d.push(s[i]);
		else if (s[i] == '(')
		{

			while (d.top() != ')')
			{
				res = res + d.top();
				res = res + " ";
				d.pop();
			}
			d.pop();
		}
		else if (!isdigit(s[i]))
		{

			if (d.empty())
			{
				d.push(s[i]);
				continue;
			}
			else if (precedence(s[i]) == precedence(d.top()))
			{
				d.push(s[i]);
				continue;
			}
			else if (precedence(s[i]) > precedence(d.top()))
			{
				d.push(s[i]);
				continue;
			}
			else if (precedence(s[i]) < precedence(d.top()))
			{
				while (!d.empty() && precedence(s[i]) < precedence(d.top()))
				{
					res = res + d.top();
					d.pop();
				}
			}
			d.push(s[i]);
		}
	}

	while (!d.empty())
	{
		if (res.back() == ' ')
			res.pop_back();
		res = res + ' ';
		res = res + d.top();

		d.pop();
	}
	s = "";
	res = invert_numbers(res);
	reverse_string(s, res);

	return s;
}

HugeInt operations(char op, HugeInt op1, HugeInt op2)
{
	if (op == '*')				// Perform the operations
		return (op1 * op2);
	else if (op == '/')
		return (op1 / op2);
	else if (op == '+')
		return (op1 + op2);
	else
		return (op1 - op2);
}

HugeInt calculate_postfix(string s)
{
	string res = convert_to_postfix(s);
	string data;
	stack<HugeInt> pf;
	HugeInt sum, num, temp2, temp1;
	bool check = false;
	for (int i = 0; i < res.length(); i++)
	{
		if (data.length() == 0 && res[i] == ' ')
		{
			continue;
		}
		if (res[i] == '-' && isdigit(res[i + 1])) // condition for negative
			check = true;
		else if (res[i] == ' ')
		{
			num.SetIntegerpost(data);
			if (check)			// for negative
			{
				HugeInt temp(-1);
				num = num * temp;
				check = false;
			} // till here
			pf.push(num);
			data = "";
		}
		else if (isdigit(res[i]))
		{
			data = data + res[i];
		}
		else if (!isdigit(res[i]))
		{
			temp1 = pf.top();
			pf.pop();
			temp2 = pf.top();
			pf.pop();

			sum = operations(res[i], temp2, temp1);
			pf.push(sum);
		}
	}
	return pf.top();
}

HugeInt calculate_prefix(string s)
{
	string res = convert_to_prefix(s);
	res = invert_numbers(res);
	string data;
	stack<HugeInt> pf;
	HugeInt sum, num, temp1, temp2;
	for (int i = res.length() - 1; i >= 0; i--)
	{
		if (data.length() == 0 && res[i] == ' ')
		{
			continue;
		}
		if (res[i] == ' ')
		{
			num.SetIntegerpre(data);
			pf.push(num);
			data = "";
		}
		else if (isdigit(res[i]))
		{
			data = data + res[i];
		}
		else if (!isdigit(res[i]))
		{
			temp1 = pf.top();
			pf.pop();
			if (!pf.empty())
			{
				temp2 = pf.top();
				pf.pop();
			}
			else
			{
				HugeInt temp(0);
				temp2.SetInteger(temp);
			}
			sum = operations(res[i], temp1, temp2);
			pf.push(sum);
		}
	}
	return pf.top();
}


int main()
{
	string s, choice;
	do
	{
		cout << "Enter an expression: (With spaces) " << endl;
		getline(cin, s);

		//string s = "( ( 123123123124132423523543243 - 12312312312423423423221343124132413431241324132413 / 1498393431431452345234523413241 ) * 39493054124132413241234123431241241 - 31313123141324132545346533123123 + ( 43434653635635653653354 / 123123182483489239842984298429848924899842983 ) - 3132134365365324532452345432543252345343543 )";
		//string s = "41324132432413243 * ( 413413413243124141 / ( 4314314132413424 * 124324134132 ) - 413431431241341314 ) - 4134314134134314 * ( 43143141341324312 / 43143124134413 ) - 441341343124132413242 + ( 14134132413241344 / 55432523454325233 )";

		cout << "Expression: " << s << endl << endl;
		cout << "Postfix conversion: " << endl << convert_to_postfix(s) << endl << endl;
		cout << calculate_postfix(s) << endl << endl;
		cout << "Prefix conversion: " << endl << convert_to_prefix(s) << endl << endl;
		cout << calculate_prefix(s) << endl << endl;
		system("pause");
		system("cls");

	} while (choice != "e" && choice != "E");


	return 0;
}
