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

		// Mb i need to insert in this line makeBalance?
	}
}

Node* Tree::createLeaf(Information& info) {
	return new Node(info);
}

bool Tree::empty() {
	return !root;
}

void Tree::view() {
	if (empty()) {
		std::cout << "Tree is empty!\n";
		return;
	}
	
	Node* tmp = root;

	int max_height = 0;
	getHeight(root, 0, max_height);

	// amount of all possible elements - (2^max_height - 1); from geometric progression.
	// ~ pow(2, max_height) - 1; 2 - 10 -> 2 << max_height(= 4) = 100000 = 32 
	// but 2^4 = 16 -> because of 2 = 10 in binary -> 2^max_height = 2 << (max_height - 1)
	int size = (2 << (max_height - 1)) - 1;

	Node** arr = new Node*[size];
	
	arr[0] = tmp;
	// i element -> left child - 2 * i + 1, right child - 2 * i + 2
	for (int i = 0; 2 * i + 2 < size; ++i) {
		if (arr[i] == nullptr) {
			arr[2 * i + 1] = nullptr;
			arr[2 * i + 2] = nullptr;
		}
		else {
			arr[2 * i + 1] = arr[i]->left;
			arr[2 * i + 2] = arr[i]->right;
		}
	}
	
	int index = 0; // current element;

	for (int i = 0; i < max_height; ++i) {

		// I did this because if i = 0 -> 2 << -1 = 0 -> the output is not correct.
		int size_tmp = 1;
		if (i)
			size_tmp = 2 << (i - 1); // ~ pow(2, i);

		int j = 0;

		for (int x = 1; x < max_height - i; ++x) {
			std::cout << ' ';
		}
		
		while (j < size_tmp) {
			if (arr[index + j] != nullptr)
				std::cout << arr[index + j]->info_.age;
			
			std::cout << ' ';
			++j;
		}

		index += j;
		std::cout << '\n';
	}

	delete[] arr;
}

void Tree::clear(Node* leaf) {
	if (leaf) {
		clear(leaf->left);
		clear(leaf->right);
		delete leaf;
		
		leaf->left = leaf->right = nullptr; // In order not to point to something in memory;
	}

	if (leaf == root) {
		root = nullptr; // Set root = nullptr to show that tree is empty;
	}
}

void Tree::search(Information& info) {
	Node* tmp = root;

	if (empty()) {
		std::cout << "Tree is empty!\n";
		return;
	}

	while (tmp != nullptr) {
		if (tmp->info_ == info) {
			std::cout << tmp->info_;
			if (tmp->left != nullptr)
				std::cout << "Left child:" << tmp->left->info_;
			if (tmp->right!= nullptr)
				std::cout << "Right child:" << tmp->right->info_;
			return;
		}
		else if (tmp->info_ < info) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	std::cout << "No such element in tree :(\n";
}

Node* Tree::maxKey(bool isNeedToShowMessage) {
	if (empty()) {
		std::cout << "Tree is empty!\n";
		return root;
	}
	Node* tmp = root;

	while (tmp->right != nullptr) {
		tmp = tmp->right;
	}

	if (isNeedToShowMessage)
		std::cout << "Maximum | " << tmp->info_;
	return tmp;
}

Node* Tree::minKey(bool isNeedToShowMessage) {
	if (empty()) {
		std::cout << "Tree is empty!\n";
		return root;
	}
	Node* tmp = root;

	while (tmp->left != nullptr) {
		tmp = tmp->left;
	}

	if (isNeedToShowMessage)
		std::cout << "Minimum | " << tmp->info_;
	return tmp;
}