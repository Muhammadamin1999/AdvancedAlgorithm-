
#include "BST.cpp"

template<class k, class v>
class AVL : public BST<k, v>
{
public:
	AVL() {}

	AVL(const AVL& obj) {
		this->root = nullptr;
		cAVL(this->root, obj.root);
	}

	void insert(k const key, v const value) {
		insert(key, value, this->root);
	}

	int height() const {
		return this->root->height;
	}

	~AVL() {}

private:
	void RotateLeft(TNode<k, v>*& x) {
		TNode<k, v>* y = x->rightChild;
		x->rightChild = y->leftChild;
		y->leftChild = x;
		x->height = 1 + max(geth(x->rightChild), geth(x->leftChild));
		y->height = 1 + max(geth(y->rightChild), geth(y->leftChild));
		x = y;
	}

	void RotateRight(TNode<k, v>*& x) {
		TNode<k, v>* y = x->leftChild;
		x->leftChild = y->rightChild;
		y->rightChild = x;
		x->height = 1 + max(geth(x->rightChild), geth(x->leftChild));
		y->height = 1 + max(geth(y->rightChild), geth(y->leftChild));
		x = y;
	}

	void DRotateRight(TNode<k, v>*& x) {
		RotateLeft(x->leftChild);
		RotateRight(x);
	}

	void DRotateLeft(TNode<k, v>*& x) {
		RotateRight(x->rightChild);
		RotateLeft(x);
	}

	int geth(TNode<k, v>* nd) {
		if (nd)
		{
			return nd->height;
		}
		return -1;
	}

	void insert(k const key, v const value, TNode<k, v>*& nd) {
		if (nd == nullptr)
		{
			nd = new TNode<k, v>;
			nd->value = value;
			nd->key = key;
			nd->leftChild = nullptr;
			nd->rightChild = nullptr;
			nd->height = 0;
			return;
		}
		else if (nd->key == key)
		{
			return;
		}
		else if (nd->key > key)
		{
			insert(key, value, nd->leftChild);
			if (geth(nd->leftChild) - geth(nd->rightChild) == 2)
			{
				if (key < nd->leftChild->key) //case 2
				{
					RotateRight(nd);
				}
				else //case 4
				{
					DRotateRight(nd);
				}
			}
		}
		else
		{
			insert(key, value, nd->rightChild);
			if (geth(nd->leftChild) - geth(nd->rightChild) == -2)
			{
				if (key > nd->rightChild->key) //case 1
				{
					RotateLeft(nd);
				}
				else //case 3
				{
					DRotateLeft(nd);
				}
			}
		}
		nd->height = 1 + max(geth(nd->leftChild), geth(nd->rightChild));
	}

	void cAVL(TNode<k, v>*& node, TNode<k, v>* node1) {
		if (node1)
		{
			node = new TNode<k, v>;
			node->height = node1->height;
			node->key = node1->key;
			node->value = node1->value;
			cAVL(node->leftChild, node1->leftChild);
			cAVL(node->rightChild, node1->rightChild);
		}
		else
		{
			node = nullptr;
		}
	}
};
