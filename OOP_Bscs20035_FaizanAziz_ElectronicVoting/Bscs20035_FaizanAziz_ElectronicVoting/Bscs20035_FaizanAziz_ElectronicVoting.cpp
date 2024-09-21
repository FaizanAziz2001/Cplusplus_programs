
#include <iostream>
#include<fstream>
using namespace std;

void readingfile(string name[], int data[], int& size, int DA[], int& Dsize)
{
    ifstream fin("Votes.txt");

    fin >> Dsize;
    for (int i = 0; i < Dsize; i++)
    {
        fin >> name[i];
    }

    fin >> size;
    for (int i = 0; i < size; i++)
    {
        fin >> data[i];
    }
}

int max(int FS[], int Dsize)
{
    int max = FS[0];
    int max_index = 0;
    for (int i = 1; i < Dsize; i++)
    {
        if (FS[i] > max)
        {
            max = FS[i];
            max_index = i;
        }
    }
    return max_index;
}
int frequency(int data[], int size, int temp)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (data[i] == temp)
            count++;
    }
    return count++;
}

void printarray(int data[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
}

bool Ispresent(int DA[], int Dsize, int temp)
{
    for (int i = 0; i < Dsize; i++)
    {
        if (DA[i] == temp)
            return true;
    }
    return false;
}

void distinct_values(int data[], int DA[], int size)
{
    int x = 0;
    for (int i = 0; i < size; i++)
    {
        if (!Ispresent(DA, size, data[i]))
        {
            DA[x] = data[i];
            x++;
        }
    }
}

void Calculateall_frequency(int data[],int DA[],int Dsize, int size,int FS[])
{
    for (int i = 0; i < Dsize; i++)
    {
        FS[i] = frequency(data, size, DA[i]);
    }
}

void sortBydistict(int DA[], int Dsize, int FS[])
{
    for (int i = 0; i < Dsize; i++)
    {
        for (int i = 0; i+1 < Dsize; i++)
        {
            if (DA[i] > DA[i + 1])
            {
                swap(DA[i + 1], DA[i]);
                swap(FS[i + 1], FS[i]);

            }
        }
    }
}

void printall(string name[],int DA[],int Dsize,int FS[])
{
    char ch = -37;
    cout << "Partyname      " << " VoteID" << '\t' << '\t' << "Votes" << endl;
    for (int i = 0; i < Dsize; i++)
    {
        cout << name[i] << '\t' << '\t' << DA[i] << '\t' << '\t' << FS[i] << endl;
    }
    cout << endl;

    int index = max(FS, Dsize);
    cout << name[index] << " won the elections with " << FS[index] << " votes " << endl << endl;

    cout << "Partyname      "  << '\t' << "Votes"  << '\t' << "Graph" << endl;
    for (int i = 0; i < Dsize; i++)
    {
        cout << name[i] << '\t' << '\t' << FS[i] << '\t' ;
        for (int j = 0; j < FS[i]; j++)
        {
            cout << ch;
        }
        cout << endl << endl ;
    }
}

int main()
{
    const int capacity = 100;
    string partynames[capacity];
    int data[capacity],size, DA[capacity],Dsize, FS[capacity];

    readingfile(partynames, data, size, DA, Dsize);
    distinct_values(data, DA, size);

    Calculateall_frequency(data,DA,Dsize, size,FS);
   
    sortBydistict(DA, Dsize, FS);
    printall(partynames, DA, Dsize, FS);
}
