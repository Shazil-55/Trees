#pragma once
#include<iostream>
#include "Stack.h"
using namespace std;
template <typename T>
struct AVLNode
{
	T info;
	int height;
	AVLNode<T>* left;
	AVLNode<T>* right;
	AVLNode()
	{
		height = 1;
		left = nullptr;
		right = nullptr;
	}
	AVLNode(T val)
	{
		height = 1;
		info = val;
		left = nullptr;
		right = nullptr;
	}
};

template<typename T>
class AVL
{
	AVLNode<T>* root;
	int calBF(AVLNode<T>* p);
	void updateHeight(AVLNode<T>* p);
	void print(AVLNode<T>* p);
	void LL(AVLNode<T>*, Stack<AVLNode<T>*>&);
	void RR(AVLNode<T>*, Stack<AVLNode<T>*>&);
	void LR(AVLNode<T>*, Stack<AVLNode<T>*>&);
	void RL(AVLNode<T>*, Stack<AVLNode<T>*>&);
public:
	AVL();
	void insert(T node);
	void display();
	void remove(T node);
	bool search(T node);
};

template<typename T>
int AVL<T>::calBF(AVLNode<T>* p)
{
	int bf = 0;
	if (!p)
		return 0;
	if (p->left && p->right)
		bf = p->left->height - p->right->height;
	else if (p->left && !p->right)
		bf = p->left->height;
	else if (!p->left && p->right)
		bf = -(p->right->height);
	return bf;
}

template<typename T>
void AVL<T>::updateHeight(AVLNode<T>* p)
{
	if (!p->left && !p->right)
		p->height = 1;
	else if (p->left && !p->right)
		p->height = 1 + p->left->height;
	else if (!p->left && p->right)
		p->height = 1 + p->right->height;
	else if (p->left && p->right)
		p->height = 1 + max(p->left->height, p->right->height);
}

template<typename T>
void AVL<T>::LL(AVLNode<T>* ptr, Stack<AVLNode<T>*>& stack)
{
	cout << "Left-Left Rotation\n";
	AVLNode<T>* LP = ptr->left;
	AVLNode<T>* RLP = LP->right;
	LP->right = ptr;
	ptr->left = RLP;
	updateHeight(ptr);
	updateHeight(LP);
	if (ptr == root)
		root = LP;
	else
	{
		AVLNode<T>* PP = stack.pop();
		if (ptr == PP->left)
			PP->left = LP;
		else
			PP->right = LP;
		updateHeight(PP);
		while (!stack.isEmpty())
		{
			PP = stack.pop();
			updateHeight(PP);
		}
	}
}

template<typename T>
void AVL<T>::RR(AVLNode<T>* ptr, Stack<AVLNode<T>*>& stack)
{
	cout << "Right-Right Rotation\n";
	AVLNode<T>* RP = ptr->right;
	AVLNode<T>* LRP = RP->left;
	RP->left = ptr;
	ptr->right = LRP;
	updateHeight(ptr);
	updateHeight(RP);
	if (ptr == root)
		root = RP;
	else
	{
		AVLNode<T>* PP = stack.pop();
		if (ptr == PP->left)
			PP->left = RP;
		else
			PP->right = RP;
		updateHeight(PP);
		while (!stack.isEmpty())
		{
			PP = stack.pop();
			updateHeight(PP);
		}
	}
}

template<typename T>
void AVL<T>::LR(AVLNode<T>* ptr, Stack<AVLNode<T>*>& stack)
{
	cout << "Left-Right Rotation\n";
	AVLNode<T>* LP = ptr->left;
	AVLNode<T>* RLP = LP->right;
	AVLNode<T>* LRLP = RLP->left;
	AVLNode<T>* RRLP = RLP->right;
	RLP->left = LP;
	RLP->right = ptr;
	LP->right = LRLP;
	ptr->left = RRLP;
	updateHeight(ptr);
	updateHeight(LP);
	updateHeight(RLP);
	if (ptr == root)
		root = RLP;
	else
	{
		AVLNode<T>* PP = stack.pop();
		if (ptr == PP->left)
			PP->left = RLP;
		else
			PP->right = RLP;
		updateHeight(PP);
		while (!stack.isEmpty())
		{
			PP = stack.pop();
			updateHeight(PP);
		}
	}
}

template<typename T>
void AVL<T>::RL(AVLNode<T>* ptr, Stack<AVLNode<T>*>& stack)
{
	cout << "Right-Left Rotation\n";
	AVLNode<T>* RP = ptr->right;
	AVLNode<T>* LRP = RP->left;
	AVLNode<T>* LLRP = LRP->left;
	AVLNode<T>* RLRP = LRP->right;
	LRP->right = RP;
	LRP->left = ptr;
	RP->left = RLRP;
	ptr->right = LLRP;
	updateHeight(ptr);
	updateHeight(RP);
	updateHeight(LRP);
	if (ptr == root)
		root = LRP;
	else
	{
		AVLNode<T>* PP = stack.pop();
		if (ptr == PP->left)
			PP->left = LRP;
		else
			PP->right = LRP;
		updateHeight(PP);
		while (!stack.isEmpty())
		{
			PP = stack.pop();
			updateHeight(PP);
		}
	}
}

template<typename T>
AVL<T>::AVL()
{
	root = nullptr;
}

template<typename T>
void AVL<T>::insert(T node)
{
	if (!root)
	{
		root = new AVLNode<T>(node);
		return;
	}
	AVLNode<T>* p = root;
	AVLNode<T>* parent = root;
	Stack<AVLNode<T>*> stack;
	while (p)
	{
		parent = p;
		stack.push(p);
		if (node < p->info)
			p = p->left;
		else
			p = p->right;
	}
	bool flag2 = false;
	if (node < parent->info)
		parent->left = new AVLNode<T>(node);
	else
		parent->right = new AVLNode<T>(node);
	AVLNode<T>* ptr = nullptr;
	int BF = 0;
	while (!stack.isEmpty())
	{
		ptr = stack.pop();
		updateHeight(ptr);
		BF = calBF(ptr);
		if (BF < -1 || BF > 1)
		{
			flag2 = true;
			break;
		}
	}
	if (flag2)
	{
		int leftBF = 0;
		int rightBF = 0;
		leftBF = calBF(ptr->left);
		rightBF = calBF(ptr->right);
		if (BF == 2 && leftBF == 1)
			LL(ptr, stack);
		else if (BF == -2 && rightBF == -1)
			RR(ptr, stack);
		else if (BF == -2 && rightBF == 1)
			RL(ptr, stack);
		else if (BF == 2 && leftBF == -1)
			LR(ptr, stack);
	}
}

template<typename T>
void AVL<T>::display()
{
	print(root);
}

template<typename T>
void AVL<T>::print(AVLNode<T>* p)
{
	if (p)
		cout << "Info: " << p->info << " Height: " << p->height << " Balance Factor: " << calBF(p) << endl;
	if (p->left)
		print(p->left);
	if (p->right)
		print(p->right);
}

template<typename T>
void AVL<T>::remove(T node)
{
	if (!root)
		return;
	AVLNode<T>* p = root;
	AVLNode<T>* prev = root;
	Stack<AVLNode<T>*> stack;
	while (p)
	{
		stack.push(p);
		if (p->info == node)
			break;
		prev = p;
		if (node >= p->info)
			p = p->right;
		else
			p = p->left;
	}
	if (p)
	{
		if (!p->left && !p->right)
		{
			if (node < prev->info)
				prev->left = nullptr;
			else
				prev->right = nullptr;
			delete p;
			stack.pop();
		}
		else if (p->left && !p->right || !p->left && p->right)
		{
			if (root->info == node)
			{
				if (root->left)
					root = root->left;
				else
					root = root->right;
			}
			if (node < prev->info)
			{
				if (p->left)
					prev->left = p->left;
				else
					prev->left = p->right;
			}
			else
			{
				if (p->left)
					prev->right = p->left;
				else
					prev->right = p->right;
			}
			delete p;
		}
		else if (p->left && p->right)
		{
			AVLNode<T>* parent = p->right;
			AVLNode<T>* temp = p->right;
			while (temp->left)
			{
				parent = temp;
				temp = temp->left;
			}
			p->info = temp->info;
			if (parent == temp)
				p->right = temp->right;
			else
				parent->left = temp->right;
			delete temp;
		}
	}
	AVLNode<T>* ptr = nullptr;
	bool flag2 = false;
	int BF = 0;
	while (!stack.isEmpty())
	{
		ptr = stack.pop();
		updateHeight(ptr);
		BF = calBF(ptr);
		if (BF < -1 || BF > 1)
		{
			flag2 = true;
			break;
		}
	}
	if (flag2)
	{
		cout << BF << endl;
		cout << ptr->info;
		int leftBF = 0;
		int rightBF = 0;
		leftBF = calBF(ptr->left);
		rightBF = calBF(ptr->right);
		if (BF == 2 && (leftBF == 1 || leftBF == 0))
			LL(ptr, stack);
		else if (BF == -2 && (rightBF == -1 || rightBF == 0))
			RR(ptr, stack);
		else if (BF == -2 && rightBF == 1)
			RL(ptr, stack);
		else if (BF == 2 && leftBF == -1)
			LR(ptr, stack);
	}
}

template<typename T>
bool AVL<T>::search(T node)
{
	AVLNode<T>* p = root;
	while (p != nullptr)
	{
		if (node == p->info)
			return true;
		if (node < p->info)
			p = p->left;
		else
			p = p->right;
	}
	return false;
}

//
//int main()
//{
//	AVL<int> a1;
//	a1.insert(10);
//	a1.insert(20);
//	a1.insert(30);
//	a1.insert(40);
//	a1.insert(50);
//	a1.insert(25);
//
//	a1.display();
//
//}