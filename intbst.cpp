// intbst.cpp
// Implements class IntBST
// Skyler Brown, 01/30/26

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
	root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
	clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
	if (!n) return;
	clear(n->left);
	clear(n->right);
	delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
	if (!root) {
            root = new Node(value);
            return true;
	}
       	return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) {
	    return false;
    }
    if (value < n->info) {
	    if (n->left) {
		    return insert(value, n->left);
	    }
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
    }
    if (value > n->info) {
	    if (n->right) {
		    return insert(value, n->right);
	    }
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
	printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
	if (!n) return;
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
	printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
	if (!n) return;
	printInOrder(n->left);
	cout << n->info << " ";
	printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
	printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
	if (!n) return;
	printPostOrder(n->left);
	printPostOrder(n->right);
	cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
	if (!n) return 0;
	return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
	if (!n) return 0;
	return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
	if (!n) return NULL;
	if (value == n->info) {
		return n;
	}
	if (value < n->info) {
		return getNodeFor(value, n->left);
	}
	return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
	if (getNodeFor(value, root) == NULL) {
		return false;
	}
	return true;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node * curr = getNodeFor(value, root);
    if (curr == NULL) {
	    return NULL;
    }
    if (curr->left) {
	  curr = curr->left;
	while (curr->right) {
	      curr = curr->right;
	}
	return curr;
    }
    Node * currParent = curr->parent;
    while (currParent && curr == currParent->left) {
	curr = currParent;
        currParent = currParent->parent;
    }
    return currParent;    
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node * pred = getPredecessorNode(value);
    if (pred == NULL) {
	    return 0;
    }
    return pred->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node * curr = getNodeFor(value, root);
    if (curr == NULL) {
	    return NULL;
    }
    if (curr->right) {
	    curr = curr->right;
	    while (curr->left) {
		    curr = curr->left;
	    }
	    return curr;
    }
    Node * currParent = curr->parent;
    while (currParent && curr == currParent->right) {
	    curr = currParent;
	    currParent = currParent->parent;
    }
    return currParent;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node * succ = getSuccessorNode(value);
    if (succ == NULL) {
	    return 0;
    }
    return succ->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
	Node * curr = getNodeFor(value, root);
	if (curr == NULL) {
		return false;
	}
	if (curr->left != NULL && curr->right != NULL) {
		Node * succ = getSuccessorNode(value);
		curr->info = succ->info;
		curr = succ;
	}
	Node * child = NULL;
	if (curr->left != NULL) {
		child = curr->left;
	}
	else if (curr->right != NULL) {
		child = curr->right;
	}
	if (child != NULL) {
		child->parent = curr->parent;
	}
	if (curr->parent == NULL) {
		root = child;
   	}
	else if (curr == curr->parent->left) {
		curr->parent->left = child;
	}
	else {
		curr->parent->right = child;
	}
	delete curr;
	return true;
}
