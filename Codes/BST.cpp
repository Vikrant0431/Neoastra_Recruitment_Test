#include<bits/stdc++.h>
using namespace std;

typedef vector<int> KEY;
typedef int T;


struct Elem {
	KEY key;
	T data;
	Elem *left;
	Elem *right;
	bool rightThread; //normal right child link or a threadlink
};
Elem *_root; // a dummy root sentinel
int _size;
Elem *_lastLeft;

// helper method for creating a new node of tree
struct Elem *createNew(const T &data) {
	// Allocate memory for new node
	struct Elem *elem = (struct Elem*)malloc(sizeof(struct Elem));
	elem->data = data;
	elem->left = NULL;
	elem->right = NULL;
	elem->rightThread = false;
	return elem;
}

// helper method for inserting record into tree.
bool insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft) {
	Elem *newElem = createNew(data);
	Elem *current = root;
	Elem *parent = NULL;
	while (true) {
		parent = current;
		if (data == current->data)
        {
            cout<<"Duplicate Key !"<<endl;
            return false;
        }
		if (data < current->data) {
		    current = current->left;
			if (current == NULL) {
				parent->left = newElem;
				newElem->right = parent;
				newElem->rightThread = true;
				lastLeft = newElem;
				_size++;
				return true;
			}
		} else {
			if(current->rightThread == false){
				current = current->right;
				if(current == NULL){
					parent->right = newElem;
					_size++;
					return true;
				}
			} else {
				Elem *temp = current->right;
				current->right = newElem;
				newElem->right = temp;
				newElem->rightThread = true;
				_size++;
				return true;
			}
		}
	}
}

Elem *leftMostNode(Elem *node){
	if (node == NULL) {
		return NULL;
	} else {
		while (node->left != NULL) {
			node = node->left;
		}
		return node;
	}
}

// helper method for print tree
void printTree(ostream& out, int level, Elem *p) {
	Elem *current = leftMostNode(_root);
	while (current != NULL) {
		out<<" "<<current->data;
		if (current->rightThread) {
			current = current->right;
		} else {
			current = leftMostNode(current->right);
		}
	}
	out<<endl;
}

// common code for deallocation
void destructCode(Elem *& p) {
	Elem *current = leftMostNode(_root);
	Elem *temp = NULL;
	while (current != NULL) {
		cout<<"Deleting: "<<current->data<<endl;
		temp = current;
		if (current->rightThread) {
			current = current->right;
		} else {
			current = leftMostNode(current->right);
		}
		delete(temp);
	}
}

int main() {
	
	_root = createNew(20);
	_lastLeft = _root;
	_size++;
	insert(_root, _root->key, 10, _lastLeft);
	insert(_root, _root->key, 30, _lastLeft);
	insert(_root, _root->key, 5, _lastLeft);
	insert(_root, _root->key, 16, _lastLeft);
	insert(_root, _root->key, 14, _lastLeft);
	insert(_root, _root->key, 17, _lastLeft);
	insert(_root, _root->key, 13, _lastLeft);
	printTree(cout, 0, _root);
	destructCode(_root);
// 	printTree(cout, 0, _root);
    return 0;
}