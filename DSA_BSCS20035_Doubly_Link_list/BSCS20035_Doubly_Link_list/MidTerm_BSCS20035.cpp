#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Double_Link
{
private:
	class Node
	{
		T data;
		Node* next;
		Node* prev;
		friend class Double_Link;

	public:
		Node(T d, Node* p = nullptr, Node* n = nullptr)
		{
			data = d;
			prev = p;
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
	class F_iterator
	{
		Node* t;
		friend class Double_Link;
	public:
		F_iterator()
		{
			t = nullptr;
		}

		F_iterator(Node* n)
		{
			t = n;
		}

		F_iterator operator++(int)
		{
			t = t->next;
			return *this;
		}

		F_iterator operator+(int i)
		{
			int s = 0;
			while (s < i)
			{
				t = t->next;
				s++;
			}
			return t;
		}

		bool operator==(F_iterator temp)
		{
			return (t == temp.t);
		}

		bool operator!=(F_iterator temp)
		{
			return (t != temp.t);
		}

		T& operator*()
		{
			return t->data;
		}
	};

	class R_iterator
	{
		Node* t;
		friend class Double_Link;
	public:
		R_iterator()
		{
			t = nullptr;
		}

		R_iterator(Node* n)
		{
			t = n;
		}

		R_iterator operator++(int)
		{
			t = t->prev;
			return *this;
		}

		R_iterator operator+(int i)
		{
			int s = 0;
			while (s < i)
			{
				t = t->next;
				s++;
			}
			return t;
		}

		bool operator==(R_iterator temp)
		{
			return (t == temp.t);
		}

		bool operator!=(R_iterator temp)
		{
			return (t != temp.t);
		}

		T& operator*()
		{
			return t->data;
		}
	};

	class General_iterator
	{
		Node* t;
		friend class Double_Link;
	public:
		General_iterator()
		{
			t = nullptr;
		}

		General_iterator(Node* n)
		{
			t = n;
		}

		General_iterator operator++(int)
		{
			t = t->next;
			return *this;
		}

		General_iterator operator--(int)
		{
			t = t->prev;
			return *this;
		}

		General_iterator operator+(int i)
		{
			int s = 0;
			while (s < i)
			{
				t = t->next;
				s++;
			}
			return t;
		}

		bool operator==(General_iterator temp)
		{
			return (t == temp.t);
		}

		bool operator!=(General_iterator temp)
		{
			return (t != temp.t);
		}

		T& operator*()
		{
			return t->data;
		}
	};


	F_iterator f_Begin()
	{
		return F_iterator(head);
	}

	F_iterator f_End()
	{
		return F_iterator(nullptr);
	}

	R_iterator r_Begin()
	{
		return R_iterator(tail);
	}

	R_iterator r_End()
	{
		return R_iterator(nullptr);
	}

	General_iterator Begin()
	{
		return General_iterator(head);
	}

	General_iterator Tail()
	{
		return General_iterator(tail);
	}

	General_iterator End()
	{
		return General_iterator(nullptr);
	}

	Double_Link()
	{
		head = tail = nullptr;
		Size = 0;
	}

	bool Empty()
	{
		return (head == nullptr);
	}

	void InsertAtFront(T val)
	{
		auto temp = new Node(val);
		if (Empty())
		{
			head = tail = temp;
			Size++;
			return;
		}

		temp->next = head;
		head->prev = temp;
		head = temp;
		Size++;

		return;
	}

	void InsertAtTail(T val)
	{
		auto temp = new Node(val);
		if (Empty())
		{
			head = tail = temp;
			Size++;
			return;
		}
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
		Size++;
		return;
	}

	T RemoveAt(General_iterator i)
	{
		if (Empty())
			return -1;

		T data = i.t->data;
		Node* temp = head;
		Node* temp2 = i.t;

		if (i.t == head && i.t->next == nullptr)
		{
			delete[] temp2;
			head = tail = nullptr;
			Size--;
			return data;
		}
		if (i.t == head)
		{
			i.t->next->prev = nullptr;
			head = i.t->next;
			Size--;
			delete[] temp2;
			return data;

		}

		else if (i.t == tail)
		{
			i.t->prev->next = nullptr;
			tail = i.t->prev;
			Size--;
			delete[] temp2;
			return data;
		}



		temp2->prev->next = temp2->next;
		temp2->next->prev = temp2->prev;
		Size--;
		delete[] temp2;
		return data;


	}

	void InsertAtAfter(General_iterator i, T val)
	{
		auto temp = new Node(val);
		if (i == nullptr)
			return ;
		if (i == tail)
		{
			temp->prev = tail;
			tail->next = temp;
			tail = i.t;
			Size++;
			return;
		}

		temp->next = i.t->next;
		temp->prev = i.t;

		i.t->next = temp;
		temp->next->prev = temp;
		Size++;
		return;
	}

	void InsertAtBefore(General_iterator i, T val)
	{
		auto temp = new Node(val);

		if (i.t == nullptr)
			return;

		if (i == head)
		{
			temp->prev = nullptr;
			temp->next = head;
			i.t->prev = temp;
			head = temp;
			Size++;
			return;
		}

		temp->next = i.t->next;
		temp->prev = i.t;

		i.t->next = temp;
		temp->next->prev = temp;
		Size++;
		return;
	}

	void Splice(General_iterator i, General_iterator head, General_iterator tail)
	{
		if (i.t == this->tail)
		{
			auto temp = i.t->next;
			tail.t->next = nullptr;
			i.t->next = head.t;
			head.t->prev = i.t;
			return;
		}
		auto temp = i.t->next;
		tail.t->next = i.t->next;
		i.t->next = head.t;
		head.t->prev = i.t;
		temp->prev = tail.t;


	}

};









#include <iostream>
#include"Double_Link.h"
using namespace std;

int main()
{
	Double_Link<int> L;
	Double_Link<int> Splice;


	L.InsertAtFront(50);
	L.InsertAtFront(100);
	L.InsertAtFront(150);
	L.InsertAtFront(200);
	L.InsertAtFront(250);
	Splice.InsertAtTail(-500);
	Splice.InsertAtTail(-400);
	Splice.InsertAtTail(-300);
	Splice.InsertAtTail(-200);


	cout << "Linked List 1: ";
	for (auto t = L.Begin(); t != L.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl;

	cout << "Linked List 2: ";
	for (auto t = Splice.Begin(); t != Splice.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl << endl;


	auto t = L.Begin() + 2;

	L.Splice(t, Splice.Begin(), Splice.Tail());
	cout << "Starting point: " << *t << endl;
	cout << "Ending point: " << *(L.Tail()) << endl << endl;


	cout << "Spliced List: ";
	for (auto t = L.Begin(); t != L.End(); t++)
	{
		cout << *t << " ";
	}
	cout << endl;
}

