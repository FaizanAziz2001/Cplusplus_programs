#include<fstream>
#include <iostream>
using namespace std;

struct DynamicArray 
{
    int* Vs;
    int S;
};

void Regrow(DynamicArray& DA, int Newsize)
{
    
    int* TA = new int[DA.S + 1];
    for (int i = 0; i < DA.S; i++)
    {
        TA[i] = DA.Vs[i];
    }

    delete[]DA.Vs;

    TA[DA.S] = Newsize;
    DA.Vs = TA;
    DA.S++;

}

void InsertInSortedArray(DynamicArray& DA, int i, int Val)
{
    
    
    int* TA = new int[DA.S + 1];
    for (int i = 0; i < DA.S; i++)
    {
        TA[i] = DA.Vs[i];
    }
    delete[]DA.Vs;
    TA[i] = Val;
    DA.Vs = TA;
    for (int si = i; i >= 1; i--)
    {
        if (DA.Vs[i - 1] > DA.Vs[i])
            swap(DA.Vs[i - 1], DA.Vs[i]);
    }

    DA.S++;
}

void LoadData(DynamicArray& DA,string name)
{
    ifstream fin(name);
    int d;
    do
    {
        fin >> d;
        if (d != -1)
        {
            Regrow(DA, d);
        }
    } while (d != -1);
}

void LoadData_Task4(DynamicArray& DA)
{
    ifstream fin("Task4 input.txt");

    int d,i=0;
    do
    {
        fin >> d;
        if (d != -1)
        {
            InsertInSortedArray(DA, i, d);
            i++;
        }
    } while (d != -1);
}

void init(DynamicArray& DA,ifstream& fin)
{
    int d;
    do
    {
        fin >> d;
        if (d != -1)
        {
            Regrow(DA, d);
        }
    } while (d != -1);
}

void PrintData(DynamicArray& DA)
{
    for (int i = 0; i < DA.S; i++)
    {
        cout << DA.Vs[i] << " ";
    }
}

void PrintDataWithAstericks(DynamicArray& DA)
{
    for (int i = 0; i < DA.S; i++)
    {
        cout << *(DA.Vs+i) << " ";
    }
}

int Frequency(DynamicArray DA,int T)
{
    int count = 0;
    for (int i = 0; i < DA.S; i++)
    {
        if (DA.Vs[i] == T)
            count++;
    }
    return count;
}

void FindUniqueElements(DynamicArray& DA, DynamicArray& UDA)
{
    for (int i = 0; i < DA.S; i++)
    {
        if (Frequency(DA, DA.Vs[i]) == 1)
        {
            Regrow(UDA, DA.Vs[i]);
        }
    }    
}

void FindUniqueElementsWithAstericks(DynamicArray& DA, DynamicArray& UDA)
{
  
    for (int i = 0; i < DA.S; i++)
    {
        if (Frequency(DA, *(DA.Vs+i)) == 1)
        {
            Regrow( UDA,*(DA.Vs+i));
           
        }
    }
}

void SortinAsc(DynamicArray& DA, int si, int ei)
{
    for (int i = si; i < ei; i++)
    {
        for (int i = 0; i + 1 < ei; i++)
        {
            if (DA.Vs[i] > DA.Vs[i + 1])
                swap(DA.Vs[i], DA.Vs[i + 1]);
        }
    }
}

void SortinDsc(DynamicArray& DA, int si, int ei)
{
    for (int i = si; i < ei; i++)
    {
        for (int i = 0; i + 1 < ei; i++)
        {
            if (DA.Vs[i] < DA.Vs[i + 1])
                swap(DA.Vs[i], DA.Vs[i + 1]);
        }
    }
}

void SortinAscWithAstericks(DynamicArray& DA, int si, int ei)
{
    for (int i = si; i < ei; i++)
    {
        for (int i = 0; i + 1 < ei; i++)
        {
            if (*(DA.Vs+i) > *(DA.Vs+i + 1))
                swap(*(DA.Vs+i), *(DA.Vs+i+1));
        }
    }
}

void SortinDscWithAstericks(DynamicArray& DA, int si, int ei)
{
    for (int i = si; i < ei; i++)
    {
        for (int i = 0; i + 1 < ei; i++)
        {
            if (*(DA.Vs + i) < *(DA.Vs + i + 1))
                swap(*(DA.Vs + i), *(DA.Vs + i + 1));
        }
    }
}

DynamicArray DynamicArrayMerge(const DynamicArray const& DA1, const DynamicArray const& DA2)
{
    DynamicArray DA3{ 0 };
    DA3.S = DA1.S + DA2.S;
    int* TA = new int[DA3.S];

    for (int k = 0, i = 0, j = 0; i < DA1.S || j < DA2.S; k++)
    {
        if (j>=DA2.S || (i < DA1.S && DA1.Vs[i] <= DA2.Vs[j]))
        {
            TA[k] = DA1.Vs[i];
            i++;
        }
        else
        {
            TA[k] = DA2.Vs[j];
            j++;
        }
    }
    DA3.Vs = TA;
    return DA3;
}

void task1()
{
    string name = "Task1 input.txt";
    DynamicArray DA{ 0 };
    LoadData(DA,name);
    PrintData(DA);

    delete[] DA.Vs;

}

void task2A()
{
    string name = "Task2 input.txt";
    DynamicArray DA{ 0 }, UDA{ 0 };
    LoadData(DA,name);

    cout << "Input array: " << endl;

    PrintData(DA);
    FindUniqueElements(DA, UDA);
    SortinDsc(UDA, 0,UDA.S - UDA.S/2);
    SortinAsc(UDA, UDA.S/2 + 1,UDA.S / 2);

    cout << endl;
    cout << "Output Array: " << endl;
    PrintData(UDA);
    delete[] UDA.Vs;
    delete[] DA.Vs;
}

void task2B()
{
    DynamicArray DA{ 0 }, UDA{ 0 };
    string name = "Task2 input.txt";
    LoadData(DA,name);

    FindUniqueElementsWithAstericks(DA, UDA);
    SortinDscWithAstericks(UDA, 0, UDA.S - UDA.S / 2);
    SortinAscWithAstericks(UDA, UDA.S / 2 + 1, UDA.S / 2);

    PrintDataWithAstericks(UDA);
    delete[] UDA.Vs;
    delete[] DA.Vs;
}

void task3()
{
    ifstream fin("Task3 input.txt");
    DynamicArray DA1{ 0 }, DA2{ 0 },DA3;
    init(DA1, fin);
    init(DA2, fin);

    cout << "Input array: " << endl;
    PrintData(DA1); cout << endl;
    PrintData(DA2);
    DA3 = DynamicArrayMerge(DA1, DA2);

    cout << endl;
    cout << "Output Array: " << endl;
    PrintData(DA3);
    delete[] DA3.Vs;
    delete[] DA2.Vs;
    delete[] DA1.Vs;
}

void task4()
{
    DynamicArray DA{ 0 };
    LoadData_Task4(DA);
    PrintData(DA);
    delete[] DA.Vs;
}

void menu()
{
    system("cls");
    cout << "1. Configuration of Dynamic Array" << endl
        << "2. Find unique elements and sort Dynamic Array" << endl
        << "3. Merge and sort Dynamic Array" << endl
        << "4. Insert in sorted sub array " << endl;
}

int main()
{
    int choice;
    char cont;
    do
    {
        menu();
        cout << "Enter a task number: ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            task1();
            break;
        case 2:
            task2A();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        }
        cout << endl << endl;
        cout << "Do you want to continue?(Y for yes)";
        cin >> cont;
    } while (cont == 'Y' || cont == 'y');

    return 0;
}

