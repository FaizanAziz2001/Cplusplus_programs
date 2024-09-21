#pragma once
#include<iostream>
using namespace std;

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node(T val = 0, Node<T>* d = nullptr)
	{
		data = val;
		next = d;
	}
	friend ostream& operator<<(ostream&, Node<T>& N)
	{
		cout << &N << " ->\t" << N.data << " => \t" << N.next << "\t";
		return cout;
	}
};

template<typename T>
class LinkedList
{

private:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* mid;
	void Print_recursion_iteration(Node<T>* temp)
	{
		if (temp == nullptr)
			return;
		cout << *temp << endl;
		Print_recursion_iteration(temp->next);
	}
	void Print_reverse_recursion_iteration(Node<T>* temp)
	{
		if (temp == nullptr)
			return;
		Print_reverse_recursion_iteration(temp->next);
		cout << temp->data << "  ";
	}

public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		mid = nullptr;
	}

	void Find_Middle()
	{
		if (IsEmpty() || head->next == nullptr)
		{
			mid = head;
			return;
		}

		Node<T>* slow = head;
		Node<T>* fast = head->next;

		while (fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (fast == nullptr)
				break;
		}

		mid = slow;
	}

	bool IsEmpty()
	{
		return (head == nullptr);
	}

	void InsertAfterAt(T val, T key)
	{
		Node<T>* temp = head;
		Node<T>* temp2 = new Node<T>(key);
		while (temp->data != val)
		{
			if (temp->next == nullptr)
				return;
			temp = temp->next;

		}

		if (temp == tail)
		{
			temp->next = temp2;
			tail = temp2;
			return;
		}
		temp2->next = temp->next;
		temp->next = temp2;


	}

	void InsertBeforeAt(T val, T key)
	{
		Node<T>* temp = head;
		Node<T>* temp2 = new Node<T>(key);

		if (head->data == val)
		{
			temp2->next = temp;
			head = temp2;
			return;

		}
		while (temp->next->data != val)
		{
			if (temp->next == nullptr)
				return;
			temp = temp->next;

		}

		temp2->next = temp->next;
		temp->next = temp2;
	}

	void InsertAtFront(T val)
	{
		Node<T>* temp = new Node<T>(val);

		if (IsEmpty())
		{
			head = tail = temp;
			return;
		}

		temp->next = head;
		head = temp;
	}

	void InsertAtTail(T val)
	{
		Node<T>* temp = new Node<T>(val);

		if (IsEmpty())
		{
			head = tail = temp;
			return;
		}
		tail->next = temp;
		tail = temp;
	}

	void InsertAtMid(T val)
	{

		Find_Middle();
		Node<T>* temp = new Node<T>(val);

		if (IsEmpty())
		{
			head = mid = tail = temp;
			return;
		}

		if (head->next == nullptr)
		{
			tail = temp;
		}
		temp->next = mid->next;
		mid->next = temp;
	}

	void InsertAfter(T val, T index)
	{
		Node<T>* temp = new Node<T>(val);
		Node<T>* temp2 = head;
		int i = 1;
		while (i < index)
		{
			temp2 = temp2->next;
			i++;
		}

		temp->next = temp2->next;
		temp2->next = temp;
	}

	void InsertBefore(T val, T index)
	{
		Node<T>* temp = new Node<T>(val);
		Node<T>* temp2 = head;

		int i = 1;
		while (i < index - 1)
		{
			temp2 = temp2->next;
			i++;
		}

		temp->next = temp2->next;
		temp2->next = temp;
	}

	void Print()
	{
		Node<T>* temp = head;
		cout << "Linked List: ";
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	T GetFront()
	{
		if (IsEmpty())
			return -1;
		return head->data;
	}

	T GetTail()
	{
		if (IsEmpty())
			return -1;
		return tail->data;
	}

	T RemoveFront()
	{

		if (IsEmpty())
			return -1;

		Node<T>* temp = head;
		T data;

		if (head == tail)
		{
			data = temp->data;
			delete[] temp;
			head = tail = nullptr;
			return data;
		}
		data = head->data;
		head = head->next;
		delete[] temp;
		return data;
	}

	T RemoveTail()
	{

		if (IsEmpty())
			return -1;

		Node<T>* temp = head;
		Node<T>* temp2 = tail;
		T data;
		if (tail == head)
		{
			data = temp2->data;
			delete[] temp2;
			head = tail = nullptr;
			return data;
		}

		while (temp->next != tail)
		{
			temp = temp->next;
		}



		data = temp2->data;
		temp->next = nullptr;
		tail = temp;
		delete[] temp2;
		return data;
	}

	T RemoveMiddle()
	{
		if (IsEmpty())
			return -1;
		T data;

		Node<T>* temp = head;


		if (head == tail)
		{
			data = temp->data;
			delete[] temp;
			head = tail = nullptr;
			return data;
		}

		Find_Middle();
		Node<T>* temp2 = mid;

		if (head == mid)
		{

			temp2 = temp->next;
			data = temp2->data;
			temp->next = nullptr;
			tail = head;
			delete[]temp2;
			return data;
		}


		while (temp->next != mid)
			temp = temp->next;

		temp->next = mid->next;
		data = mid->data;
		delete[] temp2;
		return data;

	}

	T Middle_Element()
	{
		Node<T>* slow = head;
		Node<T>* fast = head;

		while (fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (fast == nullptr)
				break;
		}
		return slow->data;
	}

	Node<T>* Search(T val)
	{
		Node<T>* temp = head;
		while (temp->next != nullptr)
		{
			if (temp->data == val)
				return temp;
			temp = temp->next;
		}

		return nullptr;
	}

	void Reverse()
	{
		Node<T>* current, * prev, * next;
		current = head;
		tail = head;
		prev = nullptr;

		while (current->next != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		head = current;
		head->next = prev;
	}

	void Print_recursion()
	{
		Print_recursion_iteration(head);
	}

	void Remove_Range(T D1, T D2)
	{
		Node<T>* temp = nullptr, *curr;
		for (curr = head; curr != nullptr;)
		{
			if (curr->data >= D1 and curr->data <= D2)
			{
				if (!temp)
					head = curr->next;
				auto next = curr->next;
				delete curr;
				curr = next;
				
			}
			else
			{
				if (!temp)
					temp = curr;
				else
				{
					temp->next = curr;
					temp = curr;
				}
				curr = curr->next;
			}

			
		}

		if(temp)
		temp->next = nullptr;

	}

	void Print_reverse_recursion()
	{
		Print_reverse_recursion_iteration(head);
	}

	bool check_circular_linkedlist()
	{
		if (tail->next == head)
			return true;
		return false;
	}

	friend ostream& operator<<(ostream& S, LinkedList<T> LL)
	{
		int i = 0;
		cout << "Linked List: " << endl;
		Node<T>* temp = LL.head;
		while (temp != nullptr)
		{
			for (int j = 0; j <= i; j++)
				cout << "\t";
			cout << *temp << endl;
			temp = temp->next;
			i++;
		}

		return cout;
	}
};
