#include<iostream>
using namespace std;
// me 
template<typename T>
struct AVLNode
{
	T info;
	AVLNode<T>* left = nullptr;
	AVLNode<T>* right = nullptr;
	int height = 1;
	AVLNode()
	{

	}
	AVLNode(T val)
	{
		info = val;
		height = 1;
	}
};

template<typename T>
class AVL
{
private:
	AVLNode<T>* root;

public:
	AVL()
	{
		root = nullptr;
	}

	void remove1(T key)
	{
		if (!search(key))return;
		remove2(key, root);
	}

	void remove3(T key, AVLNode<T>* ptr, AVLNode<T>* prev)
	{
		prev = root;
		if (ptr == nullptr)
		{
			return ;
		}
		else if (key < ptr->info)
		{
			remove3( key , ptr->left,ptr);
		}
		else if (key > ptr->info)
		{
			remove3( key, ptr->right,ptr);
		}
		else
		{
			if (ptr->left == nullptr && ptr->right == nullptr)
			{
				delete ptr;
				ptr = nullptr;
				return ;
			}
			else if (ptr->left && !ptr->right)
			{
				AVLNode<T>* delNode = ptr;
				ptr = ptr->left;
				delete delNode;
				delNode = nullptr;

				return ;
			}
			else if (!ptr->left && ptr->right)
			{
				AVLNode<T>* delNode = ptr;
				ptr = ptr->right;
				delNode = nullptr;
				delete delNode;
				return ;
			}
			else
			{
				AVLNode<T>* succ = ptr->right;
				while (succ->left)
				{
					succ = succ->left;
				}
				ptr->info = succ->info;
				remove3(succ->info , ptr->right,ptr);
			}

		}
		ptr->height = 1 + max(getHeight(ptr->left), getHeight(ptr->right));
		int bf = BalanceFactor(ptr);
		//1 LL case 
		if (bf > 1 && key < ptr->left->info)
		{
			rightRotate(ptr, prev);
		}
		// 2 LR case
		else if (bf > 1 && key > ptr->left->info)
		{
			ptr->left = leftRotate(ptr->left, ptr);
			rightRotate(ptr, prev);

		}
		// 3 RL case
		else if (bf < -1 && key < ptr->right->info)
		{
			ptr->right = rightRotate(ptr->right, ptr);
			leftRotate(ptr, prev);
		}
		// 4 RR case
		else if (bf < -1 && key > ptr->right->info)
		{
			leftRotate(ptr, prev);
		}
	}

	void remove2(T key, AVLNode<T>* p)
	{
		p = root;
		AVLNode<T>* prev = root;
		while (p->info != key)
		{
			if (key < p->info)
			{
				prev = p;
				p = p->left;
			}
			else
			{
				prev = p;
				p = p->right;
			}
		}
		if (prev->info > p->info)	// left side 
		{
			if (p->left == nullptr)
			{
				prev->left = p->left;
				delete p;
				p = nullptr;
			}
			else
			{
				AVLNode<T>* high_node = p;
				while (high_node->right != nullptr)
				{
					high_node = high_node->right;
				}
				p->info = high_node->info;
				delete high_node;
				high_node = nullptr;
			}
		}
		else// right side 
		{
			if (p->left == nullptr)
			{
				prev->right = p->right;
				delete p;
				p = nullptr;
			}
			else
			{
				AVLNode<T>* small_node = p;
				while (small_node->left != nullptr)
				{
					small_node = small_node->left;
				}
				p->info = small_node->info;
				delete small_node;
				small_node = nullptr;
			}
			
		}
	}

	int BalanceFactor(AVLNode<T>*ptr)
	{
		if (ptr == nullptr)return 0;
		return getHeight(ptr->left) - getHeight(ptr->right);
	}

	int getHeight(AVLNode<T>*p)
	{
		if (p == nullptr)return 0;
		return p->height;

	}

	void insert2(AVLNode<T>* p, T key, AVLNode<T>* prev)
	{
			if (key < p->info)
			{
				if (p->left)
				{
					insert2(p->left, key, p);
				}
				else
				{
					p->left = new AVLNode<T>(key);
				}
			}
			else if (key > p->info)
			{
				if (p->right)
				{
					insert2(p->right, key, p);
				}
				else
				{
					p->right = new AVLNode<T>(key);
				}
			}
			p->height = 1 + max(getHeight(p->left), getHeight(p->right));
			int bf = BalanceFactor(p);
			//1 LL case 
			if (bf > 1 && key < p->left->info)
			{
				rightRotate(p, prev);
			}
			// 2 LR case
			else if (bf > 1 && key > p->left->info)
			{
				p->left = leftRotate(p->left, p);
				rightRotate(p, prev);

			}
			// 3 RL case
			else if (bf < -1 && key < p->right->info)
			{
				p->right = rightRotate(p->right, p);
				leftRotate(p, prev);
			}
			// 4 RR case
			else if (bf < -1 && key > p->right->info)
			{
				leftRotate(p, prev);
			}
			return;
		
	}

	AVLNode<T>* rightRotate(AVLNode<T>*pivot, AVLNode<T>* pp)
	{
		cout << " R_R ";
		AVLNode<T>* lp=pivot->left;
		AVLNode<T>* rlp = nullptr;
		if (lp->right!=nullptr) rlp=lp->right;
		if (pivot == root)
		{
			lp->right = pivot;
			pivot->left = rlp;
		}
		else
		{
			lp->right = pivot;
			if (pp != root)
			{
				/*int bf = BalanceFactor(pp);
				if (bf > 1)pp->left = lp;
				else
				{
					pp->right = lp;
				}*/
				pp->left = lp;
			}
			else
			{
				root->left = lp;
			}
			pivot->left = rlp;
		}
		pivot->height = 1 + max(getHeight(pivot->left), getHeight(pivot->right));
		lp->height = 1 + max(getHeight(lp->left), getHeight(lp->right));

		return lp;
	}

	AVLNode<T>* leftRotate(AVLNode<T>* pivot, AVLNode<T>* pp)
	{
		AVLNode<T>* rp = pivot->right;
		AVLNode<T>* lrp = nullptr;
		if (rp->left != nullptr) lrp = rp->left;
		int bf = BalanceFactor(pp);
		rp->left = pivot;
		if (pp != root)
		{
			if (bf > 1)pp->left = rp;
			else
			{
				pp->right = rp;
			}
		}
		else
		{
			root->left = rp;
		}
		pivot->right = lrp;

		pivot->height = 1 + max(getHeight(pivot->left), getHeight(pivot->right));
		rp->height = 1 + max(getHeight(rp->left), getHeight(rp->right));

		return rp;
	} 

	void VLR()
	{
		VLR_2(root);
	}  
	void VLR_2(AVLNode<T>* p)
	{
		if (p == nullptr)return;
		if (p != nullptr)cout << p->info << " " << p->height  <<  endl;
		if (p->left)
			VLR_2(p->left);
		if (p->right)
			VLR_2(p->right);
	}

	void insert(T key)
	{
		if (!root)
		{
			root = new AVLNode<T>(key);
			return;
		}
		else
		{
			insert2(root, key,root);
		}
	}

	bool search(T key)
	{
		AVLNode<T>* p = root;
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

};