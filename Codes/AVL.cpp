#include<bits/stdc++.h>
using namespace std;

#define max(a, b) (return (a>b)?a:b)
typedef vector<int> KEY;
typedef int T;

void rotateRight(Elem *& node);
void rotateLeft(Elem *& node);
void doubleRotateRight(Elem *& node);
void doubleRotateLeft(Elem *& node);
void balance(Elem*& cur, const KEY &key);

struct Elem {
	Elem():left(0), right(0), height(-1), rightThread(false) {}
	KEY key;
	T data;
	Elem *left;
	Elem *right;
	int height;
	bool rightThread; //normal right child link or a threadlink
};
Elem *_root; // a dummy root sentinel
int _size;
Elem *_lastLeft;

int height(Elem *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

void updateHeight(Elem*& cur) {
	cur->height = 1 + max(height(cur->left), height(cur->right));
}

int balanceFactor(Elem *cur) {
	if (cur == NULL)
        return 0;
    return height(cur->left) - height(cur->right);
}

// helper method for creating a new node of tree
struct Elem *createNew(const T &data) {
	// Allocate memory for new node
	struct Elem *elem = (struct Elem*)malloc(sizeof(struct Elem));
	elem->data = data;
	elem->left = NULL;
	elem->right = NULL;
	elem->height = 1;
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

void rotateRight(Elem *& node) {
	struct Elem *x = node->left;
    struct Elem *T2 = x->right;
 
    // Perform rotation
    x->right = node;
    node->left = T2;
 
    // Update heights
    node->height = max(height(node->left), height(node->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}

void rotateLeft(Elem *& node) {
	struct Node *y = node->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = node;
    node->right = T2;
 
    //  Update heights
    node->height = max(height(node->left), height(node->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
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