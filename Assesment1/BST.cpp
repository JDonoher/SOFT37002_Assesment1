#include "BST.h"
#include <iostream>
#include "BST.h"

TNode::TNode(int k, string v, TNode* l, TNode* r) {
	key = k;
	value = v;
	left = l;
	right = r;
}

Dictionary::Dictionary() {
	root = nullptr;
}

TNode* Dictionary::deepCopy(TNode* p) {

	if (p == nullptr)
		return p;

	TNode* l = deepCopy(p->left);
	TNode* r = deepCopy(p->right);

	return (new TNode(p->key, p->value, l, r));
}

Dictionary::Dictionary(const Dictionary& d) {
	root = deepCopy(d.root);
}

Dictionary::Dictionary(Dictionary&& d) {
	root = d.root;
	d.root = nullptr;
}

Dictionary& Dictionary::operator=(const Dictionary& d) {

	if (this != &d) {
		this->~Dictionary();
		root = deepCopy(d.root);
	}
	return *this;
}

Dictionary& Dictionary::operator=(Dictionary&& d) {
	if (this != &d) {
		this->~Dictionary();
		root = d.root;
		d.root = nullptr;
	}
	return *this;
}

// Actual deletion of nodes done here
void Dictionary::doDelete(TNode* p) {
	if (p == nullptr)
		return;

	doDelete(p->left);
	doDelete(p->right);
	delete p;
}

Dictionary::~Dictionary() {
	doDelete(root);
}

void Dictionary::insert(int k, string v) {
	if (root == nullptr) {
		root = new TNode(k, v);
	}
	else {
		TNode* p = root;
		bool inserted = false;
		while (p != nullptr && !inserted) {
			if (p->key == k) {
				p->value = v;
				inserted = true;
			}
			else if (k < p->key) {
				if (p->left == nullptr) {
					p->left = new TNode(k, v);
					inserted = true;
				}
				else
					p = p->left;
			}
			else {
				if (p->right == nullptr) {
					p->right = new TNode(k, v);
					inserted = true;
				}
				else
					p = p->right;
			}
		}
	}
}

void Dictionary::doInsert(TNode** root, int k, string v) {
	if (*root == nullptr) {
		*root = new TNode(k, v);
	}
	else {
		TNode* p = *root;
		if (k == p->key)
			p->value = v;
		else if (k < p->key)
			doInsert(&p->left, k, v);
		else
			doInsert(&p->right, k, v);
	}
}

void Dictionary::insert_rec(int k, string v) {
	doInsert(&root, k, v);
}

string* Dictionary::lookup(int k) {

	TNode* p = root;
	string* r = nullptr;
	bool found = false;

	while (p != nullptr && !found) {
		if (p->key == k) {
			r = &(p->value);
			found = true;
		}
		else if (k < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	return r;
}

std::string* Dictionary::doLookup(TNode* root, int i) {
	std::string* r = nullptr;
	if (root == nullptr)
		return r;

	if (root->key == i) {
		r = &(root->value);
	}
	else if (i < root->key) {
		r = doLookup(root->left, i);
	}
	else {
		r = doLookup(root->right, i);
	}
	return r;
}

std::string* Dictionary::lookup_rec(int i) {
	return doLookup(root, i);
}

void Dictionary::doDisplayEntries(TNode* p) {
	if (p == nullptr)
		return;

	doDisplayEntries(p->left);
	cout << p->key << " " << p->value << endl;
	doDisplayEntries(p->right);

}

void Dictionary::displayEntries() {
	doDisplayEntries(root);
}

void Dictionary::doDisplayTree(TNode* p, string identation) {

	if (p == nullptr) {
		cout << identation << "(*)" << endl;
		return;
	}
	else {
		cout << identation << p->key << " " << p->value << endl;
	}

	doDisplayTree(p->left, identation + "   ");
	doDisplayTree(p->right, identation + "   ");
}

void Dictionary::displayTree() {
	doDisplayTree(root, "");
}

TNode* Dictionary::minValueNode(TNode* p) {

	while (p != nullptr && p->left != nullptr) {
		p = p->left;
	}
	return p;
}

void Dictionary::doRemove(TNode** root, int k) {

	TNode* p = *root;
	if (p == nullptr)
		return;
	if (k < p->key) {
		doRemove(&p->left, k);
	}
	else if (k > p->key) {
		doRemove(&p->right, k);
	}
	else {
		if (p->left == nullptr && p->right == nullptr) {
			delete p;
			*root = nullptr;
		}
		else if (p->left == nullptr) {
			*root = p->right;
			delete p;
		}
		else if (p->right == nullptr) {
			*root = p->left;
			delete p;
		}
		else {
			TNode* in = minValueNode(p->right);
			p->key = in->key;
			p->value = in->value;
			doRemove(&p->right, in->key);
		}
	}
}

void Dictionary::remove(int k) {
	doRemove(&root, k);
}

void Dictionary::rotateRight(TNode** root) {

	TNode* p = *root;
	if (p == nullptr || p->left == nullptr)
		return;

	TNode* pA = p->left;
	p->left = pA->right;
	pA->right = p;
	*root = pA;
}

void Dictionary::doRotateRightOn(TNode** root, int k) {

	TNode* p = *root;
	if (p == nullptr)
		return;

	if (k < p->key) {
		doRotateRightOn(&(p->left), k);
	}
	else if (k > p->key) {
		doRotateRightOn(&(p->right), k);
	}
	else {
		rotateRight(root);
	}
}

void Dictionary::rotateLeft(TNode** root) {

	TNode* p = *root;
	if (p == nullptr || p->right == nullptr)
		return;

	TNode* pB = p->right;
	p->right = pB->left;
	pB->left = p;
	*root = pB;

}

void Dictionary::doRotateLeftOn(TNode** root, int k) {

	TNode* p = *root;
	if (p == nullptr)
		return;

	if (k < p->key) {
		doRotateLeftOn(&(p->left), k);
	}
	else if (k > p->key) {
		doRotateLeftOn(&(p->right), k);
	}
	else {
		rotateLeft(root);
	}
}

void Dictionary::rotateRightOn(int k) {
	doRotateRightOn(&root, k);
}

void Dictionary::rotateLeftOn(int k) {
	doRotateLeftOn(&root, k);
}

int Dictionary::doGetHeight(TNode* currentNode)
{
	//If the tree is empty (root is null), return 0
	if (currentNode == nullptr) {
		return 0;
	}

	//Find the deepest left branch and the deepest right brancg, compare and return the higher value
	int leftDepth = doGetHeight(currentNode->left);
	int rightDepth = doGetHeight(currentNode->right);

	return (std::max(leftDepth, rightDepth) + 1);
}

int Dictionary::getHeight() {
	return(doGetHeight(root));
}