#pragma once
#include <string>
using namespace std;
struct TNode {
	int key;
	string value;
	TNode* left;
	TNode* right;
	TNode(int, string, TNode* = nullptr, TNode* = nullptr);
};

class Dictionary {
private:
	TNode* root;
	void doDisplayEntries(TNode*);
	void doDisplayTree(TNode*, string);
	void doInsert(TNode**, int, string);
	string* doLookup(TNode*, int);
	TNode* minValueNode(TNode*);
	void doRemove(TNode**, int);
	void doDelete(TNode*);
	TNode* deepCopy(TNode*);
	void rotateLeft(TNode**);
	void rotateRight(TNode**);
	void doRotateRightOn(TNode**, int k);
	void doRotateLeftOn(TNode**, int k);

public:
	Dictionary();
	~Dictionary();
	Dictionary(const Dictionary& d);
	Dictionary(Dictionary&&);
	Dictionary& operator=(const Dictionary&);
	Dictionary& operator=(Dictionary&&);
	void insert(int, string);
	void insert_rec(int, string);
	string* lookup(int);
	string* lookup_rec(int);
	void displayEntries();
	void displayTree();
	void remove(int);
	void rotateRightOn(int k);
	void rotateLeftOn(int k);
	int getHeight();
	int doGetHeight(TNode*);
};