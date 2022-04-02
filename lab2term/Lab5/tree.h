#pragma once
#include <iomanip>
#include "iostream"
#include "information.h"

struct Node {
	Node() = default;
	
	Node(Information& info) : info_(info), height(1) {}

	int height;
	Information info_;
	Node* left = nullptr;
	Node* right = nullptr;
};

void GetTreeHeight(Node*, int current_height, int&);
int getHeight(Node*);
int balanceFactor(Node*);
void SetFixedHeight(Node*);
Node* removeMin(Node*);

class Tree {
private:
	Node* root = nullptr; // ~ begining of the tree
	Node* insert(Node*, Information& info);
	Node* remove(Node* node, Information& info);

public:
	Tree() = default;

	Tree(Information& info) {
		root->info_ = info;
	}

	Node* GetRoot();
	Node* createLeaf(Information& info);
	bool empty();
	void insert(Information& info);
	void view();
	void clear(Node* leaf);
	Node* search(Information& info, bool isNeedToPrintMessage = true);
	Node* maxKey(bool isNeedToShowMessage = false);
	Node* minKey(bool isNeedToShowMessage = false);
	Node* minKey(Node* node, bool isNeedToShowMessage = false);
	void remove(Information& info);

	
	//Node* makeBalance(Node*, Information*&, int, int);
};