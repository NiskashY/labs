#pragma once
#include <iomanip>
#include "iostream"
#include "information.h"

struct Node {
	Node() = default;
	
	Node(Information& info) : info_(info) {}

	Information info_;
	Node* left = nullptr;
	Node* right = nullptr;
};

void getHeight(Node*, int current_height, int&);

class Tree {
private:
	Node* root = nullptr; // ~ begining of the tree

public:
	Tree() = default;

	Tree(Information& info) {
		if (root != nullptr)
			root->info_ = info;
	}

	Node* GetRoot();
	Node* createLeaf(Information& info);
	bool empty();
	void insert(Information& info);
	void view();
	
	void view(Information&);
	void clear(Node* leaf);
	void maxKey();
	void minKey();
	void remove();
	void makeBalance();
	Node* search();

};