#include "tree.h"

// ------Balance + insert----------
int getHeight(Node* node) {
	return node == nullptr ? 0 : node->height;
}

int getBalanceFactor(Node* node) {
	return getHeight(node->right) - getHeight(node->left);
}

void SetFixedHeight(Node* node) { // Востонавливает значение текущей node. left и right УЖЕ являются корректными
	int left_height = getHeight(node->left);
	int right_height = getHeight(node->right);

	node->height = 1 + (right_height > left_height ? right_height: left_height);
}

Node* RotateRight(Node* node) {
	Node* tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	SetFixedHeight(tmp->left);
	SetFixedHeight(tmp->right);

	return tmp;
}

Node* RotateLeft(Node* node) {
	Node* tmp = node->right;
	node->right= tmp->left;
	tmp->left = node;
	SetFixedHeight(tmp->left);
	SetFixedHeight(tmp->right);

	return tmp;
}

Node* BalanceTree(Node* node) {
	SetFixedHeight(node);

	if (getBalanceFactor(node) == 2) {
		if (getBalanceFactor(node->right) < 0)
			node->right = RotateRight(node->right);
		return RotateLeft(node);
	}
	
	if (getBalanceFactor(node) == -2) {
		if (getBalanceFactor(node->left) > 0)
			node->left = RotateLeft(node->left);
		return RotateRight(node);
	}

	return node;

}

Node* Tree::insert(Node* node, Information& info) {
	if (node == nullptr) {
		return createLeaf(info);
	}

	if (info < node->info_)
		node->left = insert(node->left, info);
	else
		node->right = insert(node->right, info);

	return BalanceTree(node);
}

void Tree::insert(Information& info) {
	root = insert(root, info);
}


Node* Tree::remove(Node* node, Information& info) {
	if (node == nullptr)
		return nullptr;

	if (node->info_ < info) {
		node->right = remove(node->right, info);
	}
	else if (info < node->info_) {
		node->left = remove(node->left, info);
	}
	else { // if info == node->info_
		Node* left = node->left;
		Node* right = node->right;
		delete node;

		if (right == nullptr) {
			return left;
		}

		Node* minimum = minKey(right);
		// Выстраиваем логику: удаляемое заменяется на минимум в правом дереве, правое избавляется от минимума, левое остаётся без изменений.
		minimum->right = removeMin(right);
		minimum->left = left;
		return BalanceTree(minimum);
	}

	BalanceTree(node);
}

void Tree::remove(Information& info) {
	if (!search(info)) {
		return;
	}

	root = remove(root, info);
}

Node* removeMin(Node* node) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->left == nullptr) {
		return node->right;
	}
	node->left = removeMin(node->left);
	BalanceTree(node);
}

// ----------------

Node* Tree::GetRoot() {
	return root;
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

	std::cout << "___________________\n";
	
	Node* tmp = root;

	int max_height = getHeight(root);

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
	int otstup = 2 << max_height;

	for (int i = 0; i < max_height; ++i) {
		

		// I did this because if i = 0 -> 2 << -1 = 0 -> the output is not correct.
		int size_tmp = 1;
		if (i)
			size_tmp = 2 << (i - 1); // ~ pow(2, i);

		int j = 0;

		if (i % 2) { // для того, чтобы легче различать строки в дереве при выводе.
			std::cout << "\033[48;5;235m"; // серый 
		}

		while (j < size_tmp) {
			if (arr[index + j] != nullptr)
				std::cout << std::setw(otstup) << arr[index + j]->info_.age << std::setw(otstup) << ' ' ;
			else
				std::cout << std::setw(otstup) << '-' << std::setw(otstup) << ' ';

			
			++j;
		}

		index += j;
		std::cout << "\033[m" << '\n';
		otstup /= 2;
	}


	std::cout << "___________________\n";

	delete[] arr;
}

void Tree::clear(Node* leaf) {
	if (leaf) {
		clear(leaf->left);
		clear(leaf->right);
		delete leaf;
	}

	if (leaf == root) {
		root = nullptr; // Set root = nullptr to show that tree is empty;
	}
}

Node* Tree::search(Information& info, bool isNeedToPrintMessage){
	Node* tmp = root;

	if (empty()) {
		std::cout << "Tree is empty!\n";
		return nullptr;
	}

	while (tmp != nullptr) {
		if (tmp->info_ == info) {
			std::cout << tmp->info_;
			if (tmp->left != nullptr && isNeedToPrintMessage)
				std::cout << "Left child:" << tmp->left->info_;
			if (tmp->right!= nullptr && isNeedToPrintMessage)
				std::cout << "Right child:" << tmp->right->info_;
			return tmp;
		}
		else if (tmp->info_ < info) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	std::cout << "No such element in tree :(\n";
	return nullptr;
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
	return minKey(root);
}

Node* Tree::minKey(Node* node, bool isNeedToShowMessage) {
	if (node == nullptr) {
		std::cout << "Tree is empty!\n";
		return node;
	}
	Node* tmp = node;

	while (tmp->left != nullptr) {
		tmp = tmp->left;
	}

	if (isNeedToShowMessage)
		std::cout << "Minimum | " << tmp->info_;
	return node;
}

/*

void GetTreeHeight(Node* tmp, int current_height, int& max_height) {

	if (max_height < current_height)
		max_height = current_height;

	if (tmp) {
		current_height++;
		GetTreeHeight(tmp->left, current_height, max_height);

		GetTreeHeight(tmp->right, current_height, max_height);
	}
}


void FillArray(Information*& arr, Node* tmp, int& index) {
	if (tmp == nullptr) {
		return;
	}

	arr[index++] = tmp->info_;
	FillArray(arr, tmp->left, index);
	FillArray(arr, tmp->right, index);
}

void SortArr(Information*& arr, int real_amount_of_elements) {
	for (int i = 0; i < real_amount_of_elements; ++i) {
		for (int j = 0; j < real_amount_of_elements - 1; ++j) {
			if (arr[j + 1] < arr[j]) {
				auto x = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = x;
			}
		}
	}
}


Node* Tree::makeBalance(Node* tmp, Information*& arr, int left, int right) {
	if (left == right) {
		tmp = nullptr;
		return tmp;
	}
	int mid = (left + right) / 2;
	Information x = arr[mid];

	tmp = createLeaf(x);
	tmp->left = makeBalance(tmp->left, arr, left, mid);
	tmp->right = makeBalance(tmp->right, arr, mid + 1, right);

	return tmp;
}

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


		int height = 0;
		int real_amount_of_elements = 0;
		GetTreeHeight(root, 0, height);
		int max_amount_of_elements = (2 << (height - 1)) - 1;
		Information* all_keys = new Information[max_amount_of_elements];
		FillArray(all_keys, root, real_amount_of_elements);
		SortArr(all_keys, real_amount_of_elements);

		clear(root);
		root = makeBalance(root, all_keys, 0, real_amount_of_elements);
	}
*/
