#include <iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<string>
#include <time.h>
#include <chrono>

using namespace std;

struct Fval
{
	ifstream Rdr;
	int val;
};

struct Comp
{
	bool operator()(const Fval* File1, const Fval* File)
	{
		return File1->val > File->val;
	}
};

#pragma region 
vector<int> Merge(vector<int>& A, vector<int>& B)
{
	vector<int>C(A.size() + B.size());
	for (int i = 0, j = 0, k = 0; k < C.size(); k++)
	{
		if (i == A.size())
			C[k] = B[j++];
		else if (j == B.size())
			C[k] = A[i++];
		else if (A[i] < B[j])
			C[k] = A[i++];
		else
			C[k] = B[j++];
	}

	return C;
}

void MergeSort(vector<int>& D)
{
	if (D.size() < 2)
		return;
	vector<int> L(D.begin(), D.begin() + D.size() / 2);
	vector<int> R(D.begin() + D.size() / 2, D.end());
	MergeSort(L);
	MergeSort(R);
	D = Merge(L, R);
}
#pragma endregion mergesort

#pragma region
int Partition(vector<int>& D, int si, int ei)
{
	int pivot = ei;
	int pi = si - 1;

	for (int i = si; i < ei; i++)
	{
		if (D[i] <= D[pivot])
		{
			pi++;
			swap(D[pi], D[i]);

		}
	}
	swap(D[pi + 1], D[pivot]);
	return (pi + 1);
}

void QS(vector<int>& D, int si, int ei)
{

	if (si >= ei)
		return;
	
		int Pi = Partition(D, si, ei);
		QS(D, si, Pi - 1);
		QS(D, Pi + 1, ei);
	
}

void Quick_Sort(vector<int>& D)
{
	QS(D, 0, D.size() - 1);
}
#pragma endregion quicksort

#pragma region
void Heap_sort(vector<int>& D)
{
	priority_queue <int, vector<int>, greater<int> > pq;
	for (int i = 0; i < D.size(); i++)
	{
		pq.push(D[i]);
	}

	D.clear();
	while (!pq.empty())
	{
		D.push_back(pq.top());
		pq.pop();
	}

}
#pragma endregion heapsort

#pragma region
bool SwappingAllTheWay(vector<int>& D)
{
	bool Change_Happen = false;
	for (int i = 0; i + 1 < D.size(); i++)
	{
		if (D[i] > D[i + 1])
		{
			swap(D[i], D[i + 1]);
			Change_Happen = true;
		}
	}

	return Change_Happen;
}

void BubbleSort(vector<int>& D)
{
	while (SwappingAllTheWay(D))
	{

	}
}
#pragma endregion bubblesort

#pragma region
int MinInRange(vector<int>& D, int si, int ei)
{
	int min = si;
	for (int i = si + 1; i < ei; i++)
	{
		if (D[i] < D[min])
			min = i;
	}

	return min;
}

void SelectionSort(vector<int>& D)
{
	for (int i = 0; i < D.size(); i++)
	{
		int min = MinInRange(D, i, D.size());
		swap(D[min], D[i]);
	}
}
#pragma endregion selection sort

#pragma region 
void HelperFile(vector<int>& D, string& path)
{
	ofstream fout(path);
	MergeSort(D);
	for (int k = 0; k < D.size(); k++)
	{
		fout << D[k] << endl;
	}
	path.clear();
	D.clear();
	fout.close();
}

void DiskLoad(string name, int NOF, int size)
{
	vector<int> D;
	ifstream fin(name);
	string input;

	for (int j = 1; j <= NOF; j++)
	{
		string path = std::to_string(j) + "File.txt";

		for (int i = 0; i < size; i++)
		{
			fin >> input;
			int num = std::stoi(input);
			D.push_back(num);
		}

		HelperFile(D, path);
	}
}

void DiskMerge(string name, int NOF)
{
	priority_queue <Fval*, vector<Fval*>, Comp> pq;
	string input;

	for (int i = 0; i < NOF; i++)
	{
		string path = std::to_string(i + 1) + "File.txt";
		Fval* Files = new Fval();
		Files->Rdr.open(path);
		Files->Rdr >> Files->val;

		pq.push(Files);
	}

	ofstream fout(name);
	while (!pq.empty())
	{
		fout << pq.top()->val << endl;
		auto temp = pq.top();
		pq.pop();
		temp->Rdr >> temp->val;
		if (!temp->Rdr.eof())
		{
			pq.push(temp);
		}

	}
}

void DiskSort(string name)
{

	int NOF = 3;
	int size = 3 * 1024 * 1024;
	DiskLoad(name, NOF, size / 3);			//Assume 1Kb=3000 bytes
	DiskMerge("DiskSorted.txt", NOF);
}
#pragma endregion disksort

void Random_init(vector<int>& D)
{
	srand(time(0));
	for (int i = 0; i < D.size(); i++)
	{
		D[i] = rand() % 100;
	}
}

void WriteFileGB()
{
	ofstream fout("Save.txt");
	int GB = 1024 * 1024 * 1024;
	for (long long i = 0; i < GB; i++)
	{
		fout << rand() % 100 << endl;
	}
}

void WriteFileMB(long long size, string name)
{
	srand(0);
	ofstream fout(name);
	long long MB = (1024 * 1024) / 3;
	for (long long i = 0; i < size * MB; i++)
	{
		fout << rand() % 10 << endl;
	}
}

void WriteFileKB(long long size, string name)
{
	srand(0);

	ofstream fout;

	fout.open(name);
	long long KB = 1024;
	for (long long i = 0; i < size * KB; i++)
	{
		fout << rand() % 10 << endl;
	}
	fout.close();
}

void Read_file(vector<int>& D, string name)
{
	ifstream fin(name);	//Read the file
	string v;
	int num;
	while (fin)
	{
		fin >> v;
		if (fin.eof())
			break;

		num = std::stoi(v);
		D.push_back(num);
	}
}

ostream& operator<<(ostream& cout, vector<int>D)
{
	for (int i = 0; i < D.size(); i++)
	{
		cout << D[i] << " ";
	}
	cout << endl;
	return cout;
}

int main()
{

	//DiskSort("DiskSort.txt");
	//return 0;

	vector<int> D;

	int choice;
	while (true)
	{

		Read_file(D, "Sort.txt");
		cout << "Enter number: ";
		cin >> choice;
		cout << endl;

		auto start = chrono::steady_clock::now();
		switch (choice)
		{

		case 1:
			cout << "Quick Sort Time: ";
			/*Quick_Sort(D);*/
			sort(D.begin(), D.end());
			break;
		case 2:
			cout << "Merge Sort Time: ";
			MergeSort(D);
			break;
		case 3:
			cout << "Heap Sort Time: ";
			Heap_sort(D);
			break;
		case 4:
			cout << "Bubble Sort Time: ";
			BubbleSort(D);
			break;
		case 5:
			cout << "Selection Sort Time: ";
			SelectionSort(D);
			break;
		}

		auto stop = chrono::steady_clock::now();
		auto diff = stop - start;
		cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / (1000 * 60) << " min" << endl;
		cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
		cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;
		D.clear();
	}

}




