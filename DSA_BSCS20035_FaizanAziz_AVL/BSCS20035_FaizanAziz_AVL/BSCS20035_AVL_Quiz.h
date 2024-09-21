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
		friend class AVL;
	public:
		Node(int v = 0, Node* L = nullptr, Node* R = nullptr)
		{
			val = v;
			left = L;
			right = R;
		}
	};

	Node* root;


public:
	AVL(Node* r=nullptr)
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
		return abs(Height(r->left) - Height(r->right));
	}

	bool IsBalanced(Node* r)
	{
		return (Height_Difference(r) <= 1);
	}
};
