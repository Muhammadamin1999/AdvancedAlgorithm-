
#include <iostream>
using namespace std;

template<typename k, typename v>
struct TNode
{
	k key;
	v value;
	int height;
	TNode<k, v>* leftChild;
	TNode<k, v>* rightChild;
};

template<class k, class v>
class BST
{
public:
	BST() {
		root = nullptr;
	}

	BST(const BST& obj) {
		root = nullptr;
		cBST(obj.root);
	}

	void insert(k const key, v const value) {
		insert(key, value, root);
	}

	v* search(k key) {
		return search(key, root);
	}

	void inorderPrintKeys() const {
		inorderPrintKeys(root);
	}

	int length() const {
		return length(root);
	}

	void deleteKey(k key) {
		deleteKey(key, root);
	}

	~BST() {
		destructTree(root);
	}

private:
	void insert(k key, v d, TNode<k, v>*& r) {
		if (r == nullptr)
		{
			TNode<k, v>* temp = new TNode<k, v>;
			temp->key = key;
			temp->value = d;
			temp->leftChild = nullptr;
			temp->rightChild = nullptr;
			r = temp;
		}
		else if (key == r->key)
		{
			return;
		}
		else if (key < r->key)
		{
			insert(key, d, r->leftChild);
		}
		else
		{
			insert(key, d, r->rightChild);
		}
	}

	void cBST(TNode<k, v>* node) {
		if (node != nullptr)
		{
			insert(node->key, node->value);
			cBST(node->leftChild);
			cBST(node->rightChild);
		}
	}

	v* search(k key, TNode<k, v>* r) {
		if (r == nullptr)
		{
			return nullptr;
		}
		else if (r->key == key)
		{
			return &(r->value);
		}
		else if (key < r->key)
		{
			return search(key, r->leftChild);
		}
		else
		{
			return search(key, r->rightChild);
		}
	}

	void inorderPrintKeys(TNode<k, v>* r) const {
		if (r != nullptr)
		{
			inorderPrintKeys(r->leftChild);
			cout << r->key << " ";
			inorderPrintKeys(r->rightChild);
		}
	}

	int length(TNode<k, v>* r) const {
		if (!r)
		{
			return 0;
		}
		return 1 + length(r->leftChild) + length(r->rightChild);
	}

	void deleteKey(k key, TNode<k, v>*& r) {
		if (r == nullptr)
		{
			return;
		}
		else if (key < r->key)
		{
			deleteKey(key, r->leftChild);
		}
		else if (key > r->key)
		{
			deleteKey(key, r->rightChild);
		}
		else //key found
		{
			if (!r->leftChild && !r->rightChild) //case 1
			{
				delete r;
				r = nullptr;
			}
			else if (r->leftChild != nullptr && r->rightChild != nullptr) //case 3
			{
				TNode<k, v>* nd = getmax(r->leftChild);
				r->key = nd->key;
				r->value = nd->value;
				deleteKey(nd->key, r->leftChild);
			}
			else //case 2
			{
				TNode<k, v>* temp = nullptr;
				if (r->rightChild)
				{
					temp = r->rightChild;
				}
				else
				{
					temp = r->leftChild;
				}
				delete r;
				r = temp;
			}
		}
	}

	TNode<k, v>* getmax(TNode<k, v>* r) const {
		while (r->rightChild)
		{
			r = r->rightChild;
		}
		return r;
	}

	void destructTree(TNode<k, v>*& r) {
		if (r)
		{
			destructTree(r->leftChild);
			destructTree(r->rightChild);
			delete r;
			r = nullptr;
		}
	}

protected:
	TNode<k, v>* root;
};
