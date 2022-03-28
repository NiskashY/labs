#include "tree.h"

bool operator<(Information& lhs, Information& rhs) {
	return lhs.age < rhs.age;
}

void Tree::insert(Information& info) {
	if (empty()) { // if tree is empty
		root = createLeaf(info);
	}
	else {
		Node* tmp = root;

		while (true) {
			if (tmp->info_ < info) {
				if (tmp->right == nullptr) {
					tmp->right = new Node(info);
					break;
				}
				tmp = tmp->right;
			}
			else {
				if (tmp->left == nullptr) {
					tmp->left = new Node(info);
					break;
				}
				tmp = tmp->left;
			}
		}
	}
}

Node* Tree::createLeaf(Information& info) {
	return new Node(info);
}

bool Tree::empty() {
	return root == nullptr;
}