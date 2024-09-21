
#include <iostream>
using namespace std;

//Circular Queue
class MyCircularQueue {
    private:
    int front;
	int rear;
	int capacity;
	int* Ds;

public:
    MyCircularQueue(int c=1) {
        capacity = c;
		front = -1;
		rear = -1;
		Ds = new int[capacity];

    }
    
    bool enQueue(int value) {
        if (isFull())
			return false;
		else if (isEmpty())
		{
			front = 0;
			rear = 0;
		}
		else
			rear=(rear+1)%capacity;


		Ds[rear] = value;
		return true;

    }
    
    bool deQueue() {
        if (isEmpty())
			return false;
		else if (front == rear)
		{
			front = -1, rear = -1;
			return true;
		}
		else
			front=(front+1)%capacity;
		return true;
    }
    
    int Front() {
        if (isEmpty())
			return -1;
		return Ds[front];
    }
    
    int Rear() {
        if (isEmpty())
			return -1;
		return Ds[rear];
    }
    
    bool isEmpty() {
        		return (rear == -1 && front == -1);
    }
    
    bool isFull() {
        	return (rear+1)%capacity == front;
    }
};

//Circular Deque
class MyCircularDeque {
    private:
    int front,rear,size,capacity;
    int* Ds;
public:
    MyCircularDeque(int k) {
        front=rear=size=0;
        capacity=k;
        Ds=new int[capacity];
    }
    
    bool insertFront(int value) {
        if(isFull())
            return false;
        if(front==0)
            front=capacity-1;
        else
            front--;
        Ds[front]=value;
        size++;
        return true;
        
    }
    
    bool insertLast(int value) {
        if(isFull())
            return false;
        Ds[rear]=value;
        rear=(rear+1)%capacity;
        size++;
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty())
            return false;
        front=(front+1)%capacity;
        size--;
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty())
            return false;
        if(rear==0)
            rear=capacity-1;
        else
            rear--;
        size--;
        return true;
    }
    
    int getFront() {
        if(isEmpty())
            return -1;
        return Ds[front];
    }
    
    int getRear() {
        if(isEmpty())
            return -1;
        if(rear==0)
            return Ds[capacity-1];
        
        else
            return Ds[rear-1];
    }
    
    bool isEmpty() {
        return size==0;
    }
    
    bool isFull() {
        return size==capacity;
    }
};


int maint()
{
	return 0;
}
