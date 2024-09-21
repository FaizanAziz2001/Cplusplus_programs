#pragma once
#include<iostream>
using namespace std;

template<typename T>
class forwardlist
{
private:
	class Node
	{
		T data;
		Node* next;
		friend class forwardlist;

	public:
		Node(T d, Node* n = nullptr)
		{
			data = d;
			next = n;
		}

		friend ostream& operator<<(ostream&, Node& N)
		{
			cout << N.data << "-> ";
			return cout;
		}
	};

	Node* head;
	Node* tail;
	int Size;

public:

	class Fl_iterator
	{
		Node* t;
		friend class forwardlist;
	public:
		Fl_iterator()
		{
			t = nullptr;
		}

		Fl_iterator(Node* n)
		{
			t = n;
		}

		Fl_iterator operator++(int)
		{
			t = t->next;
			return *this;
		}

		Fl_iterator operator+(int i)
		{
			int s = 0;
			while (s < i)
			{
				t = t->next;
				s++;
			}
			return t;
		}

		bool operator==(Fl_iterator temp)
		{
			return (t == temp.t);
		}

		bool operator!=(Fl_iterator temp)
		{
			return (t != temp.t);
		}

		T& operator*()
		{
			return t->data;
		}
	};

	Fl_iterator Begin()
	{
		Fl_iterator t;
		return t = head;
	}

    Fl_iterator End()
	{
		return Fl_iterator(nullptr);
	}

	Fl_iterator Search(T data)
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			if (data == temp->data)
				return Fl_iterator(temp);
			temp = temp->next;
		}

		return Fl_iterator(nullptr);

	}

	forwardlist()
	{
		head = tail = nullptr;
		Size = 0;
	}

	bool IsEmpty()
	{
		return (head == nullptr);
	}

	void InsertAtEnd(T data)
	{
		Node* temp = new Node(data);
		if (head == nullptr)
		{
			head = tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		Size++;
	}

	void InsertAtFront(T data)
	{
		Node* temp = new Node(data);
		if (head == nullptr)
		{
			head = tail = temp;
		}
		else
		{
			temp->next = head;
			head = temp;
		}
		Size++;
	}

	void InsertAfter(Fl_iterator i, T val)
	{
		Node* temp = new Node(val);
		temp->next = i.t->next;
		i.t->next = temp;
		Size++;
	}

	void Insertbefore(Fl_iterator i, T val)
	{
		Node* temp = new Node(val);
		Node* temp2 = head;
		while (temp2->next != i.t)
		{
			temp2 = temp2->next;
		}
		temp2->next = temp;
		temp->next = i.t;
		Size++;
	}

	void Print()
	{
		Node* temp = head;
		cout << "Linked List: ";
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	T RemoveAt(Fl_iterator& i)
	{
		if (IsEmpty())
			return -1;
		Node* temp = head;
		Node* temp2 = i.t;
		T data = i.t->data;
		while (temp->next != i.t)
		{
			temp = temp->next;
		}
		temp->next = i.t->next;

		delete[] temp2;
		i.t = nullptr;
		Size--;
		return data;

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

		Node* temp = head;
		T data;

		if (head == tail)
		{
			data = temp->data;
			delete[] temp;
			head = tail = nullptr;
			Size--;
			return data;
		}
		data = head->data;
		head = head->next;
		delete[] temp;
		Size--;
		return data;
	}

	T RemoveTail()
	{

		if (IsEmpty())
			return -1;

		Node* temp = head;
		Node* temp2 = tail;
		T data;

		if (tail == head)
		{
			data = temp2->data;
			delete[] temp2;
			head = tail = nullptr;
			Size--;
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
		Size--;
		return data;
	}


};