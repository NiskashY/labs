#pragma once
#include "iostream"
#include "information.h"


struct Node {
	Node() = default;
	
	Node(Information& info) : info_(info) {}

	Information info_;
	Node* left = nullptr;
	Node* right = nullptr;
};

bool operator<(Information& lhs, Information& rhs);

class Tree {
private:
	Node* root = nullptr; // ~ begining of the tree

public:
	Tree() = default;

	Tree(Information& info) {
		if (root != nullptr)
			root->info_ = info;
	}

	Node* createLeaf(Information& info);

	void insert(Information& info);

	void view();
	void view(Information&);
	void clear();
	void maxKey();
	void minKey();
	void remove();
	void makeBalance();
	Node* search();

	bool empty();
};