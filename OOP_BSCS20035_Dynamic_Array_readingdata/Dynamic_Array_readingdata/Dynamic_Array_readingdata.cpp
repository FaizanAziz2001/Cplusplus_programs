

#include"vector.h"
#include"ArrayList.h"
#include"AutoGrowingArray.h"
#include<string>
using namespace std;



void Generate_file(string fname, int size)
{
	srand(time(0));		// Generate a file of 1 mb
	ofstream fout(fname);
	for (int i = 0; i < size * 1024 * 1024; i++)
	{
		fout << rand() % 10;
	}
}


void task1(int size)
{
	Vector<int> data;
	ofstream fout("OutputVector.txt");
	auto start = chrono::steady_clock::now();
	data.Read_file("Ds.txt");
	auto stop = chrono::steady_clock::now();

	auto diff = stop - start;
	/*cout << data << endl;*/
	cout << "For a " << size << "MB file: " << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "For a " << size << "MB file: " << endl;
	cout << "Number of operations: " << N_vector <<endl;
	fout << "Number of operations: " << N_vector << endl;
}

void task2(int size)
{
	ArrayList<int> data;
	ofstream fout("OutputArrayList.txt");
	auto start = chrono::steady_clock::now();
	data.Read_file("Ds.txt");
	auto stop = chrono::steady_clock::now();


	auto diff = stop - start;
	/*cout << data << endl;*/
	cout << "For a " << size << "MB file: " << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "For a " << size << "MB file: " << endl;
	cout << "Number of operations: " << N_arraylist << endl;
	fout << "Number of operations: " << N_arraylist << endl;
}

void task3(int size)
{
	AutoGrowingArray<int> data;
	ofstream fout("OutputGA.txt");
	auto start = chrono::steady_clock::now();
	data.Read_file("Ds.txt");
	auto stop = chrono::steady_clock::now();


	auto diff = stop - start;
	/*cout << data << endl;*/
	cout << "For a " << size << "MB file: " << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "For a " << size << "MB file: " << endl;
	cout << "Number of operations: " << N_grow << endl;

}
int main()
{
	int choice;
	int size = 2;
	Generate_file("Ds.txt", size);
	do
	{
		cout << "1. Vector \n"
			<< "2. ArrayList \n"
			<< "3. Growable array" << endl;
		cin >> choice;
		if (choice == 1)
			task1(size);
		else if (choice == 2)
			task2(size);
		else if (choice == 3)
			task3(size);
		else
			break;
		cout << endl;
	}while(true);
	
	
	return 0;
	
}
