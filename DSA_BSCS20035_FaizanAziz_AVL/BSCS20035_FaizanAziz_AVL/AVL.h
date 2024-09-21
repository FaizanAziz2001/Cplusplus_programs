#pragma once
#include<iostream>
#include<math.h>
using namespace std;

class AVL
{
	class Node
	{
		int val;
		Node* left;
		Node* right;
		Node* parent;
		int height;
		friend class AVL;
	public:
		Node(int v = 0, Node* L = nullptr, Node* R = nullptr, Node* P = nullptr)
		{
			val = v;
			left = L;
			right = R;
			parent = P;
			height = 1;
		}
	};

	Node* root;

	void Output_Tree_recursion(Node* r, int pos)
	{
		if (!r)
			return;
		Output_Tree_recursion(r->right, pos + 5);
		for (int i = 0; i < pos; i++)
		{
			cout << " ";
		}
		cout << r->val << endl;
		Output_Tree_recursion(r->left, pos + 5);
	}

	void Zig(Node* r)
	{
		if (!r)
			return;

		Node* Shift_tree = r->left->right;
		Node* L_Node = r->left;

		if (r->parent != nullptr && r == r->parent->left)
			r->parent->left = L_Node;
		else if (r->parent != nullptr && r == r->parent->right)
			r->parent->right = L_Node;

		L_Node->parent = r->parent;
		L_Node->right = r;

		r->left = Shift_tree;
		r->parent = L_Node;

		if (r == root)
			root = L_Node;

		r->height = Height(r);
		L_Node->height = Height(L_Node);
	}

	void Zag(Node* r)
	{
		if (!r)
			return;

		Node* Shift_tree = r->right->left;
		Node* R_Node = r->right;

		if (r->parent != nullptr && r == r->parent->left)
			r->parent->left = R_Node;
		else if (r->parent != nullptr && r == r->parent->right)
			r->parent->right = R_Node;

		R_Node->parent = r->parent;
		R_Node->left = r;

		r->right = Shift_tree;
		r->parent = R_Node;

		if (r == root)
			root = R_Node;

		r->height = Height(r);
		R_Node->height = Height(R_Node);
	}

	void Deletion_case1(Node*& temp)
	{
		auto del = temp;

		if (temp == temp->parent->left)
		{
			temp->parent->left = nullptr;
			delete del;
		}
		else if (temp == temp->parent->right)
		{
			temp->parent->right = nullptr;
			delete del;
		}
	}

	void Deletion_case2(Node*& temp)
	{

		auto del = temp;
		if (temp->right == nullptr)										//Case 2: left child
		{
			if (temp == temp->parent->left)
			{
				temp->parent->left = temp->left;
				temp->left->parent = temp->parent;
				delete del;
			}
			else if (temp == temp->parent->right)
			{
				temp->parent->right = temp->left;
				temp->left->parent = temp->parent;
				delete del;
			}
			return;
		}

		if (temp->left == nullptr)										//Case 2: right child
		{
			if (temp == temp->parent->left)
			{
				temp->parent->left = temp->right;
				temp->right->parent = temp->parent;
				delete del;
			}
			else if (temp == temp->parent->right)
			{
				temp->parent->right = temp->right;
				temp->right->parent = temp->parent;
				delete del;
			}
			return;
		}
	}

	void Deletion_case3(Node*& temp)
	{
		LNR_iterator it(temp);							//Both left and right child exist
		auto pre = it.Predecessor(it.i);

		if (pre->right != nullptr && pre->left != nullptr)
		{
			swap(temp->val, pre->val);
			if (pre == pre->parent->right)
			{
				pre->parent->right = nullptr;
				delete pre;
			}
			else if (pre == pre->parent->left)
			{
				pre->parent->left = nullptr;
				delete pre;
			}
			return;
		}

		if (temp == temp->parent->left)
		{
			pre->right = temp->right;
			pre->parent = temp->parent;

			temp->parent->left = pre;
			temp->right->parent = pre;
		}
		else if (temp == temp->parent->right)
		{
			pre->right = temp->right;
			pre->parent = temp->parent;

			temp->parent->right = pre;
			temp->right->parent = pre;
		}

		delete temp;

	}

public:

	class LNR_iterator
	{
		Node* i;
		friend class AVL;

	public:
		LNR_iterator(Node* n)
		{
			i = n;
		}

		int operator*()
		{
			return i->val;
		}

		Node* Min(Node* temp)
		{
			while (temp->left != nullptr)
				temp = temp->left;
			return temp;
		}

		Node* Max(Node* temp)
		{
			while (temp->right != nullptr)
				temp = temp->right;
			return temp;
		}

		Node* Successor(Node* r)
		{
			if (r->right != nullptr)
			{
				return Min(r->right);
			}
			while (r->parent != nullptr && r->parent->right == r)
				r = r->parent;
			return r->parent;
		}

		Node* Predecessor(Node* r)
		{
			if (r->left != nullptr)
			{
				return Max(r->left);
			}
			while (r->parent != nullptr && r->parent->left == r)
				r = r->parent;
			return r->parent;
		}

		LNR_iterator operator++()
		{
			i = Successor(i);
			return *this;
		}

		LNR_iterator operator--()
		{

			i = Predecessor(i);
			return *this;
		}

		bool operator==(LNR_iterator n)
		{
			return i == n.i;
		}

		bool operator!=(LNR_iterator n)
		{
			return i != n.i;
		}
	};

	LNR_iterator Search(int val)
	{
		Node* temp = root;
		if (val == root->val)
		{
			return LNR_iterator(temp);
		}

		while (temp != nullptr)
		{
			if (temp->val == val)
				return temp;
			else if (temp->val > val)
				temp = temp->left;
			else
				temp = temp->right;
		}

		return LNR_iterator(temp);
	}

	AVL(Node* r = nullptr)
	{
		root = r;
	}

	int Height(Node* r)
	{
		if (!r)
			return 0;
		return max(Height(r->left), Height(r->right)) + 1;
	}

	int Height_Difference(Node* r)
	{
		return Height(r->left) - Height(r->right);
	}

	bool IsBalanced(Node* r)
	{
		return abs(Height_Difference(r)) <= 1;
	}

	void Insert(int d)
	{
		Node* insert = new Node(d);
		Node* temp = root;

		if (root == nullptr)
		{
			root = insert;
			root->parent = nullptr;
			return;
		}

		do
		{
			if (temp->val > d)
			{
				if (temp->left)
					temp = temp->left;
				else
				{
					temp->left = insert;
					insert->parent = temp;
					break;
				}
			}
			else
			{
				if (temp->right)
					temp = temp->right;
				else
				{
					temp->right = insert;
					insert->parent = temp;
					break;
				}
			}
		} while (true);


		while (temp)
		{
			temp->height = Height(temp);
			if (!IsBalanced(temp))
			{
				Check_cases(temp);
			}

			temp = temp->parent;
		}
	}

	void Check_cases(Node* r)
	{
		if (Height_Difference(r) > 1)
		{
			if (Height_Difference(r->left) == 0)
			{
				Zig(r);
			}
			else if (Height_Difference(r->left) > 0)
			{
				Zig(r);
			}
			else
			{
				Zag(r->left);
				Zig(r);
			}
		}
		else if (Height_Difference(r) < -1)
		{
			if (Height_Difference(r->right) == 0)
			{
				Zag(r);
			}
			else if (Height_Difference(r->right) > 0)
			{
				Zig(r->right);
				Zag(r);
			}
			else
			{
				Zag(r);
			}
		}
	}

	void Output_Tree()
	{
		Output_Tree_recursion(root, 0);
	}

	void Deletion(int value)
	{
		if (root == nullptr)
			return;

		auto itr = Search(value);
		Node* temp = itr.i;
		Node* p = temp->parent;

		if (temp == nullptr)
			return;

		if (temp->right == nullptr && temp->left == nullptr)					// Case 1: No children
		{
			Deletion_case1(temp);
		}
		else if (temp->right == nullptr || temp->left == nullptr)
		{
			Deletion_case2(temp);														//Case 2:One child exist
		}
		else if (temp->right != nullptr && temp->left != nullptr)
		{
			Deletion_case3(temp);															//Case 3: Both children exist;
		}

		while (p != nullptr)
		{
			p->height = Height(p);
			if (!IsBalanced(p))
			{
				Check_cases(p);
			}
			p = p->parent;
		}
	}


};
