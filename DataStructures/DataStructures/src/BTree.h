#include <iostream>

template <class T>
class BTreeNode {

public:

	T* data;
	BTreeNode* parent;
	BTreeNode** children;
	bool* exist;
	int order;
	int size;
	BTreeNode(int order) {

		data = new T[order];
		children = new BTreeNode * [order + 1];
		exist = new bool[order];
		parent = nullptr;
		this->order = order;
		size = 0;
		for (int i = 0; i < order; i++) {
			exist[i] = false;
			children[i] = nullptr;
		}
		children[order] = nullptr;
	}
	
	void Add(T key) {

		int i = 0;
		for (; i < size; i++)
			if (data[i] > key)
				break;
		for (int j = size; j > i; j--)
			data[j] = data[j - 1];
		data[i] = key;
		exist[size] = true;
		size++;
	}

	bool isLeaf() {

		for (int i = 0; i < order + 1; i++)
			if (children[i])
				return false;
		return true;
	}

	void print() {
		for (int i = 0; i < size; i++)
			std::cout << data[i] << ' ';
		std::cout << '\n';
	}

	~BTreeNode() {

		delete[] data;
		delete[] children;
		delete[] exist;
	}

};

template <class T, int order>
class BTree {

public:

	int size;
	BTreeNode <T>* root;
	BTree() {
		root = new BTreeNode <T>(order);
	}


	void insert(T key) {
		insertAux(key, root);

	}

	void insertAux(T key, BTreeNode <T>* n) {

		if (n->isLeaf()) {

			n->Add(key);
			insertFix(n);
			return;
		}

		T lastVal = key;
		int i = 0;
		
		for (; i < n->size; i++)
			if (n->exist[i]) {
				if (key < n->data[i] && key >= lastVal) {
					insertAux(key, n->children[i]);
					return;
				}
				lastVal = n->data[i];
			}

		insertAux(key, n->children[i]);
	}

	void insertFix(BTreeNode <T>* n) {

		BTreeNode <T>* r = n, * lChild, * rChild;
		
		while (r->size == order) {
			lChild = new BTreeNode <T> (order);
			rChild = new BTreeNode <T> (order);
			
			// if order is even then the node from the split is taken from the second half
			int j = 0;
			for (; j < order / 2; j++) {
			
				lChild->Add(r->data[j]);
				lChild->children[j] = r->children[j];
				if(lChild->children[j])
					lChild->children[j]->parent = lChild;

			}
			lChild->children[j] = r->children[j];
			if (lChild->children[j])
				lChild->children[j]->parent = lChild;
			j++;
			
			for (; j < order; j++) {
				rChild->Add(r->data[j]);
				rChild->children[j - (order / 2 + 1)] = r->children[j];
				if (rChild->children[j])
				rChild->children[j - (order / 2 + 1)]->parent = rChild;
			}
			rChild->children[j - (order / 2 + 1)] = r->children[j];
			if (rChild->children[j - (order / 2 + 1)])
				rChild->children[j - (order / 2 + 1)]->parent = rChild;

			n = r->parent;
			if (!n) {
				root = new BTreeNode <T>(order);
				n = root;
			}
			int i = 0;
			n->Add(r->data[order / 2]);
			//
			for (; i < n->size; i++)
				if (n->data[i] == r->data[order / 2]) {
					for (int j = n->size; j > i; j--)
						n->children[j] = n->children[j - 1];
					break;
				}

			n->children[i] = lChild;
			n->children[i + 1] = rChild;
			
			lChild->parent = rChild->parent = n;
			delete r;
			r = n;
		}
	}


	void print() {
		printAux(root, 0);
	}
	void printAux(BTreeNode <T>* n, int depth) {
		if (!n)
			return;
		for (int i = 0; i < depth; i++)
			std::cout << ' ';
		n->print();
		for (int i = 0; i < order + 1; i++)
			if (n->children[i])
				printAux(n->children[i], depth + 1);
	}
};
