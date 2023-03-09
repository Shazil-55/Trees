#pragma once
#include <iostream>
#include "math.h"
using namespace std;

template <typename T>
class BinaryTree
{
private:

	int maxHeight;
	T* data;
	bool* nodeStatus;

public:
	BinaryTree(int h)
	{
		nodeStatus = 0;
		maxHeight=pow(2, h)-1;
		data = new T[maxHeight];
		nodeStatus = new bool[maxHeight];
		for (int i = 0; i < maxHeight; i++)
		{
			nodeStatus[i] = false;
		}
	}

	void setRoot(T v)
	{
		data[0] = v;
		nodeStatus[0] = 1;
	}

	T getRoot()
	{
		return data[0];
	}

	// in order to make recursive function 
	int search(int i, T key)
	{
		int status = -1;
		if (data[i] == key)status = i;

		if (status == -1 && 2 * i + 1 < maxHeight && nodeStatus[2 * i + 1 ])
			status = search(2 * i + 1 , key);

		if (status == -1 && 2 * i + 2 < maxHeight && nodeStatus[ 2 * i + 2 ])
			status = search(2 * i + 2, key);

		return status;
	}


	void pre_order_VLR(int i)
	{
		cout << data[i] << " ";

		if ( 2 * i + 1 < maxHeight && nodeStatus[ 2 * i + 1 ])
			 pre_order_VLR(2 * i + 1);

		if ( 2 * i + 2 < maxHeight && nodeStatus[ 2 * i + 2 ])
			pre_order_VLR(2 * i + 2);

	}

	void post_order_LRV(int i)
	{
		

		if (2 * i + 1 < maxHeight && nodeStatus[2 * i + 1])
			post_order_LRV(2 * i + 1);

		if (2 * i + 2 < maxHeight && nodeStatus[2 * i + 2])
			post_order_LRV(2 * i + 2);

		cout << data[i] << " ";
	}

	void in_order_LVR(int i)
	{

		if (2 * i + 1 < maxHeight && nodeStatus[2 * i + 1])
			in_order_LVR(2 * i + 1);

		cout << data[i] << " ";

		if (2 * i + 2 < maxHeight && nodeStatus[2 * i + 2])
			in_order_LVR(2 * i + 2);
		
	}


	void setLeftChild(T parent , T child)
	{
		int i = search(0, parent);
		if (i == -1 || i > maxHeight)return;
		if(2 * i + 1 < maxHeight)
		{
			data[2 * i + 1] = child;
			nodeStatus[2 * i + 1] = 1;
		}
	}

	void setRightChild(T parent, T child)
	{
		int i = search(0, parent);
		if (i == -1 || i > maxHeight)return;
		if (2 * i + 2 < maxHeight)
		{
			data[2 * i + 2] = child;
			nodeStatus[2 * i + 2] = 1;
		}
	}

	int getHeight(int i)
	{
		int h = 1, l = 0, r = 0;
		if (2 * i + 1 < maxHeight && nodeStatus[2 * i + 1])
			l = getHeight(2 * i + 1);
		if (2 * i + 2 < maxHeight && nodeStatus[2 * i + 2])
			r = getHeight(2 * i + 2);
		 
		return h + max(l, r);

	}

	void displayDescendants(T node)
	{
		int index = search(0, node);
		if (index != -1 && index*2+1<maxHeight)
		{
			cout << " The descendants are ";
			pre_order_VLR(index*2+1);
			pre_order_VLR(index * 2 + 2);

		}
	}

	T getParent(T child)
	{
		int index = search(0, child);
		if (index = 0)return;
		int parent_index = (index + 1) / 2;
		return data[parent_index-1];
		/*for (int i = 0; i < maxHeight; i++)
		{
			if (child == data[i])
			{
				int index;
				if (i % 2 == 1) 
				{
					index = i / 2;
				}
				else
				{
					index = (i / 2)-1;
				}
				return data[index];
			}
		}
		return data[maxHeight -1];*/
	}

	void remove(T node)
	{
		for (int i = 0; i < maxHeight; i++)
		{
			if (node == data[i])
			{
				int index,index2;
				index = i * 2 + 1;
				index2 = i * 2 + 2;
				while (index2 < maxHeight)
				{
					nodeStatus[index] = 0;
					nodeStatus[index2] = 0;
					index = index * 2 + 1;
					index2 = index * 2 + 2;
				}

			}
		}
	}

	void display()
	{
		for (int i = 0; i < maxHeight; i++)
		{
			cout << data[i] << " ";
		}
	}

	void display_level(int level)
	{
		int level1 = pow(2, level) - 1;
		int level2 = pow(2, level + 1)-1;
		for (int i = level1; i < level2; i++)
		{
			if (nodeStatus[i])
			{
				cout << data[i] << " ";
			}
		}
	}

	void displayAncestors(T node)
	{

		int i = search(0, node);
			if (i!=-1)
			{
				cout << " Ancestors are ";
				int index = i;
				do
				{
					if (i % 2 == 1)
					{
						index = index / 2;
					}
					else
					{
						index = (index / 2) - 1;
					}
					cout << "->" << data[index];
				} while (data[index] != data[0]);
			}
		
	}


};