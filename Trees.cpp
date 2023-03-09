#include <iostream>
#include "BinaryTree.h"
#include "BST.h"
#include "AVL.h"
#include "LinkBinaryTree.h"
using namespace std;

int main()
{
	AVL<int> b1;
	b1.insert(15);
	b1.insert(10);
	//b1.insert(100);
	b1.insert(5);	
	//b1.insert(12);
	//b1.insert(3);
	//b1.insert(7);
	//b1.insert(1);
	b1.VLR();
	//b1.printParenthesizedView2();


//	b1.remove(30);
	//b1.setLeftChild(5, 7);
//cout << 	b1.count_task1();
	//cout << endl;
	////cout << endl << b1.isBst();
	//cout << endl;
	//b1.remove(10);
	//b1.delete_leafNodes();
	//b1.deleteLeaf();
	//cout << endl;
	//b1.VLR();



	//cout << b1.minimum_value();
	//cout << endl << b1.countLeafNodes();

	//LinkBinaryTree<string> b1;

	//b1.setRoot("A");
	///*cout << b1.getRoot();
	//b1.setLeftChild("A", "B");
	//cout << b1.getParent("c");*/

	
	//b1.setLeftChild("A", "B");
	//b1.VLR();
	//b1.setRightChild("A", "C");
	//b1.setLeftChild("B", "D");
	//b1.setRightChild("B", "E");
	//b1.setLeftChild("E", "F");
	////b1.remove("B");
	////cout  << b1.getHeight(0);
	//	b1.in_order_LVR(0);
	//	cout << endl;
	//	b1.pre_order_VLR(0);
	//	cout << endl;
	//	b1.post_order_LRV(0);
	//	cout << endl;
	//	b1.displayDescendants("B");
	//	cout << endl;
	//	b1.displayAncestors("F");
	//	cout << endl;
	//	b1.display_level(2);
	//	cout << endl;




	//b1.display();
}