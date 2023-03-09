#pragma once
#include <iostream>
#include "math.h"
using namespace std;

template <typename T>
struct BTNode
{
	T info;
	BTNode<T>* left, * right;

	BTNode(T val)
	{
		info = val;
		left = right = nullptr;
	}
};


template<typename T>
class BST
{
private:

	BTNode<T>* root;

public:
	BST()
	{
		root = nullptr;
	}

	void setRoot(T val)
	{
		if (!root)root = new BTNode<T>(val);
		root->info = val;
	}

	BTNode<T>* search(T key, BTNode<T>*& p2)
	{
		BTNode<T>* p = nullptr;
		if (p2->info == key)
		{
			p = p2;
		}
		if (!p && p2->left)
		{
			p = search(key, p2->left);
		}
		if (!p && p2->right)
		{
			p = search(key, p2->right);
		}
		return p;
	}

	void VLR()
	{
		VLR_2(root);
	}
	void VLR_2(BTNode<T>* p)
	{
		if (p == nullptr)return;
		if ( p!=nullptr)cout << p->info << " ";
		if (p->left)
			VLR_2(p->left);
		if (p->right)
			VLR_2(p->right);
	}
	int countLeafNodes()
	{
		return countNodes(root);
	}
	int countNodes(BTNode<T>*p)
	{
		int count = 0;
		if (p->left == nullptr && p->right == nullptr)return 1;
		if (p->left)count += countNodes(p->left);
		if (p->right)count += countNodes(p->right);
		return count;
	}
	void setLeftChild(T parent, T child)
	{
		BTNode<T>* temp = search(parent, root);
		if (temp!=nullptr)temp->left = new BTNode<T>(child);

	}
	//void setRightChild(T parent, T child)
	//{
	//	
	//	BTNode<T>* temp = search(parent, root);
	//	if (temp != nullptr)temp->right = new BTNode<T>(child);

	//}


	void insert(T key)
	{
		if (!root)
		{
			root = new BTNode<T>(key);
		}
		BTNode<T>* p = root;
		BTNode<T>* prev = root;

		while (p != nullptr)
		{
			if (p->info == key)return ;
			else if (key < p->info) 
			{
				prev = p;
				p = p->left;
				if (p == nullptr)
				{
					prev->left = new BTNode<T>(key);
				}
			}
			else
			{
				prev = p;
				p = p->right;
				if (p == nullptr)
				{
					prev->right = new BTNode<T>(key);
				}
			}
		}

	}

	bool search( T key )
	{
		BTNode<T>* p = root;
		while (p != nullptr)
		{
			if (p->info == key)return true;
			else if (key < p->info)p = p->left;
			else
			{
				p = p->right;
			}
		}
		return false;
	}

	void remove(T key )
	{
		if (!root || !search(key))return;

	
		BTNode<T>* p = root;
		BTNode<T>* prev = root;

		//int count = 0;
		if (root->info == key && root->left)
		{
			// agar root ko hi remove karna hai to uska left wali side se jo rightmost hai usko pakr ke info replace kar do
			BTNode<T>* p_root = root->left;
			BTNode<T>* prev_root = root->left;

			while (p_root->right != nullptr)
			{
				prev_root = p_root;
				p_root = p_root->right;

			}
			root->info = p_root->info;
			prev_root->right = nullptr;
			delete p_root;
			return;
		}
		while (p->info != key)
		{
			
			 if (key < p->info)
			 {
				prev = p;
				p = p->left;
				if (p->info == key && p->left==nullptr && p->right==nullptr)
				{
					prev->left = nullptr;
					delete p;
					return;
				}
				else if (p->info == key && p->left == nullptr && p->right != nullptr)
				{
					prev->left = p->right;
					delete p;
					return;
				}
				else if (p->info == key && p->right == nullptr && p->left != nullptr)
				{
					prev->left = p->left;
					delete p;
					return;
				}
				// degree 3
				else if (p->info == key && p->right != nullptr && p->left != nullptr)
				{
					BTNode<T>* p2 = p->right;
					BTNode<T>* prev2 = p;

					while (p2->left != nullptr)
					{
						prev2 = p2;
						p2 = p2->left;
					}
					p->info = p2->info;
					delete p2; 
					prev2->left = nullptr;
					return;
				}
			 }
			else if (key>p->info)
			{
				 prev = p;
				 p = p->right;
				 if (p->info == key && p->left == nullptr && p->right == nullptr)
				 {
					 prev->right = nullptr;
					 delete p;
					 return;
				 }
				else if (p->info == key && p->left == nullptr && p->right != nullptr)
			    {
					 prev->right = p->right;
					 delete p;
					 return;
			    }
				 else if (p->info == key && p->right == nullptr && p->left != nullptr)
				 {
					 prev->right = p->left;
					 delete p;
					 return;
				 }
				 else if (p->info == key && p->right != nullptr && p->left != nullptr)
				 {
					 BTNode<T>* prev2 = p->right;
					 BTNode<T>* p2 = p;
					 while (p2->left != nullptr)
					 {
						 prev2 = p2;
						 p2 = p2->left;
					 }
					 p->info = p2->info;
					 delete p2; prev2->left = nullptr;
					 return;
				 }
			}
		}


	}


	bool isBst()
	{
		return isbst(root);
	}
	bool isbst(BTNode<T>* p)
	{
		if (!root)return true;

		if (p->left && p->left->info > p->info)return false;
		if (p->right && p->right->info < p->info)return false;

		if (p->left)
		{
			bool flag = isbst(p->left);
			if (!flag)return false;
		}
		if (p->left) {
			bool flag = isbst(p->right);
			if (!flag)return false;
		}
		// agar uper kuch bhi false hi hova hai 
		return true;

	}

	int minimum_value()
	{
		if (!root)return 0;
		BTNode<T>* p = root;

		while (p->left != nullptr)
		{
			p = p->left;
		}
		return p->info;


	}

	//void delete_leafNodes()
	//{
	//	delete2(root);
	//}
	//void delete2(BTNode<T>* &p)
	//{
	//	if (p->left == nullptr && p->right == nullptr)
	//	{
	//		delete p;
	//		p = nullptr;
	//		return;
	//	}
	//	else if (p->left != nullptr && p->right != nullptr)
	//	{
	//		//cout << p->info << " ";
	//		delete2(p->left);
	//		delete2(p->right);
	//		
	//	}
	//}

	void LDelete(BTNode<T>* p)
	{
		if (p == nullptr)
			return;
		if (!p->left && !p->right)
		{
			remove(p->info);
			return;
		}
		LDelete(p->left);
		LDelete(p->right);
	}
	void deleteLeaf()
	{
		LDelete(root);
	}


	//practice sets

	int count_nod(BTNode<T>* p)
	{
		int count = 0;
		if (!p)return 0;
		if (!p->left && !p->right)return 1;
		if (p->left)count += count_nod(p->left);
		if (p->right)count += count_nod(p->right);

		return count + 1;

	}

	int count_task1()
	{
		return count_nod(root);
	}
	void printParenthesizedView2()
	{
		printParenthesizedView(root);
	}
	void printParenthesizedView(BTNode<T>* printNode)
	{
		if (!printNode)
			return;
		if (printNode)
			cout << printNode->info;
		if (printNode->left || printNode->right)
			cout << "(";
		if (printNode->left)
			printParenthesizedView(printNode->left);
		if (printNode->left || printNode->right)
			cout << ",";
		if (printNode->right)
			printParenthesizedView(printNode->right);
		if (printNode->left || printNode->right)
			cout << ")";
	}


};

