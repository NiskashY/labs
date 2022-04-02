#pragma once

#include <iostream>
#include <iomanip>
#include <stdio.h> 
#include <time.h> 

#include "information.h"

struct Node {
	Node() = default;
	
	Node(Information& info) : info_(info), height(1) {}

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
	Node* insert(Node*, Information&, bool&);
	Node* remove(Node*, Information&);

public:
	Tree() = default;
	bool empty();
	bool insert(Information&);

	void view();
	void clear(Node*);
	void remove(Information&);

	Node* GetRoot();
	Node* createLeaf(Information&);
	Node* search(Information&, bool isNeedToPrintMessage = true);
	Node* maxKey(bool isNeedToShowMessage = false);
	Node* minKey(bool isNeedToShowMessage = false);
	Node* minKey(Node*, bool isNeedToShowMessage = false);

};

//Node* makeBalance(Node*, Information*&, int, int);
//void GetTreeHeight(Node*, int current_height, int&);

