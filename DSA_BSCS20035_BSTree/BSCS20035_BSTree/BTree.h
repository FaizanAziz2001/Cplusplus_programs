#pragma once
#include<iostream>

using namespace std;
template<typename T>

class BTree
{
	class Node
	{
		T data;
		Node* left;
		Node* right;
		Node* parent;
		friend class BTree;

	private:
		Node(T d, Node* l = nullptr, Node* r = nullptr)
		{
			data = d;
			left = l;
			right = r;
		}
	};

	Node* root;

	void Print_recursion(Node* temp)
	{
		if (temp == nullptr)
			return;
		Print_recursion(temp->left);
		cout << temp->data << " ";
		Print_recursion(temp->right);
	}

	void Print_recursion_reverse(Node* temp)
	{
		if (temp == nullptr)
			return;
		Print_recursion_reverse(temp->right);
		cout << temp->data << " ";
		Print_recursion_reverse(temp->left);
	}

	bool check_trees(Node* r1, Node* r2)
	{
		if (r1 == nullptr && r2 == nullptr)
			return true;
		if (r1 == nullptr || r2 == nullptr)
			return false;
		if (r1->data != r2->data)
			return false;

		return (check_trees(r1->left, r2->left) && check_trees(r1->right, r2->right));
	}

	int Even_Count_check(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (temp % 2 == 0)
		{
			return (Even_Count_check(temp->left) + Even_Count_check(temp->right) + 1);
		}
		else
			return (Even_Count_check(temp->left) + Even_Count_check(temp->right));
	}

	bool check_BT_recursion(Node* temp, int max, int min)
	{
		if (temp == nullptr)
			return true;
		if (temp->data > min && temp->data < max)
			return (check_BT_recursion(temp->left, root->data, min) && check_BT_recursion(temp->right, max, root->data));
		else
			return false;

	}

	int Internal_Node_count_recursion(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (temp->left == nullptr && temp->right == nullptr)
			return 0;
		return (Internal_Node_count_recursion(temp->left) + Internal_Node_count_recursion(temp->right) + 1);
	}

	int Leaves_count_recursion(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (temp->right == nullptr && temp->left == nullptr)
			return 1;
		return (Leaves_count_recursion(temp->left) + Leaves_count_recursion(temp->right));

	}

	void OutputTree_recursion(Node* temp, int pos)
	{

		if (temp == nullptr)
			return;

		if (temp != nullptr)
		{
			OutputTree_recursion(temp->right, pos + 5);
			for (int i = 0; i < pos; i++)
			{
				cout << " ";
			}
			cout << temp->data << endl;
			OutputTree_recursion(temp->left, pos + 5);
		}
	}

	Node* LCA_recursion(Node* r, Node* n1, Node* n2)
	{
		if (r == n1 || r == n2)														//return matching node
			return r;
		if (r == nullptr)
			return nullptr;

		Node* left = LCA_recursion(r->left, n1, n2);							//find left node
		Node* right = LCA_recursion(r->right, n1, n2);							//find right node

		if (left == nullptr && right == nullptr)								//left and right node match given nodes
			return nullptr;
		if (left != nullptr && right != nullptr)								//left and right node do not match given nodes
			return r;
		if (left != nullptr)													//left node matches n1 or n2
			return left;
		if (right != nullptr)													//right node matches n1 or n2
			return right;


	}

	bool IsSubTree_recursion(Node* r, Node* r2)
	{
		if (r == nullptr)
			return false;
		if (r2 == nullptr)
			return false;
		if (r->data == r2->data)
			if (check_trees(r, r2))
				return true;
		return IsSubTree_recursion(r->left, r2) || (r->right, r2);

	}
public:
	class iterator
	{
		Node* i;
	public:
		iterator(Node* n)
		{
			i = n;
		}
		T operator*()
		{
			return i->data;
		}
		bool operator==(iterator n)
		{
			return i == n.i;
		}
		bool operator!=(iterator n)
		{
			return i != n.i;
		}
	};

	class LNR_iterator
	{
		Node* i;
		friend class BTree;

	public:
		LNR_iterator(Node* n)
		{
			i = n;
		}

		T operator*()
		{
			return i->data;
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

	iterator Start()
	{
		return iterator(root);
	}

	iterator End()
	{
		return iterator(nullptr);
	}

	LNR_iterator LNR_Start()
	{
		LNR_iterator temp(root);
		return temp.Min(temp.i);
	}

	LNR_iterator LNR_End()
	{
		LNR_iterator temp(root);
		return temp.Max(temp.i);
	}

	LNR_iterator LCA(LNR_iterator i1, LNR_iterator i2)
	{
		return LCA_recursion(root, i1.i, i2.i);
	}

	BTree()
	{
		root = nullptr;
	}

	void Insert(T d)
	{
		Node* temp = new Node(d);

		if (root == nullptr)
		{
			root = temp;
			return;
		}

		Node* temp2 = root;

		do
		{

			int ram = (rand() % 10);
			if (ram == 0 || ram == 2 || ram == 4 || ram == 8 || ram == 10)
			{
				if (temp2->left == nullptr)
				{
					temp2->left = temp;
					return;
				}
				temp2 = temp2->left;
				continue;
			}
			else
			{
				if (temp2->right == nullptr)
				{
					temp2->right = temp;
					return;
				}
				temp2 = temp2->right;
				continue;
			}
		} while (true);
	}

	void Print()
	{
		Print_recursion(root);
	}

	void Print_reverse()
	{
		Print_recursion_reverse(root);
	}

	bool Identical_trees(BTree T2)
	{
		return check_trees(root, T2.root);
	}

	int Even_Count()
	{
		return Even_Count_check(root);
	}

	bool Check_BT()
	{
		return check_BT_recursion(root, INT_MAX, INT_MIN);
	}

	int Internal_Node_Count()
	{
		return Internal_Node_count_recursion(root);
	}

	int Leaves_count()
	{
		return Leaves_count_recursion(root);
	}

	void OutputTree()
	{
		int pos = 5;
		if (root == nullptr)
			return;
		return OutputTree_recursion(root, pos);
	}

	bool IsSubtree(BTree T2)
	{
		return IsSubtree_recursion(root, T2.root);
	}
};
