#include <iostream>
#include<list>
#include"GraphAjd_List.h"
#include"GraphAjd_matrix.h"
using namespace std;

void printlist(vector<list<int>> result)
{
    cout << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << i << ": ";
        for (auto itr : result[i])
        {
            cout << itr << " ";
        }
        cout << endl;
    }

}

int main()
{
    GraphAjd_List m(6, true);
    //GraphAjd_matrix m(10, true);
    cout << endl;
    m.addedge(0, 1);
    m.addedge(0, 3);
    m.addedge(1, 3);
    m.addedge(2, 3);
    m.addedge(4, 5);


 

    m.print_graph();
    cout << endl;


    auto trans=m.transpose();
    printlist(trans);

  /*  cout << m.is_graphdag(); cout << endl;*/
    auto result = m.inverse();
    m.assign_cnn();


    auto result2 = m.get_cnn(0);

    cout << result2;
    cout << endl;


    result2 = m.get_cnn(3);

    cout << result2;
    cout << endl;
    return 0;


}

