#include "tree.h"


int GetHeight(Node* node) {
	return node == nullptr ? 0 : node->height;
}

// ------Balance----------

int GetBalanceFactor(Node* node) {
	return GetHeight(node->right) - GetHeight(node->left);
}

void SetFixedHeight(Node* node) { // Востонавливает значение текущей node. left и right УЖЕ являются корректными
	if (node == nullptr) {
		return;
	}

	int left_height = GetHeight(node->left);
	int right_height = GetHeight(node->right);

	node->height = 1 + (right_height > left_height ? right_height: left_height);
}

Node* RotateRight(Node* node) {
	Node* tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;

	SetFixedHeight(tmp->left);
	SetFixedHeight(tmp->right);
	SetFixedHeight(tmp);

	return tmp;
}

Node* RotateLeft(Node* node) {
	Node* tmp = node->right;
	node->right= tmp->left;
	tmp->left = node;
	
	SetFixedHeight(tmp->left);
	SetFixedHeight(tmp->right);
	SetFixedHeight(tmp);

	return tmp;
}

Node* BalanceTree(Node* node) {
	SetFixedHeight(node);

	if (GetBalanceFactor(node) == 2) {
		if (GetBalanceFactor(node->right) < 0)
			node->right = RotateRight(node->right);
		return RotateLeft(node);
	}
	
	if (GetBalanceFactor(node) == -2) {
		if (GetBalanceFactor(node->left) > 0)
			node->left = RotateLeft(node->left);
		return RotateRight(node);
	}

	return node;
}

// ------Insert----------

Node* Tree::insert(Node* node, Information& info, bool& isDuplicate) {
	if (node == nullptr) {
		return createLeaf(info);
	}

	if (info == node->info_) {
		std::cout << "{ " << info.age << ", " << info.favorite_color << " } node already exist in tree!\n";
		isDuplicate = true;
		return node;
	}

	if (info < node->info_)
		node->left = insert(node->left, info, isDuplicate);
	else
		node->right = insert(node->right, info, isDuplicate);

	return BalanceTree(node);
}

bool Tree::insert(Information& info) {
	bool isDuplicate = false;
	root = insert(root, info, isDuplicate);
	return isDuplicate;
}

// ------Remove----------

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
		Node* node_left = node->left;
		Node* node_right = node->right;
		delete node;
		node = nullptr;

		if (node_right == nullptr) {
			return node_left;
		}

		Node* minimum = minKey(node_right);
		// Выстраиваем логику: удаляемое заменяется на минимум в правом дереве
		// правое избавляется от минимума, левое остаётся без изменений.
		minimum->right = RemoveMin(node_right);
		minimum->left = node_left;
		return BalanceTree(minimum);
	}

	return BalanceTree(node);
}

void Tree::remove(Information& info) {
	if (!search(info, false)) {
		return;
	}
	root = remove(root, info);
	std::cout << "Removed node with key " << info.age << '\n';
}

Node* RemoveMin(Node* node) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->left == nullptr) {
		return node->right;
	}
	node->left = RemoveMin(node->left);
	BalanceTree(node);
}

// ----------------

bool Tree::empty() {
	return !root;
}

void Tree::view() {
	if (empty()) {
		std::cout << "Tree is empty!\n";
		return;
	}
	std::cout << "___________________\n";

	clock_t start = clock();

	Node* tmp = root;
	int max_height = GetHeight(root);

	// amount of all possible elements - (2^max_height - 1); from geometric progression.
	// ~ pow(2, max_height) - 1; 2 - 10 -> 2 << max_height(= 4) = 100000 = 32 
	// but 2^4 = 16 -> because of 2 = 10 in binary -> 2^max_height = 2 << (max_height - 1) or 2^max_height = 1 << max_height
	int size = (1 << max_height) - 1;

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
	
	int index = 0; // begining of curent group of elements
	int otstup = 2 << max_height;
	int amount_elements_in_group = 1;
	for (int i = 0; i < max_height; ++i) {

		if (i % 2) { // для того, чтобы легче различать строки в дереве при выводе.
			std::cout << "\033[48;5;235m"; // set background color for line
		}

		int j = 0;
		while (j < amount_elements_in_group) {
			if (arr[index + j] != nullptr)
				std::cout << std::setw(otstup) << arr[index + j]->info_.age << std::setw(otstup) << ' ' ;
			else
				std::cout << std::setw(otstup) << '-' << std::setw(otstup) << ' ';
			++j;
		}

		index += j;
		std::cout << "\033[m" << '\n';// delete color
		otstup /= 2;
		amount_elements_in_group *= 2; // ~ pow(2, i);
	}

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;

	std::cout << "Seconds for view: " << seconds << '\n';
	std::cout << "___________________\n";

	delete[] arr;
}

void Tree::clear(Node* leaf) {
	if (leaf) {
		clear(leaf->left);
		leaf->left = nullptr;
		clear(leaf->right);
		leaf->right = nullptr;
		delete leaf;
	}

	if (leaf == root) { // when tree is cleared, root will contain garbage (as a leaf), so i need to set this parameters as nullptr
		leaf = root = nullptr; // Set root = nullptr to show that tree is empty;	
	}
}

Node* Tree::GetRoot() {
	return root;
}

Node* Tree::createLeaf(Information& info) {
	return new Node(info);
}

Node* Tree::search(Information& info, bool isNeedToPrintMessage){
	Node* tmp = root;

	if (empty()) {
		std::cout << "Tree is empty!\n";
		return nullptr;
	}

	while (tmp != nullptr) {
		if (tmp->info_ == info) {
			if (isNeedToPrintMessage) {
				std::cout << "Search find this node: " << tmp->info_ << '\n';
				std::cout << "With LEFT child: ";
				
				if (tmp->left != nullptr)
					std::cout << tmp->left->info_ << '\n';
				else std::cout << "nullptr.\n";
				
				std::cout << "With RIGHT child: ";
				if (tmp->right != nullptr)
					std::cout << tmp->right->info_ << '\n';
				else 
					std::cout << "nullptr\n";

			}
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
	return minKey(root, isNeedToShowMessage);
}

Node* Tree::minKey(Node* node, bool isNeedToShowMessage) {
	if (node == nullptr) {
		std::cout << "Tree is empty!\n";
		return node;
	}

	while (node->left != nullptr) {
		node = node->left;
	}

	if (isNeedToShowMessage)
		std::cout << "Minimum | " << node->info_;
	return node;
}

// -------Traversal------

void ShowLeftRootRight(Node* node) {
	if (node == nullptr) {
		return;
	}

	ShowLeftRootRight(node->left);
	std::cout << node->info_.age << ' ';
	ShowLeftRootRight(node->right);
}

void ShowRootLeftRight(Node* node) {
	if (node == nullptr) {
		return;
	}

	std::cout << node->info_.age << ' ';
	ShowRootLeftRight(node->left);
	ShowRootLeftRight(node->right);
}

void ShowLeftRightRoot(Node* node) {
	if (node == nullptr) {
		return;
	}

	ShowLeftRightRoot(node->left);
	ShowLeftRightRoot(node->right);
	std::cout << node->info_.age << ' ';
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
