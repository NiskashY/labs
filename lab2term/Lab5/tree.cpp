#include "tree.h"

void getHeight(Node* tmp, int current_height, int& max_height) {

	if (max_height < current_height)
		max_height = current_height;

	if (tmp) {
		current_height++;
		getHeight(tmp->left, current_height, max_height);

		getHeight(tmp->right, current_height, max_height);
	}
}

Node* Tree::GetRoot() {
	return root;
}

void Tree::insert(Information& info) {
	if (empty()) { // if tree is empty
		root = createLeaf(info);
	}
	else {
		Node* tmp = root;

		while (true) {
			if (tmp->info_ == info) {
				std::cout << "{ " << info.age << ", " << info.favorite_color << " } node already exist in tree!\n";
				break;
			}
			else if (tmp->info_ < info) {
				if (tmp->right == nullptr) {
					tmp->right = createLeaf(info);
					break;
				}
				tmp = tmp->right;
			}
			else {
				if (tmp->left == nullptr) {
					tmp->left = createLeaf(info);
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
	return !root;
}

void Tree::view() {
	Node* tmp = root;
	int index = 0;

	int max_height = 0;
	getHeight(root, 0, max_height);
	// amount of all possible elements - (2^max_height - 1);
	// i will show only age in console.
	// check notes in notebook...
	int size = pow(2, max_height) - 1;
	Node** arr = new Node*[size];
	arr[0] = tmp;
	for (int i = 1; i < max_height; ++i) {
		int elem_in_group = pow(2, i);
		for (int j = pow(2, i - 1); j < elem_in_group; j++) {
			arr[j] = arr[j];

		}

		for (int j = index; j <= i;);
	}
}