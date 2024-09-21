
#include <iostream>
#include"S_Queue.h"
#include"D_Queue.h"
using namespace std;

int main()
{
    D_Queue<int> Q(3);
    cout << Q.Empty()<<endl;
    Q.Enqueue(1);
        Q.Enqueue(2);
        Q.Enqueue(3);
    cout << Q.Dequeue() << endl;
    Q.Enqueue(4);
    Q.Enqueue(5);
    Q.Enqueue(6);
    cout << Q.Full();
    cout << Q.Front();
}
