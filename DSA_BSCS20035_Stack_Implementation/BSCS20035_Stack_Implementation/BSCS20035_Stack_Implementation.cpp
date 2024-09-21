
#include <iostream>
#include "S_Stack.h"
#include"Queue.h"
using namespace std;

int main()
{
	Queue<int> Q(5);
	int x = 10;
	int x1 = 20;
	Q.Enqueue(x);
	cout << Q.IsEmpty() << endl;
	x++;
	Q.Enqueue(x);
	x++;
	Q.Dequeue();
	Q.Enqueue(x);
	x++;

	Q.Enqueue(x);
	x++;
	Q.Enqueue(x);
	x++;
	Q.Enqueue(x);
	x++;
	Q.Enqueue(x);
	x++;
	cout << Q.IsFull();
	 Q.Front(x1);
	 cout << x1;
	 Q.Back(x1);
	 cout << x1;
	Q.Dequeue();
	Q.Dequeue();
	Q.Dequeue();
	Q.Enqueue(x);
	Q.Dequeue();
	Q.Dequeue();
	
	Q.Dequeue();



}
