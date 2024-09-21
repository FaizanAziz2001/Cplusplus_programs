#include <iostream>
#include "Mystring.h"
using namespace std;

void task1()
{
	//length
	Mystring s = "This is Pakistan";
	cout << "string: "; s.Print(); cout << endl;
	cout << s.Length();
}

void task2()
{
	//equal strings
	Mystring s1 = "abcde";
	Mystring s2 = "abcde";
	cout << "string s1: "; s1.Print(); cout << endl;
	cout << "string s2: "; s2.Print(); cout << endl;
	cout << s1.equal(s2);

}

void task3()
{
	//comparison
	Mystring s = "this is pakistan", s2 = "meer", s3 = "This is pakistan";
	cout << "string s1: "; s.Print(); cout << endl;
	cout << "string s2: "; s2.Print(); cout << endl;

	cout << s.CMP(s2);
}

void task4()
{
	//deepcopy
	Mystring s1 = "Sara";
	Mystring s2(s1);
	s1.ReplaceFirstC('z');
	s1.Print(); cout << endl;
	s2.Print(); cout << endl;
}

void task5()
{
	//Trim
	Mystring s1 = "   \t Pakistan   ";
	cout << "Before trim: "; s1.Print(); cout << endl;
	s1.Trim();
	cout << "After trim: "; s1.Print(); cout << endl;

}

void task6()
{
	//Char copy
	Mystring s1 = "Hello";
	cout << "string: "; s1.Print(); cout << endl;
	int x = 0;
	char ch = s1.CharCopy(x);
	s1.Print(); cout << endl;
	cout << "character at index " << x << " :" << ch;
}

void task7()
{
	//CharAtreference
	Mystring s1 = "This is Pakistan";
	cout << "String : "; s1.Print(); cout << endl;
	int x = 0;
	s1.CharRefAt(x) = 't';
	cout << "String after replacing character at reference : " << endl;
	s1.Print();

}

void task8()
{
	//string concatenation
	Mystring s1 = "Usama ", s2 = "is great";
	cout << "string s1: "; s1.Print(); cout << endl;
	cout << "string s2: "; s2.Print(); cout << endl;
	Mystring s3 = s1.str_cat(s2);
	cout << "String concatenation: ";
	s3.Print();
}

void task9()
{
	//find

	Mystring s = "Pakistan";
	cout << "String: "; s.Print(); cout << endl;
	int ind1, ind2, count = 0;
	int* ind3;
	ind1 = s.find_first('a');
	ind2 = s.find_last('a');
	ind3 = s.find_all('a', count);

	cout << "First index: " << ind1 << endl;
	cout << "Last index: " << ind2 << endl;
	cout << "All indexes: " << endl;
	for (int i = 0; i < count; i++)
	{
		cout << ind3[i] << endl;
	}

}

void task10()
{
	//remove character

	Mystring s1 = "Banana";
	Mystring s2 = "Banana";
	Mystring s3 = "Banana";
	cout << "String: "; s1.Print(); cout << endl;

	s1.remove_first('a');
	s2.remove_last('a');
	s3.remove_all('a');

	cout << "First character remove: "; s1.Print(); cout << endl;
	cout << "Last character remove: "; s2.Print(); cout << endl;
	cout << "All character remove: "; s3.Print(); cout << endl;


}

void task11()
{
	//remove at index
	Mystring s1 = "apple";
	cout << "String: "; s1.Print(); cout << endl;
	int x = 2;
	s1.remove_at(x);
	cout << "String after removing index " << x << " :"; s1.Print(); cout << endl;


}

void task12()
{
	// add at index
	Mystring s1 = "aple";
	cout << "String: "; s1.Print(); cout << endl;
	char ch = 'p';
	int x = 2;
	s1.insert_at(x, ch);
	cout << "String After inserting " << ch << " at " << x << " :"; s1.Print(); cout << endl;
}

void task13()
{
	//insert at index
	Mystring s1 = "is Great";
	Mystring s2 = "Usama";
	cout << "String s1: "; s1.Print(); cout << endl;
	cout << "String s2: "; s2.Print(); cout << endl;
	char ch = 'p';
	int x = 3;
	s1.insert_at(x, s2);
	cout << "String After inserting " << ch << " at " << x << " :"; s1.Print(); cout << endl;
}

void task14()
{
	Mystring s = "sarfaraz";
	cout << "String: "; s.Print(); cout << endl;
	s.clear();
	cout << "String has been cleared" << endl;
}

void task15()
{
	//substring
	Mystring s("This is pakistan");
	cout << "String: "; s.Print(); cout << endl;
	int count = 0;
	const char* ch = "is";
	int* All = s.AllSubStrings(ch, count);
	cout << "Substring : " << ch << endl;
	cout << "ALL's : " << endl;

	for (int i = 0; i < count; i++)
	{
		cout << "[" << i << "] " << All[i] << endl;
	}

}

void task16()
{
	//split
	Mystring s("This is   pakistan");
	cout << "String: "; s.Print(); cout << endl << endl;
	int count = 0;
	char ch = ' ';
	Mystring* split = s.Split(ch, count);

	cout << "Character : " << "'" << ch << "'" << endl;
	cout << "Split " << split << ": -->" << endl << endl;
	for (int i = 0; i < count; i++)
	{
		cout << &split[i] << " "; split[i].Print(); cout << endl;
	}

	cout << endl << "count: " << count << endl;
}

void task17()
{
	//Tokenization
	Mystring s("]]]]]]][[[[[[[[This,,,,[[[[ is!!!!!pakistan,,,,,,,,,,,");
	cout << "String: "; s.Print(); cout << endl << endl;
	int count = 0;
	const char* ch = "],[!";
	Mystring* split = s.Tokenization(ch, count);

	cout << "Characters : " << "'" << ch << "'" << endl;
	cout << "Split " << split << ": -->" << endl << endl;
	for (int i = 0; i < count; i++)
	{
		cout << &split[i] << " "; split[i].Print(); cout << endl;
	}

	cout << endl << "count: " << count << endl;
}

void task18()
{
	//Alphabet to integer
	Mystring s = "99";
	int val = Mystring::Atoi(s);
	cout << "String : "; s.Print(); cout << endl;
	cout << "Integer : " << val << endl;
	cout << "Integer+1 : " << val + 1 << endl;
}

void task19()
{
	//Integer to alphabet
	int x = 123;
	Mystring s = Mystring::itoa(x);
	cout << "Integer : " << x << endl;
	cout << "String : "; s.Print(); cout << endl;
}

void menu()
{
	system("cls");
	cout << "1. Display length" << endl
		<< "2. Equal strings" << endl
		<< "3. Comparing strings" << endl
		<< "4. Deep copy " << endl
		<< "5.Trim a string" << endl
		<< "6. Char copy" << endl
		<< "7. Char at reference" << endl
		<< "8. String concatenation" << endl
		<< "9. Find string" << endl
		<< "10. Remove charatcer" << endl
		<< "11. Remove at index" << endl
		<< "12. Add a character at index" << endl
		<< "13. Add a string at index" << endl
		<< "14. Clear a string" << endl
		<< "15. Check substring" << endl
		<< "16. Split a string" << endl
		<< "17. Tokenize a string" << endl
		<< "18. Convert string to integer" << endl
		<< "19. Convert integer to string" << endl;

}

int main()
{

	int n;
	char cont;
	do
	{
		menu();
		cout << "Enter a task number: ";
		cin >> n;
		system("cls");
		switch (n)
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
			task5();
			break;
		case 6:
			task6();
			break;
		case 7:
			task7();
			break;
		case 8:
			task8();
			break;
		case 9:
			task9();
			break;
		case 10:
			task10();
			break;
		case 11:
			task11();
			break;
		case 12:
			task12();
			break;
		case 13:
			task13();
			break;
		case 14:
			task14();
			break;
		case 15:
			task15();
			break;
		case 16:
			task16();
			break;
		case 17:
			task17();
			break;
		case 18:
			task18();
			break;
		case 19:
			task19();
			break;
		}

		cout << endl << endl << "Do you want to continue?(y for yes)";
		cin >> cont;

	} while (cont == 'y' || cont == 'Y');
}

