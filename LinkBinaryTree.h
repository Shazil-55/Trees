#ifndef LINKBINARYTREE_H
#define LINKBINARYTREE_H

// cs-19
#include "Queue.h"
#include "Stack.h"

using namespace std;

template<typename T>
struct BTNode
{
	T info;
	BTNode<T>* left;
	BTNode<T>* right;
	BTNode()
	{
		left = right = nullptr;
	}
	BTNode(T val)
	{
		info = val;
		left = right = nullptr;
	}

};

template<typename T>
class LinkBinaryTree
{
	BTNode<T>* root;
	BTNode<T>* search(T key, BTNode<T>* node)
	{
		BTNode<T>* res = nullptr;
		if (node->info == key)
			res = node;
		if (res == nullptr && node->left)
			res = search(key, node->left);
		if (res == nullptr && node->right)
			res = search(key, node->right);
		return res;
	}
	BTNode<T>* getParent(T key, BTNode<T>* node)
	{
		BTNode<T>* res = nullptr;
		if (node->left && node->left->info == key || node->right && node->right->info == key)
			res = node;
		if (res == nullptr && node->left)
			res = getParent(key, node->left);
		if (res == nullptr && node->right)
			res = getParent(key, node->right);
		return res;
	}
	void VLR(BTNode<T>* printNode)
	{
		if (printNode)
			cout << printNode->info << ":";
		if (printNode->left)
			VLR(printNode->left);
		if (printNode->right)
			VLR(printNode->right);
	}
	void removeNode(BTNode<T>* p)
	{
		if (p->left)
			removeNode(p->left);
		if (p->right)
			removeNode(p->right);
		delete p;
	}
	//-------------------<Private Functions for hometask>------------------------------------//
	//1)
	int countNodes(BTNode<T>* node)
	{
		if (!node)
			return 0;
		int sumNode1 = 0, sumNode2 = 0;
		if (node->left)
			sumNode1 = countNodes(node->left);
		if (node->right)
			sumNode2 = countNodes(node->right);
		return sumNode1 + sumNode2 + 1;
	}
	//2)
	T minValue(BTNode<T>* node)
	{
		T minimumValue = node->info;
		if (node->left)
		{
			T leftResultValue = minValue(node->left);
			if (minimumValue > leftResultValue)
			{
				minimumValue = leftResultValue;
			}
		}
		\
		if (node->right)
		{
			T rightResultValue = minValue(node->right);
			if (minimumValue > rightResultValue)
			{
				minimumValue = rightResultValue;
			}
		}
		return minimumValue;
	}
	//3)
	int countLeafNodes(BTNode<T>* node)
	{
		if (!node)
			return 0;
		int res1 = 0, res2 = 0;
		if (node->left)
			res1 = countLeafNodes(node->left);
		if (node->right)
			res2 = countLeafNodes(node->right);
		if (res1 == 0 && res2 == 0)
			return 1;
		return res1 + res2;
	}
	//7)
	int isFull(BTNode<T>* node)
	{
		if (!node)
			return 1;
		int res = 0;
		if (node->left && node->right)
		{
			res = isFull(node->left);
			if (res == 1)
				res = isFull(node->right);
		}
		else if (!node->left && !node->right)
		{
			return 1;
		}
		return res;
	}
	//8)
	int getHeight(BTNode<T>* node)
	{
		if (!node)
			return 0;
		int leftTreeHeight = 0, rightTreeHeight = 0;
		if (node->left)
			leftTreeHeight = getHeight(node->left);
		if (node->right)
			rightTreeHeight = getHeight(node->right);
		if (leftTreeHeight > rightTreeHeight)
			return leftTreeHeight + 1;
		else
			return rightTreeHeight + 1;
	}
	//9)
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
	//10/11)
	void copyObjectVLR(BTNode<T>*& nodeObj, BTNode<T>* nodeCopy)
	{
		if (!nodeCopy)
			return;
		nodeObj = new BTNode<T>(nodeCopy->info);
		nodeObj->info = nodeCopy->info;
		if (nodeCopy->left)
			copyObjectVLR(nodeObj->left, nodeCopy->left);
		if (nodeCopy->right)
			copyObjectVLR(nodeObj->right, nodeCopy->right);
	}
	//12)
	void displayLevel(BTNode<T>* node, int keyLevelNo, int levelNumber = 0)
	{
		if (!node)
			return;
		if (levelNumber == keyLevelNo - 1)
		{
			cout << node->info << ":";
			return;
		}
		else if (levelNumber < keyLevelNo - 1)
		{
			if (node->left)
				displayLevel(node->left, keyLevelNo, levelNumber + 1);
			if (node->right)
				displayLevel(node->right, keyLevelNo, levelNumber + 1);
		}
	}
	//13)
	int findLevelOfNode(BTNode<T>* node, int key, int levelNumber = 0)
	{
		if (!node)
			return -1;
		if (node->info == key)
			return levelNumber;
		int res = -1;
		if (res == -1 && node->left)
			res = findLevelOfNode(node->left, key, levelNumber + 1);
		if (res == -1 && node->right)
			res = findLevelOfNode(node->right, key, levelNumber + 1);
		return res;
	}
	//14)
	int isIsomorphic(BTNode<T>* nodeObj1, BTNode<T>* nodeObj2)
	{
		if (nodeObj1->info != nodeObj2->info)
			return 0;
		int resultLeft = 0, resultRight = 0;
		if (!nodeObj1->left && !nodeObj2->left)
		{
			resultLeft = 1;
			if (!nodeObj1->right && !nodeObj2->right)
				resultRight = 1;
			else if (nodeObj1->right && nodeObj2->right)
				resultRight = isIsomorphic(nodeObj1->right, nodeObj2->right);

		}
		else if (nodeObj1->left && nodeObj2->left)
		{
			resultLeft = isIsomorphic(nodeObj1->left, nodeObj2->left);
			if (!nodeObj1->right && !nodeObj2->right)
				resultRight = 1;
			else if (nodeObj1->right && nodeObj2->right)
				resultRight = isIsomorphic(nodeObj1->right, nodeObj2->right);
		}
		if ((resultRight == 0 || resultLeft == 0) && !nodeObj1->left && !nodeObj2->right)
		{
			resultLeft = 1;
			resultRight = 0;
			if (!nodeObj1->right && !nodeObj2->left)
				resultRight = 1;
			else if (nodeObj1->right && nodeObj2->left)
				resultRight = isIsomorphic(nodeObj1->right, nodeObj2->left);
		}
		else if ((resultRight == 0 || resultLeft == 0) && nodeObj1->left && nodeObj2->right)
		{
			resultLeft = resultRight = 0;
			resultLeft = isIsomorphic(nodeObj1->left, nodeObj2->right);
			if (!nodeObj1->right && !nodeObj2->left)
				resultRight = 1;
			else if (nodeObj1->right && nodeObj2->left)
				resultRight = isIsomorphic(nodeObj1->right, nodeObj2->left);
		}
		if (resultLeft == 0 || resultRight == 0)
			return 0;
		else
			return 1;
	}
	//15)
	int isBTIsomorphic(BTNode<T>* nodeObj1, BTNode<T>* nodeObj2)
	{
		if (nodeObj1->info != nodeObj2->info)
			return 0;
		int resultLeft = 0, resultRight = 0;
		if (!nodeObj1->left && !nodeObj2->left)
			resultLeft = 1;
		else if (nodeObj1->left && nodeObj2->left)
			resultLeft = isBTIsomorphic(nodeObj1->left, nodeObj2->left);
		if (!nodeObj1->right && !nodeObj2->right)
			resultRight = 1;
		else if (nodeObj1->right && nodeObj2->right)
			resultRight = isBTIsomorphic(nodeObj1->right, nodeObj2->right);
		if (resultLeft == 0 || resultRight == 0)
			return 0;
		else
			return 1;
	}
	//16)
	int isMirror(BTNode<T>* nodeObj1, BTNode<T>* nodeObj2)
	{
		if (nodeObj1->info != nodeObj2->info)
			return 0;
		int resultLeft = 0, resultRight = 0;
		if (!nodeObj1->left && !nodeObj2->right)
		{
			resultLeft = 1;
			if (!nodeObj1->right && !nodeObj2->left)
				resultRight = 1;
			else if (nodeObj1->right && nodeObj2->left)
				resultRight = isMirror(nodeObj1->right, nodeObj2->left);
		}
		else if (nodeObj1->left && nodeObj2->right)
		{
			resultLeft = isMirror(nodeObj1->left, nodeObj2->right);
			if (!nodeObj1->right && !nodeObj2->left)
				resultRight = 1;
			else if (nodeObj1->right && nodeObj2->left)
				resultRight = isMirror(nodeObj1->right, nodeObj2->left);

		}
		if (resultLeft == 0 || resultRight == 0)
			return 0;
		else
			return 1;
	}
	//17)
	void displayLongestPath(BTNode<T>* node, Queue<T>& longestPath, Queue<T> pathFollowed = {})
	{
		if (!node)
			return;
		pathFollowed.enQueue(node->info);
		if (!node->left && !node->right)
		{
			if (longestPath.getNoOfElements() < pathFollowed.getNoOfElements())
			{
				longestPath.~Queue();
				while (!pathFollowed.isEmpty())
				{
					longestPath.enQueue(pathFollowed.deQueue());
				}
			}
			return;
		}
		if (node->left)
			displayLongestPath(node->left, longestPath, pathFollowed);
		if (node->right)
			displayLongestPath(node->right, longestPath, pathFollowed);
	}

	//18)
	void displayAllPaths(BTNode<T>* node, Queue<T> pathFollowed = {})
	{
		if (!node)
			return;
		pathFollowed.enQueue(node->info);
		if (!node->left && !node->right)
		{
			cout << "Path:";
			while (!pathFollowed.isEmpty())
			{
				cout << pathFollowed.deQueue();
				if (!pathFollowed.isEmpty())
				{
					cout << "---";
				}
			}
			cout << endl;
			return;
		}
		if (node->left)
			displayAllPaths(node->left, pathFollowed);
		if (node->right)
			displayAllPaths(node->right, pathFollowed);
	}
	//19)
	void displayAllPathsLength(BTNode<T>* node, Queue<T> pathFollowed = {})
	{
		if (!node)
			return;
		pathFollowed.enQueue(node->info);
		if (!node->left && !node->right)
		{
			cout << "Path:";
			int pathLength = pathFollowed.getNoOfElements();
			while (!pathFollowed.isEmpty())
			{
				cout << pathFollowed.deQueue();
				if (!pathFollowed.isEmpty())
				{
					cout << "---";
				}
			}
			cout << "=" << pathLength << endl;
			return;
		}
		if (node->left)
			displayAllPathsLength(node->left, pathFollowed);
		if (node->right)
			displayAllPathsLength(node->right, pathFollowed);
	}
	//20)
	int lowestCommonAncestor(BTNode<T>* node, T a, T b, T& ancestorNode, bool& childFound)
	{
		if (!node)
			exit(0);
		int foundNodes = 0, leftFound = 0, rightFound = 0;
		if (node->info == a)
			foundNodes++;
		if (node->info == b)
			foundNodes++;
		if (foundNodes != 2 && node->left)
			leftFound = lowestCommonAncestor(node->left, a, b, ancestorNode, childFound);
		if (foundNodes != 2 && node->right)
			rightFound = lowestCommonAncestor(node->right, a, b, ancestorNode, childFound);
		if (!childFound && (foundNodes + leftFound + rightFound == 2))
		{
			ancestorNode = node->info;
			childFound = true;
		}
		return foundNodes + leftFound + rightFound;
	}
	//21)
	int findDistance(BTNode<T>* node, T a, T b, bool& childFound, int& aDepth, int& bDepth, int& ancestorDepth, int levelNumber = 0)
	{
		if (!node)
			exit(0);
		levelNumber = levelNumber + 1;
		int foundNodes = 0, leftFound = 0, rightFound = 0;
		if (node->info == a)
		{
			aDepth = levelNumber;
			foundNodes++;
		}
		if (node->info == b)
		{
			bDepth = levelNumber;
			foundNodes++;
		}
		if (foundNodes != 2 && node->left)
			leftFound = findDistance(node->left, a, b, childFound, aDepth, bDepth, ancestorDepth, levelNumber);
		if (foundNodes != 2 && node->right)
			rightFound = findDistance(node->right, a, b, childFound, aDepth, bDepth, ancestorDepth, levelNumber);
		if (!childFound && (foundNodes + leftFound + rightFound == 2))
		{
			ancestorDepth = levelNumber;
			childFound = true;
		}
		return foundNodes + leftFound + rightFound;
	}
	//22)
	int findDiameter(BTNode<T>* node, int& largestDiameter)
	{
		if (!node)
			return 0;
		int leftDiameter = 0, rightDiamter = 0;
		if (node->left)
			leftDiameter = findDiameter(node->left, largestDiameter);
		if (node->right)
			rightDiamter = findDiameter(node->right, largestDiameter);
		if (leftDiameter + rightDiamter > largestDiameter)
			largestDiameter = leftDiameter + rightDiamter;
		if (leftDiameter > rightDiamter)
			return leftDiameter + 1;
		else
			return rightDiamter + 1;
	}
public:
	LinkBinaryTree()
	{
		root = nullptr;
	}
	void  setRoot(T rootValue)
	{
		if (!root)
			root = new BTNode<T>(rootValue);
		else
			root->info = rootValue;
	}
	void setLeftChild(T parentKey, T value)
	{
		BTNode<T>* p = search(parentKey, root);
		if (p == nullptr)
			return;
		if (p->left)
			p->left->info = value;
		else
			p->left = new BTNode<T>(value);
	}
	void setRightChild(T parentKey, T value)
	{
		BTNode<T>* p = search(parentKey, root);
		if (p == nullptr)
			return;
		if (p->right)
			p->right->info = value;
		else
			p->right = new BTNode<T>(value);
	}
	void preOrder()
	{
		VLR(root);
	}
	T getParent(T value)
	{
		BTNode<T>* parentNode = getParent(value, root);
		if (parentNode)
			return parentNode->info;
		exit(0);
	}
	~LinkBinaryTree()
	{
		if (root)
			removeNode(root);
		root = nullptr;
	}
	void remove(T node)
	{
		if (node == root->info)
		{
			this->~LinkBinaryTree();
			return;
		}
		BTNode<T>* parentNode = getParent(node, root);
		if (!parentNode)
			return;
		if (parentNode->left && parentNode->left->info == node)
		{
			removeNode(parentNode->left);
			parentNode->left = nullptr;
		}
		if (parentNode->right && parentNode->right->info == node)
		{
			removeNode(parentNode->right);
			parentNode->right = nullptr;
		}
	}
	void displayDescedents(T node)
	{
		BTNode<T>* parentNode = search(node, root);
		if (!parentNode)
			return;
		if (parentNode->left && parentNode->right)
		{
			VLR(parentNode->left);
			VLR(parentNode->right);
		}
	}

	void levelOrder()
	{
		if (!root)
			return;
		Queue <BTNode<T>*> nodesInLevel;
		nodesInLevel.enQueue(root);
		while (!nodesInLevel.isEmpty())
		{
			BTNode<T>* tempNode = nodesInLevel.deQueue();
			cout << tempNode->info << ":";
			if (tempNode->left)
				nodesInLevel.enQueue(tempNode->left);
			if (tempNode->right)
				nodesInLevel.enQueue(tempNode->right);
		}
		cout << endl;
	}
	int getHeight()
	{
		return getHeight(root);
	}
	//------------------- <HomeTask>------------------------//
	//1)
	int countNodes()
	{
		if (root)
			return countNodes(root);
		return 0;
	}
	//2)
	T minValue()
	{
		if (root)
			return minValue(root);
		exit(0);
	}
	//3)
	int countLeafNodes()
	{
		if (root)
			return countLeafNodes(root);
		return 0;
	}
	//4)
	void nonRecPreOrder()
	{
		if (!root)
			return;
		BTNode<T>* tempNode = root;
		Stack<BTNode<T>*> nodeInStack;
		do
		{
			if (tempNode == nullptr)
			{
				tempNode = nodeInStack.pop();
				tempNode = tempNode->right;
			}
			cout << tempNode->info << ":";
			if (tempNode->right)
				nodeInStack.push(tempNode);
			tempNode = tempNode->left;
		} while (!nodeInStack.isEmpty());
		cout << endl;
	}
	//5)
	void nonRecPostOrder()
	{
		if (!root)
			return;
		BTNode<T>* tempNode = root;
		int isPreviousNode = 0;
		Stack<BTNode<T>*> nodeInStack;
		nodeInStack.push(tempNode);
		do
		{
			if (isPreviousNode == 0)
			{
				if (tempNode->right)
					nodeInStack.push(tempNode->right);
				if (tempNode->left)
					nodeInStack.push(tempNode->left);
				if (tempNode->left)
					tempNode = tempNode->left;
				else if (tempNode->right)
					tempNode = tempNode->right;
			}
			if (isPreviousNode == 1 || !tempNode->left && !tempNode->right)
			{
				nodeInStack.pop();
				isPreviousNode = 0;
				cout << tempNode->info << ":";
				if (!nodeInStack.isEmpty())
				{
					BTNode<T>* tempParentNode = nodeInStack.stackTop();
					if (tempParentNode->left == tempNode || tempParentNode->right == tempNode)
						isPreviousNode = 1;
					tempNode = nodeInStack.stackTop();
				}
			}

		} while (!nodeInStack.isEmpty());
		cout << endl;
	}
	//6)
	void nonRecInOrder()
	{
		if (!root)
			return;
		BTNode<T>* tempNode = root;
		Stack<BTNode<T>*> nodeInStack;
		do
		{
			if (tempNode == nullptr)
			{
				tempNode = nodeInStack.pop();
				cout << tempNode->info << ":";
				tempNode = tempNode->right;
			}
			else
			{
				if (tempNode->left)
				{
					nodeInStack.push(tempNode);
					tempNode = tempNode->left;
				}
				else
				{
					cout << tempNode->info << ":";
					tempNode = tempNode->right;
				}
			}
		} while (!nodeInStack.isEmpty() || tempNode);
		cout << endl;
	}
	//7)
	int isFull()
	{
		return isFull(root);
	}
	//8)
	int findBalanceFactor(T val)
	{
		BTNode<T>* nodeBalance = search(val, root);
		if (!nodeBalance)
			exit(0);
		return getHeight(nodeBalance->left) - getHeight(nodeBalance->right);
	}
	//9)
	void printParenthesizedView()
	{
		if (!root)
			return;
		printParenthesizedView(root);
	}
	//10)
	LinkBinaryTree<T>& operator = (const LinkBinaryTree<T>& rhs)
	{
		if (this == &rhs)
			return *this;
		this->~LinkBinaryTree();
		if (!rhs.root)
			return *this;
		copyObjectVLR(root, rhs.root);
		return *this;
	}
	//11)
	LinkBinaryTree(const LinkBinaryTree<T>& obj) :LinkBinaryTree()
	{
		if (!obj.root)
			return;
		copyObjectVLR(root, obj.root);
	}
	//12
	void displayLevel(int levelNo)
	{
		displayLevel(root, levelNo);
		cout << endl;
	}
	//13)

	int findLevelOfNode(T node)
	{
		int keyLevel = findLevelOfNode(root, node);
		if (keyLevel != -1)
			return keyLevel + 1;
		return keyLevel;
	}
	//14)
	int isIsomorphic(LinkBinaryTree<T>& obj)
	{
		return isIsomorphic(root, obj.root);
	}
	//15)
	int isBTIsomorphic(LinkBinaryTree<T>& obj)
	{
		return isBTIsomorphic(root, obj.root);
	}
	//16)
	int isMirror(LinkBinaryTree<T>& obj)
	{
		return isMirror(root, obj.root);
	}
	//17)
	void displayLongestPath()
	{
		Queue<T> pathLongest;
		displayLongestPath(root, pathLongest);
		while (!pathLongest.isEmpty())
		{
			cout << pathLongest.deQueue();
			if (!pathLongest.isEmpty())
			{
				cout << "---";
			}
		}
		cout << endl;
	}
	//18)
	void displayAllPaths()
	{
		if (!root)
			return;
		displayAllPaths(root);
	}
	//19)
	void displayAllPathsLength()
	{
		if (!root)
			return;
		displayAllPathsLength(root);
	}
	//20)
	T lowestCommonAncestor(T a, T b)
	{
		if (!root)
			exit(0);
		T ancestorNode;
		bool childFound = false;
		int foundNodes = lowestCommonAncestor(root, a, b, ancestorNode, childFound);
		if (childFound)
			return ancestorNode;
		else
			exit(0);
	}
	//21)
	int findDistance(T a, T b)
	{
		if (!root)
			exit(0);
		int  aDepth, bDepth, ancestorDepth;
		bool childFound = false;
		int foundNodes = findDistance(root, a, b, childFound, aDepth, bDepth, ancestorDepth);
		if (childFound)
			return aDepth + bDepth - (2 * ancestorDepth);
		else
			exit(0);
	}
	//22)
	int findDiameter()
	{
		if (!root)
			return 0;
		int largestDiamter = 0;
		findDiameter(root, largestDiamter);
		return largestDiamter;
	}
};

#endif // !LINKBINARYTREE_H
