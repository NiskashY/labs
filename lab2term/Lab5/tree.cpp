#include "tree.h"

Tree::~Tree() {
	clear();
}

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

Node* Tree::insert(Node* node, const Information& info, bool& isDuplicate) {
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

bool Tree::insert(const Information& info) {
	bool isDuplicate = false;
	root = insert(root, info, isDuplicate);
	return isDuplicate;
}

// ------Remove----------

Node* Tree::remove(Node* node, const Information& info) {
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

void Tree::remove(const Information& info) {
	if (!search(info, false)) {
		return;
	}
	root = remove(root, info);
	std::cout << "Removed node with key " << info.age << '\n';
}

Node* RemoveMin(Node* node) {
	// Min can only be a leaf, otherwise it is not minimal and we need to go to the next element on the left
	// or (if the left element does not exist - so our cur_node is min) we need to put a node on the right instead of cur_node. 
	// In this case we don't delete the node, we just need to replace our cur_node with the right node!*
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

bool Tree::empty() const {
	return !root;
}

void Tree::view() const {
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

Node* Tree::clear(Node* leaf) {
	if (leaf) {
		leaf->left = clear(leaf->left);
		leaf->right = clear(leaf->right);
		delete leaf;
		leaf = nullptr;
	}
	return leaf;
}

void Tree::clear() {
	root = clear(root);
}

Node* Tree::GetRoot() {
	return root;
}

Node* Tree::createLeaf(const Information& info) {
	return new Node(info);
}

Node* Tree::search(const Information& info, bool isNeedToPrintMessage){
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
