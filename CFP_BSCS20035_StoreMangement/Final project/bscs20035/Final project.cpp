

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

void display_products();
void display_sales();
void search_products();
void search_sales();
void add_item();
void update_products();
void update_sales();
void del();
void buy();
void reset_sales();
void reset_products();
void copy_data();
void setup_names();
void display_names();
void total_sales();
void item();
int getinput();


int main()
{
	int num;
	char customer;
	while (true)
	{
		cout << "Press C for customer, A for Admin or E to exit: ";
		cin >> customer;

		if (customer == 'C' || customer == 'c')
		{
			cout << "\t WELCOME CUSTOMER" << endl
				<< "----------------------------------------" << endl;
			buy();
			cout << "You will receive your order in 15 mins " << endl;
			system("pause");
			system("cls");
		}

		else if (customer == 'A' || customer == 'a')
		{
			while (true)
			{
				cout << "\t WELCOME ADMIN" << endl
					<< "------------------------------------------------------------" << endl
					<< "\tEnter a number to proceed " << endl
					<< "\tEnter 1 \tto display products: " << endl
					<< "\tEnter 2 \tto search products: " << endl
					<< "\tEnter 3 \tto search sales: " << endl
					<< "\tEnter 4 \tto add products: " << endl
					<< "\tEnter 5 \tto update products: " << endl
					<< "\tEnter 6 \tto update sales: " << endl
					<< "\tEnter 7 \tto delete products: " << endl
					<< "\tEnter 8 \tto display sales: " << endl
					<< "\tEnter 9 \tto reset sales data: " << endl
					<< "\tEnter 10 \tto reset products data: " << endl
					<< "\tEnter 11 \tto copy data: " << endl
					<< "\tEnter 12 \tto reset names data: " << endl
					<< "\tEnter 13 \tto display names data:" << endl
					<< "\tEnter 14 \tto exit: " << endl;

				cout << "------------------------------------------------------------" << endl;
				num = getinput();

				if (num == 1)
				{
					display_products();
					system("pause");
					system("cls");
				}
				else if (num == 2)
				{
					search_products();
				}
				else if (num == 3)
				{
					search_sales();

				}
				else if (num == 4)
				{
					add_item();
				}
				else if (num == 5)
				{
					update_products();
				}
				else if (num == 6)
				{
					update_sales();
				}
				else if (num == 7)
				{
					del();
					system("cls");
				}
				else if (num == 8)
				{
					display_sales();
					system("pause");
					system("cls");
				}
				else if (num == 9)
				{
					reset_sales();
				}
				else if (num == 10)
				{
					reset_products();
				}
				else if (num == 11)
				{
					copy_data();
				}
				else if (num == 12)
				{
					setup_names();
				}
				else if (num == 13)
				{
					display_names();
				}
				else if (num == 14)
				{
					system("cls");
					break;
				}
				else
				{
					cout << "You have entered wrong input" << endl;
					system("pause");
					system("cls");
				}
			}
		}
		else if (customer == 'E' || customer == 'e')
		{
			return 0;
		}
		else
		{
			cout << "Please enter a valid input" << endl;
			system("pause");
			system("cls");
		}
	}
}

void display_products()
{
	char data[77];
	ifstream fin("products.txt");
	while (!fin.eof())
	{
		fin.getline(data, 77);
		if (strncmp(&data[5], "                              ", 30) != 0)
			cout << data << endl;
	}
	fin.close();
}

void display_sales()
{
	char data[102];
	ifstream fin("sales.txt");
	while (!fin.eof())
	{
		fin.getline(data, 102);
		if (strncmp(&data[5], "                              ", 30) != 0)
			cout << data << endl;
	}
	fin.close();
	cout << endl;
	total_sales();
	item();

}

void search_products()
{
	display_products();
	char search[30], data[77], content[30];
	int counter = 0;
	cout << "Enter the text you want to search: ";
	cin.ignore();
	cin.getline(search, 30);

	for (int i = 0; i < strlen(search); i++)
	{
		if (isupper(search[i]))
			search[i] = search[i] + 32;
	}

	ifstream fin("products.txt");
	cout << left << setw(5) << "Num"
		<< left << setw(30) << "Item Name"
		<< left << setw(10) << "Quantity"
		<< right << setw(10) << "Small"
		<< right << setw(10) << "Medium"
		<< right << setw(10) << "Large" << endl;

	while (!fin.eof())
	{
		fin.getline(data, 77);
		strncpy_s(content, &data[5], 29);

		for (int i = 0; i < strlen(content); i++)
		{
			if (isupper(content[i]))
				content[i] = content[i] + 32;
		}

		if (strncmp(content, search, strlen(search)) == 0)
		{
			cout << data << endl;
			counter++;
		}
	}
	cout << endl;
	if (counter == 0)
	{
		cout << "No records found" << endl;
	}
	fin.close();
	system("pause");
	system("cls");
}

void search_sales()
{
	display_sales();
	char search[30], data[102], content[30];
	int counter = 0;
	cout << "Enter the text you want to search: ";
	cin.ignore();
	cin.getline(search, 30);

	for (int i = 0; i < strlen(search); i++)
	{
		if (isupper(search[i]))
			search[i] = search[i] + 32;
	}

	ifstream fin("sales.txt");
	cout << left << setw(5) << "Num"
		<< left << setw(30) << "Item Name"
		<< left << setw(15) << "Items sold"
		<< right << setw(10) << "Small"
		<< right << setw(10) << "Medium"
		<< right << setw(10) << "Large"
		<< right << setw(20) << "Revenue Generated" << endl;

	while (!fin.eof())
	{
		fin.getline(data, 102);
		strncpy_s(content, &data[5], 29);

		for (int i = 0; i < strlen(content); i++)
		{
			if (isupper(content[i]))
				content[i] = content[i] + 32;
		}
		if (strncmp(content, search, strlen(search)) == 0)
		{
			cout << data << endl;
			counter++;
		}
	}
	cout << endl;
	if (counter == 0)
	{
		cout << "No records found" << endl;
	}
	fin.close();
	system("pause");
	system("cls");
}

void add_item()
{
	int quantity, small_price, medium_price, large_price, num;
	char name[77], compare[77];
	display_products();
	cout << "Enter the number: ";
	num = getinput();

	fstream f("products.txt", ios::in | ios::out);
	f.seekg(77 * num + 5);
	f.read(compare, 30);
	if (strncmp(compare, "                             ", 29) != 0)
	{
		cout << "data already exists at num  " << num << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "Enter the item name: ";
	cin.ignore();
	cin.getline(name, 77);
	cout << "Enter the quantity:";
	quantity = getinput();
	cout << "Enter the small price:";
	small_price = getinput();
	cout << "Enter the medium price:";
	medium_price = getinput();
	cout << "Enter the large price:";
	large_price = getinput();

	f.seekp(77 * num + 5);
	f << left << setw(30) << name;
	f.seekp(77 * num + 35);
	f << left << setw(10) << quantity;
	f.seekp(77 * num + 45);
	f << right << setw(10) << small_price;
	f.seekp(77 * num + 55);
	f << right << setw(10) << medium_price;
	f.seekp(77 * num + 65);
	f << right << setw(10) << large_price;

	fstream fin("sales.txt", ios::in | ios::out);
	fin.seekp(102 * num + 5);
	fin << left << setw(30) << name;
	fin.seekp(102 * num + 50);
	fin << right << setw(10) << small_price;
	fin.seekp(102 * num + 60);
	fin << right << setw(10) << medium_price;
	fin.seekp(102 * num + 70);
	fin << right << setw(10) << large_price;
	cout << "Data has been successfully added ";

	f.close();
	fin.close();
	system("pause");
	system("cls");
}

void update_products()
{
	int quantity, small_price, medium_price, large_price, update;
	char name[52], name2[52], input;
	display_products();
	cout << "Enter the record number to update: ";
	update = getinput();

	fstream f("products.txt", ios::in | ios::out);
	fstream fin("sales.txt", ios::in | ios::out);
	f.seekg(77 * update + 5);
	f.read(name2, 30);
	if (strncmp(name2, "                             ", 29) != 0)
	{
		cout << "Enter Q to edit quantity, P to edit price or N to edit name " << endl;
		cin >> input;

		if (input == 'q' || input == 'Q')
		{
			cout << "Enter the quantity:";
			quantity = getinput();
			f.seekp(77 * update + 35);
			f << left << setw(10) << quantity;
		}
		else if (input == 'P' || input == 'p')
		{
			cout << "Enter the small price:";
			small_price = getinput();
			f.seekp(77 * update + 45);
			f << right << setw(10) << small_price;
			fin.seekp(102 * update + 50);
			fin << right << setw(10) << small_price;

			cout << "Enter the medium price:";
			medium_price = getinput();
			f.seekp(77 * update + 55);
			f << right << setw(10) << medium_price;
			fin.seekp(102 * update + 60);
			fin << right << setw(10) << medium_price;

			cout << "Enter the large price:";
			large_price = getinput();
			f.seekp(77 * update + 65);
			f << right << setw(10) << large_price;
			fin.seekp(102 * update + 70);
			fin << right << setw(10) << large_price;
		}
		else if (input == 'N' || input == 'n')
		{
			cout << "Enter the item name: ";
			cin.ignore();
			cin.getline(name, 77);

			f.seekp(77 * update + 5);
			f << left << setw(30) << name;
			fin.seekp(102 * update + 5);
			fin << left << setw(30) << name;
		}
	}
	else
	{
		cout << "No data exists at num " << update << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "Data has been successfully updated ";
	f.close();
	fin.close();
	system("pause");
	system("cls");
}

void update_sales()
{
	int quantity, small_price, medium_price, large_price, update;
	char name[102], name2[102], input;
	display_sales();
	cout << "Enter the record number to update: ";
	update = getinput();

	fstream fin("sales.txt", ios::in | ios::out);
	fin.seekg(102 * update + 5);
	fin.read(name2, 30);
	if (strncmp(name2, "                             ", 29) != 0)
	{
		cout << "Enter Q to edit quantity, P to edit price or N to edit name " << endl;
		cin >> input;

		if (input == 'q' || input == 'Q')
		{
			cout << "Enter the quantity:";
			quantity = getinput();
			fin.seekp(102 * update + 35);
			fin << left << setw(10) << quantity;
		}
		else if (input == 'P' || input == 'p')
		{
			cout << "Enter the small price:";
			small_price = getinput();
			fin.seekp(102 * update + 50);
			fin << right << setw(10) << small_price;

			cout << "Enter the medium price:";
			medium_price = getinput();
			fin.seekp(102 * update + 60);
			fin << right << setw(10) << medium_price;

			cout << "Enter the large price:";
			large_price = getinput();
			fin.seekp(102 * update + 70);
			fin << right << setw(10) << large_price;
		}
		else if (input == 'N' || input == 'n')
		{
			cout << "Enter the item name: ";
			cin.ignore();
			cin.getline(name, 102);

			fin.seekp(102 * update + 5);
			fin << left << setw(30) << name;
		}
	}
	else
	{
		cout << "No data exists at num " << update << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "Data has been successfully updated ";
	fin.close();
	system("pause");
	system("cls");
}

void del()
{
	int del;
	char input;
	display_products();
	cout << "Are you sure you want to delete a record(Press Y for yes): ";
	cin >> input;
	if (input != 'Y' || input != 'y')

		return;

	cout << "Enter the item number which you want to delete: ";
	del = getinput();
	fstream f("products.txt", ios::in | ios::out);
	f.seekp(77 * del + 5);
	f << left << setw(30) << "";
	f.seekp(77 * del + 35);
	f << left << setw(10) << 0;
	f.seekp(77 * del + 45);
	f << right << setw(10) << 0;
	f.seekp(77 * del + 55);
	f << right << setw(10) << 0;
	f.seekp(77 * del + 65);
	f << right << setw(10) << 0;

	fstream f1("sales.txt", ios::in | ios::out);
	f1.seekp(102 * del + 5);
	f1 << left << setw(30) << "";
	f1.seekp(102 * del + 35);
	f1 << left << setw(15) << 0;
	f1.seekp(102 * del + 50);
	f1 << right << setw(10) << 0;
	f1.seekp(102 * del + 60);
	f1 << right << setw(10) << 0;
	f1.seekp(102 * del + 70);
	f1 << right << setw(10) << 0;
	f1.seekp(102 * del + 80);
	f1 << right << setw(20) << 0;


	cout << "data has been successfully deleted " << endl;
	f.close();
	f1.close();
	system("pause");
	system("cls");
}

void buy()
{
	int num, quantity, price, total;
	int small_price, medium_price, large_price;
	int tempquantity, revenue, sales_quantity;
	char size, item_name[30];
	string user_name;

	display_products();
	fstream fin("products.txt", ios::in | ios::out);
	fstream f("sales.txt", ios::in | ios::out);
	ofstream fout("names.txt", ios::app);
	cout << "Enter your name:";
	cin.ignore();
	getline(cin, user_name);



	while (true)
	{
		cout << "Enter the product number: ";
		num = getinput();
		fin.seekg(77 * num + 5);
		fin.get(item_name, 30);

		if (strncmp(item_name, "                              ", 29) != 0)
		{
			while (true)
			{
				cout << "Enter the size(S,M or L): ";
				cin >> size;
				if (size == 's' || size == 'S')
				{
					fin.seekg(77 * num + 45);
					fin >> small_price;
					price = small_price;
					break;
				}
				else if (size == 'm' || size == 'M')
				{
					fin.seekg(77 * num + 55);
					fin >> medium_price;
					price = medium_price;
					break;
				}
				else if (size == 'L' || size == 'l')
				{
					fin.seekg(77 * num + 65);
					fin >> large_price;
					price = large_price;
					break;
				}
				else
				{
					cout << "Enter a valid character" << endl;
				}
			}
			while (true)
			{
				cout << "Enter the quantity: ";
				quantity = getinput();

				fin.seekg(77 * num + 35);
				fin >> tempquantity;

				if (quantity > tempquantity)
				{
					cout << "Enter a valid quantity" << endl;
				}
				else
					break;
			}
		}
		else
		{
			cout << "Enter a valid input" << endl;
			continue;
		}
		break;
	}

	f.seekg(102 * num + 35);
	f >> sales_quantity;
	f.seekg(102 * num + 80);
	f >> revenue;

	sales_quantity = sales_quantity + quantity;
	tempquantity = tempquantity - quantity;
	total = price * quantity;
	revenue = revenue + total;

	fin.seekp(77 * num + 35);
	fin << left << setw(10) << tempquantity;

	f.seekp(102 * num + 5);
	f << left << setw(30) << item_name;
	f.seekp(102 * num + 35);
	f << left << setw(15) << sales_quantity;
	f.seekp(102 * num + 80);
	f << right << setw(20) << revenue;

	fout << left << setw(30) << user_name
		<< left << setw(30) << item_name
		<< right << setw(10) << quantity << endl;

	cout << endl
		<< "Name:" << user_name << endl
		<< "Total:RS " << total << endl
		<< "Tax: 15%" << endl
		<< "Net total:RS " << total + (0.15 * total) << endl;
	fin.close();
	f.close();
	fout.close();

}

void reset_sales()
{
	char erase_sales;
	cout << "ARE YOU SURE YOU WANT TO ERASE ALL THE DATA?(Enter Y for yes or N for no): ";
	cin >> erase_sales;
	if (erase_sales == 'Y' || erase_sales == 'y')
	{
		ofstream fout("sales.txt");;
		fout << left << setw(5) << "Name"
			<< left << setw(30) << "Item Name"
			<< left << setw(15) << "Items Sold"
			<< right << setw(10) << "Small"
			<< right << setw(10) << "Medium"
			<< right << setw(10) << "Large"
			<< right << setw(20) << "Revenue Generated" << endl;

		for (int i = 1; i < 20; i++)
		{

			fout << left << setw(5) << i;
			fout << left << setw(30) << "";
			fout << left << setw(15) << 0;
			fout << right << setw(10) << 0;
			fout << right << setw(10) << 0;
			fout << right << setw(10) << 0;
			fout << right << setw(20) << 0 << endl;

		}
		fout.close();
		cout << "All tha data has been reset " << endl;
	}
	else
	{
		cout << "No data has been reset" << endl;
		system("pause");
		system("cls");
		return;
	}
	system("pause");
	system("cls");
}

void reset_products()
{
	char erase_products;
	cout << "ARE YOU SURE YOU WANT TO ERASE ALL THE DATA?(Enter Y for yes or N for no): ";
	cin >> erase_products;
	if (erase_products == 'Y' || erase_products == 'y')
	{
		ofstream fout("products.txt");
		fout << left << setw(5) << "Name"
			<< left << setw(30) << "Item Name"
			<< left << setw(10) << "In Stock"
			<< right << setw(10) << "Small"
			<< right << setw(10) << "Medium"
			<< right << setw(10) << "Large" << endl;

		for (int i = 1; i < 20; i++)
		{
			fout << left << setw(5) << i;
			fout << left << setw(30) << "";
			fout << left << setw(10) << 0;
			fout << right << setw(10) << 0;
			fout << right << setw(10) << 0;
			fout << right << setw(10) << 0 << endl;
		}
		fout.close();
		cout << "All the data has been reset " << endl;
	}
	else
	{
		cout << "No data has been reset" << endl;
		system("pause");
		system("cls");
		return;
	}
	system("pause");
	system("cls");
}

void copy_data()
{
	char character, product_name[30], sale_name[30];
	int product_small, product_medium, product_large;
	int sale_small, sale_medium, sale_large;
	cout << "Press P to copy products name to sale file or pess S to copy products name to products file :" << endl;
	cin >> character;

	fstream fin("products.txt", ios::in | ios::out);
	fstream fout("sales.txt", ios::in | ios::out);

	if (character == 'P' || character == 'p')
	{

		for (int i = 1; i < 19; i++)
		{
			fin.seekg(77 * i + 5);
			fin.get(product_name, 30);
			fin.seekg(77 * i + 45);
			fin >> product_small;
			fin.seekg(77 * i + 55);
			fin >> product_medium;
			fin.seekg(77 * i + 65);
			fin >> product_large;
			fout.seekp(102 * i + 5);
			fout << left << setw(30) << product_name;
			fout.seekp(102 * i + 50);
			fout << right << setw(10) << product_small;
			fout.seekp(102 * i + 60);
			fout << right << setw(10) << product_medium;
			fout.seekp(102 * i + 70);
			fout << right << setw(10) << product_large;
		}
	}

	else if (character == 'S' || character == 's')
	{
		for (int i = 1; i < 19; i++)
		{
			fout.seekg(102 * i + 5);
			fout.get(sale_name, 30);
			fout.seekg(102 * i + 50);
			fout >> sale_small;
			fout.seekg(102 * i + 60);
			fout >> sale_medium;
			fout.seekg(102 * i + 70);
			fout >> sale_large;
			fin.seekp(77 * i + 5);
			fin << left << setw(30) << sale_name;
			fin.seekp(77 * i + 45);
			fin << right << setw(10) << sale_small;
			fin.seekp(77 * i + 55);
			fin << right << setw(10) << sale_medium;
			fin.seekp(77 * i + 65);
			fin << right << setw(10) << sale_large;
		}
	}
	else
	{
		cout << "No data has been copied " << endl;
		system("pause");
		system("cls");
		return;
	}
	fin.close();
	fout.close();
	cout << "All the products name and unit price has been successfully copied" << endl;
	system("pause");
	system("cls");
}

int getinput()
{
	int number = 0;
	while (number < 1)
	{
		if (!(cin >> number))
		{
			cout << "Incorrect input. Please try again" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		if (number <= 0)
			cout << "Enter a Valid number " << endl;
	}
	return number;
}

void setup_names()
{
	char input;
	cout << "Do you want to reset all the data?(press Y for yes ,press any key to exist): ";
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		ofstream fout("names.txt");
		fout << left << setw(30) << "Name"
			<< left << setw(30) << "Item name"
			<< left << setw(10) << "Amount" << endl;
		cout << "data has been successfully reset" << endl;
	}
	else
		cout << "No data has been reset" << endl;
	system("pause");
	system("cls");
}

void display_names()
{
	cout << "Log of all the customers" << endl;
	char data[72];
	ifstream fin("names.txt");
	while (!fin.eof())
	{
		fin.getline(data, 72);
		cout << data << endl;
	}
	fin.close();
	system("pause");
	system("cls");

}

void total_sales()
{
	int revenue,i = 1,sum=0;
	
	fstream fin("sales.txt", ios:: in || ios::out);
	
	while (!fin.eof())
	{
		fin.seekg(102 * i + 80);
		fin >> revenue;
		sum = sum + revenue;
		i++;
	}
	cout << "Total Sales are:RS " << sum << endl;
	fin.close();
}

void item()
{
	int quantity, max=0;
	char item_name[30];
	string max_item;
	
	fstream fin("sales.txt", ios::in || ios::out);

	for(int i=1;i<20;i++)
	{
		fin.seekg(102 * i + 5);
		fin.get(item_name, 30);
		fin.seekg(102 * i + 35);
		fin >> quantity;
		if (quantity > max)
		{
			max = quantity;
			max_item = item_name;
		}
	}
	cout << "With " << max << " number of times, the most sold item is " << max_item << endl;
	fin.close();
}


