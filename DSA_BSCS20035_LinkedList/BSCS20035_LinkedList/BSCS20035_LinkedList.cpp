
#include <iostream>
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
using namespace std;

int main()
{
	LinkedList<int> S;
	S.InsertAtTail(5);
	S.InsertAtTail(26);
	S.InsertAtTail(15);
	S.InsertAtTail(10);
	S.InsertAtMid(100);
	S.InsertAtMid(44);
	S.InsertAtFront(48);
	S.Print();
	S.InsertBeforeAt(48, 9999);
	S.Print();
	S.InsertAfterAt(10, 9999);
	S.Print();
	S.Remove_Range(10,100);
	S.Print();
	
}

