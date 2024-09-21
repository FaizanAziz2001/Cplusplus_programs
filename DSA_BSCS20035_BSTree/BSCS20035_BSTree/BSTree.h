#pragma once
#include<iostream>
#include<fstream>
#include <algorithm>  
#include<queue>
#include<list>
#include<vector>
using namespace std;
template<typename T>

class BSTree
{

private:

	friend class LNR_iterator;

	class Node
	{
		T data;
		Node* left;
		Node* right;
		Node* parent;
		Node* next;
		Node* previous;
		int size;
		int height;
		friend class BSTree;

	public:
		Node(T d, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr, Node* prev = nullptr, Node* n = nullptr)
		{
			data = d;
			left = l;
			right = r;
			parent = p;
			next = n;
			previous = prev;
			size = 1;
			height = 1;
		}
	};

	Node* root;

	void LNR_recursion(Node* temp)
	{
		if (temp == nullptr)
			return;
		LNR_recursion(temp->left);
		cout << temp->data << " ";
		LNR_recursion(temp->right);
	}

	void RNL_recursion(Node* temp)
	{
		if (temp == nullptr)
			return;
		RNL_recursion(temp->right);
		cout << temp->data << " ";
		RNL_recursion(temp->left);
	}

	void NLR_recursion(Node* r)
	{
		if (r == nullptr)
			return;
		cout << r->data << " ";
		NLR_recursion(r->left);
		NLR_recursion(r->right);
	}

	void LNR_vector_Traversal(vector<int>& v, Node* r)
	{
		if (r == nullptr)
			return;
		LNR_vector_Traversal(v, r->left);
		v.push_back(r->data);
		LNR_vector_Traversal(v, r->right);
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
			swap(temp->data, pre->data);
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

	}

	void RangeSearch_recursion_ascending(Node* r, T v1, T v2)
	{
		if (r == nullptr)
			return;
		RangeSearch_recursion_ascending(r->left, v1, v2);
		if (r->data >= v1 && r->data <= v2)
			cout << r->data << " ";
		RangeSearch_recursion_ascending(r->right, v1, v2);


	}

	void RangeSearch_recursion_descending(Node* r, T v1, T v2)
	{
		if (r == nullptr)
			return;
		RangeSearch_recursion_descending(r->right, v1, v2);
		if (r->data <= v1 && r->data >= v2)
			cout << r->data << " ";
		RangeSearch_recursion_descending(r->left, v1, v2);


	}

	void PrintNodesAtK_recursion(Node* r, int k, int count)
	{
		if (r == nullptr)
			return;
		if (k == count)
		{
			cout << r->data << " ";
			return;
		}

		PrintNodesAtK_recursion(r->left, k, count + 1);
		PrintNodesAtK_recursion(r->right, k, count + 1);
	}

	void Delete_ALL_Nodes_recursion(Node* r)
	{

		if (r == nullptr)
			return;
		if (r->left == nullptr && r->right == nullptr)
		{
			auto temp = r;
			if (r == r->parent->right)
				r->parent->right = nullptr;
			else
				r->parent->left = nullptr;

			delete temp;
			return;
		}

		Delete_ALL_Nodes_recursion(r->left);
		Delete_ALL_Nodes_recursion(r->right);
	}

	void Print_All_Leaves_recursion(Node* r)
	{
		if (r == nullptr)
			return;
		if (r->left == nullptr && r->right == nullptr)
		{
			cout << r->data << " ";
		}
	
		Print_All_Leaves_recursion(r->left);
		Print_All_Leaves_recursion(r->right);
	}

	void Save_Tree_recursion(ofstream& fout, Node* r)
	{
		if (r == nullptr)
			return;
		fout << r->data << " ";
		Save_Tree_recursion(fout, r->left);
		Save_Tree_recursion(fout, r->right);
	}

	int Even_Count_check(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (temp->data % 2 == 0)
			return (Even_Count_check(temp->left) + Even_Count_check(temp->right) + 1);
		else
			return (Even_Count_check(temp->left) + Even_Count_check(temp->right));


	}

	int Prime_Count_check(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (IsPrime(temp->data))
			return Prime_Count_check(temp->left) + Prime_Count_check(temp->right) + 1;
		else
			return Prime_Count_check(temp->left) + Prime_Count_check(temp->right);
	}

	int Tree_Height_check(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		return max(Tree_Height_check(temp->left), Tree_Height_check(temp->right)) + 1;
	}

	int Internal_Node_count_recursion(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (temp->left == nullptr && temp->right == nullptr)
			return 0;
		return (Internal_Node_count_recursion(temp->left) + Internal_Node_count_recursion(temp->right) + 1);
	}

	int Internal_Node_Count_With1branch_recursion(Node* r)
	{
		if (r == nullptr)
			return 0;
		if (r->left == nullptr && r->right == nullptr)
			return 0;
		if (r->left == nullptr || r->right == nullptr)
			return Internal_Node_Count_With1branch_recursion(r->left) + Internal_Node_Count_With1branch_recursion(r->right) + 1;
		else
			return Internal_Node_Count_With1branch_recursion(r->left) + Internal_Node_Count_With1branch_recursion(r->right);
	}

	int Leaves_count_recursion(Node* temp)
	{
		if (temp == nullptr)
			return 0;
		if (temp->right == nullptr && temp->left == nullptr)
			return 1;
		return (Leaves_count_recursion(temp->left) + Leaves_count_recursion(temp->right));

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

	Node* Closest_leafNode()
	{
		queue<Node*> Q;
		Q.push(root);
		Q.push(nullptr);
		while (!Q.empty())
		{
			auto temp = Q.front();
			if (temp != nullptr && temp->left == nullptr && temp->right == nullptr)
				return temp;
			Q.pop();
			if (temp != nullptr)
			{
				if (temp->left)
					Q.push(temp->left);
				if (temp->right)
					Q.push(temp->right);
			}
			else
			{
				if (!Q.empty())
					Q.push(nullptr);
			}
		}

		return root;
	}

	Node* Farthest_leafNode()
	{
		queue<Node*> Q;
		Node* prev = root;
		Q.push(root);
		Q.push(nullptr);
		while (!Q.empty())
		{
			auto temp = Q.front();
			if (temp)
				prev = temp;
			Q.pop();
			if (temp != nullptr)
			{
				if (temp->left)
					Q.push(temp->left);
				if (temp->right)
					Q.push(temp->right);
			}
			else
			{
				if (!Q.empty())
					Q.push(nullptr);
			}
		}

		return prev;
	}

	Node* Min_recursion(Node* r)
	{
		if (r->left == nullptr)
			return r;
		return Min_recursion(r->left);
	}

	Node* Max_recursion(Node* r)
	{
		if (r->right == nullptr)
			return r;
		return Max_recursion(r->right);
	}

	BSTree BST_sorted_array_recursion(BSTree& BST, vector<T> data, int index, int size)
	{
		if (index > size)
			return BST;
		else
		{
			int mid = (index + size) / 2;
			BST.Insert(data[mid]);
			BST_sorted_array_recursion(BST, data, index, mid - 1);
			BST_sorted_array_recursion(BST, data, mid + 1, size);
			return BST;
		}

	}

	bool check_BST_recursion(Node* temp, int max, int min)																							//left node needs to be less than parent and greater than its child
	{
		if (temp == nullptr)																														//right node needs to be greater than parent and less than its child 
			return true;
		if (temp->data > min && temp->data < max)																										//max determines upper bound and min lower bound
			return (check_BST_recursion(temp->left, temp->data, min) && check_BST_recursion(temp->right, max, temp->data));
		else
			return false;

	}

	bool check_trees(Node* r1, Node* r2)
	{
		if (r1 == nullptr && r2 == nullptr)												//both null means both are same
			return true;
		if (r1 == nullptr || r2 == nullptr)												//if any one of them is null means pictorially not same
			return false;
		if (r1->data != r2->data)
			return false;

		return (check_trees(r1->left, r2->left) && check_trees(r1->right, r2->right));
	}

	bool IsBalanced_recursion(Node* r)
	{
		if (r == nullptr)
			return true;
		if (abs(Tree_Height_check(r->left) - Tree_Height_check(r->right)) > 1)
			return false;

		return IsBalanced_recursion(r->left) && IsBalanced_recursion(r->right);
	}

	bool IsSubtree_recursion(Node* r, Node* r2)
	{
		if (r == nullptr)
			return false;
		if (r2 == nullptr)
			return false;
		if (r->data == r2->data)
			if (check_trees(r, r2))
				return true;
		return IsSubtree_recursion(r->left, r2) || IsSubtree_recursion(r->right, r2);

	}

	bool IsPrime(T val)
	{
		if (val == 0 || val == 1 || val == 2)
			return true;
		for (int i = 2; i <= val / 2; i++)
		{
			if (val % i == 0)
				return false;
		}
		return true;
	}



public:
	class iterator
	{
		Node* i;
		friend class BSTree;
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
		friend class BSTree;

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

	iterator Search(T val)
	{
		Node* temp = root;
		if (val == root->data)
		{
			return iterator(temp);
		}

		while (temp != nullptr)
		{
			if (temp->data == val)
				return temp;
			else if (temp->data > val)
				temp = temp->left;
			else
				temp = temp->right;
		}

		return iterator(temp);
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

	BSTree()
	{
		root = nullptr;
	}

	BSTree BST_sorted_array(vector<T> data)
	{
		BSTree BST;
		return BST_sorted_array_recursion(BST, data, 0, data.size() - 1);
	}

	void Insert(T d)
	{
		Node* temp = new Node(d);

		if (root == nullptr)
		{
			root = temp;
			root->parent = nullptr;
			return;
		}

		Node* temp2 = root;
		LNR_iterator itr(temp);
		do
		{
			temp2->size++;
			if (temp2->data > d)
			{
				if (temp2->left == nullptr)
				{
					temp2->left = temp;
					temp->parent = temp2;


					temp->next = itr.Successor(temp);
					temp->previous = itr.Predecessor(temp);

					if (temp->next != nullptr)
						temp->next->previous = temp;
					if (temp->previous != nullptr)
						temp->previous->next = temp;
					break;

				}

				temp2 = temp2->left;
			}
			else
			{
				if (temp2->right == nullptr)
				{
					temp2->right = temp;
					temp->parent = temp2;

					temp->next = itr.Successor(temp);
					temp->previous = itr.Predecessor(temp);

					if (temp->next != nullptr)
						temp->next->previous = temp;
					if (temp->previous != nullptr)
						temp->previous->next = temp;
					break;

					/*Node* pre = itr.Predecessor(itr.i);
					Node* suc = itr.Successor(itr.i);
					temp->next = suc;
					temp->previous = pre;

					if (suc != nullptr)
						suc->previous = temp;
					if (pre != nullptr)
						pre->next = temp;

					break;*/
				}

				temp2 = temp2->right;
			}

		} while (true);


		while (temp2 != nullptr)
		{
			temp2->height = Tree_Height_check(temp2);
			temp2 = temp2->parent;
		}
	}

	void LNR_Print()
	{
		LNR_recursion(root);
	}

	void OutputTree()
	{
		int pos = 5;
		if (root == nullptr)
			return;
		return OutputTree_recursion(root, pos);
	}

	void RNL_Print()
	{
		RNL_recursion(root);
	}

	void NLR_Print()
	{
		NLR_recursion(root);
	}

	void LNR_Alternative_Print()
	{
		LNR_iterator itr(root);
		Node* r = itr.Min(root);

		while (r != nullptr)
		{
			cout << r->data << " ";
			r = itr.Successor(r);
		}
	}

	void Deletion(T value)
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
			p->size--;
			p->height = Tree_Height_check(p);
			p = p->parent;
		}
	}

	void RangeSearch(T v1, T v2)
	{
		iterator itr(root);
		auto temp1 = Search(v1);
		auto temp2 = Search(v2);
		if (temp1 == nullptr || temp2 == nullptr)
		{
			cout << "Incorrect range";
			return;
		}

		if (v1 < v2)
			RangeSearch_recursion_ascending(root, v1, v2);
		else
			RangeSearch_recursion_descending(root, v1, v2);
	}

	void PrintNodesAtK(int k)
	{
		PrintNodesAtK_recursion(root, k, 0);
	}

	void Closest_leafPath()
	{
		auto temp = Closest_leafNode();
		while (temp != nullptr)
		{
			if (temp->parent)
				cout << temp->data << " -> ";
			else
				cout << temp->data;
			temp = temp->parent;
		}
	}

	void Farthest_leafPath()
	{
		auto temp = Farthest_leafNode();
		while (temp != nullptr)
		{
			if (temp->parent)
				cout << temp->data << " -> ";
			else
				cout << temp->data;
			temp = temp->parent;
		}
	}

	void Delete_ALL_Nodes()
	{
		Delete_ALL_Nodes_recursion(root);
	}

	void Print_All_leaves()
	{
		Print_All_Leaves_recursion(root);
	}

	void Save_Tree(string name)
	{
		ofstream fout(name);
		Save_Tree_recursion(fout, root);
	}

	void Load_Tree(string name)
	{
		int x;
		ifstream fin(name);
		while (fin >> x)
		{
			Insert(x);
		}
	}

	void Sort(vector<T>& data)
	{
		BSTree<int> Tree;
		for (int i = 0; i < data.size(); i++)
		{
			Tree.Insert(data[i]);
		}
		data.clear();
		Tree.LNR_vector_Traversal(data, Tree.root);
	}

	void Min()
	{
		auto temp = Min_recursion(root);
		cout << temp->data;
	}

	void Max()
	{
		auto temp = Max_recursion(root);
		cout << temp->data;
	}

	int Farthest_leaf()
	{
		auto n = Farthest_leafNode();
		return n->data;
	}

	int Closest_leaf()
	{
		auto n = Closest_leafNode();
		return n->data;
	}

	int Even_Count()
	{
		return Even_Count_check(root);
	}

	int Prime_Count()
	{
		return Prime_Count_check(root);
	}

	int Tree_height()
	{
		return Tree_Height_check(root);
	}

	int Internal_Node_Count()
	{
		return Internal_Node_count_recursion(root);
	}

	int Internal_Node_Count_With1branch()
	{
		return Internal_Node_Count_With1branch_recursion(root);
	}

	int Leaves_count()
	{
		return Leaves_count_recursion(root);
	}

	bool Check_BST()
	{
		return check_BST_recursion(root, INT_MAX, INT_MIN);
	}

	bool Identical_trees(BSTree T2)
	{
		return check_trees(root, T2.root);											//pictorially and value wise
	}

	bool Identical_BST_V_recursion(LNR_iterator itr1, LNR_iterator itr2)
	{
		if (itr1 == nullptr && itr2 == nullptr)
			return true;
		if (itr1 == nullptr || itr2 == nullptr)
			return false;
		if (itr1.i->data != itr2.i->data)
			return false;

		++itr1;
		++itr2;
		return Identical_BST_V_recursion(itr1, itr2);
	}

	bool Identical_BST_V(BSTree T2)
	{
		LNR_iterator itr1(root);
		LNR_iterator itr2(T2.root);
		itr1 = LNR_Start();
		itr2 = T2.LNR_Start();
		return Identical_BST_V_recursion(itr1, itr2);

	}

	bool IsBalanced()
	{
		return IsBalanced_recursion(root);
	}

	bool IsSubtree(BSTree T2)
	{
		return IsSubtree_recursion(root, T2.root);
	}

	vector<list<Node*>> Linked_List()
	{
		vector<list<Node*>> v;
		queue<Node*> Q;
		list<Node*> L;
		Q.push(root);
		Q.push(nullptr);
		while (!Q.empty())
		{
			auto temp = Q.front();
			Q.pop();
			if (temp != nullptr)
			{

				L.push_back(temp);
				if (temp->left != nullptr)
					Q.push(temp->left);
				if (temp->right != nullptr)
					Q.push(temp->right);
			}
			else
			{
				v.push_back(L);
				L.clear();
				if (!Q.empty())
					Q.push(nullptr);
			}
		}
		return v;
	}

	vector<int> Create_Array(BSTree BST)
	{
		vector<int> v1, v2, v3;
		LNR_vector_Traversal(v1, root);
		LNR_vector_Traversal(v2, BST.root);

		int i = 0, j = 0;
		while (i < v1.size() && j < v2.size())
		{
			if (v1[i] < v2[j])
				v3.push_back(v1[i++]);
			else
				v3.push_back(v2[j++]);
		}

		while (i < v1.size())
			v3.push_back(v1[i++]);
		while (j < v2.size())
			v3.push_back(v2[j++]);

		return v3;
	}
};
