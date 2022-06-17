#pragma once

#include <iostream>
#include <iomanip>
#include <stdio.h> 
#include <time.h> 

#include "information.h"
#include "MintLib.h"

struct Node {
	Node() = default;
	
	Node(const Information& info) : info_(info), height(1) {}

	int height;
	Information info_;
	Node* left = nullptr;
	Node* right = nullptr;
};

int GetHeight(Node*);
int GetBalanceFactor(Node*);
void SetFixedHeight(Node*);
Node* RemoveMin(Node*);

void ShowLeftRootRight(Node*);
void ShowRootLeftRight(Node*);
void ShowLeftRightRoot(Node*);

class Tree {
private:
	Node* root = nullptr; // ~ begining of the tree
	Node* insert(Node*, const Information&, bool&);
	Node* remove(Node*, const Information&);
	Node* clear(Node*);	// recursively clear Nodes

public:
	Tree() = default;
	~Tree();

	bool empty() const;
	bool insert(const Information&);
	
	void view() const;
	void remove(const Information&);
	void clear();	// clear full tree
	
	Node* GetRoot();
	Node* createLeaf(const Information&);
	Node* search(const Information&, bool isNeedToPrintMessage = true);
	Node* maxKey(bool isNeedToShowMessage = false);
	Node* minKey(bool isNeedToShowMessage = false);
	Node* minKey(Node*, bool isNeedToShowMessage = false);
};
