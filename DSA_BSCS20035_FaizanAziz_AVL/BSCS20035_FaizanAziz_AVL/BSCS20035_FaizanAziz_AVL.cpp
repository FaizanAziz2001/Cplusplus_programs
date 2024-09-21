
#include <iostream>
#include"AVL.h"
using namespace std;
int main()
{
    AVL T;
    //T.Insert(5);
    //T.Insert(10);
    //T.Insert(15);
    //T.Insert(2);
    //T.Insert(20);
    //T.Insert(-5);
    //T.Insert(-3);
    //T.Insert(7);

   /* T.Insert(60);
    T.Insert(70);
    T.Insert(50);
    T.Insert(49);
    T.Insert(51);*/

    //T.Output_Tree();
    //T.Insert(55);
    //cout << endl << endl;
    //T.Output_Tree();


   
    int input;
    while (true)
    {
        cout << "->";
        cin >> input;
        if (input == -1)
        {
            cin >> input;
            T.Deletion(input);
        }
        else
        {

            T.Insert(input);
        }
        cout << endl;
        T.Output_Tree(); cout << endl<<endl;
           
    }
}

