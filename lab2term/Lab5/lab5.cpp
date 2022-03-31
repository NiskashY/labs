#include <iostream>
#include <vector>
#include "information.h"
#include "tree.h"


int main() {
	Tree* tree = new Tree();

	//std::vector<Information> v = { {10, "blue"}, {11, "green"}, {7, "yellow"}, {8, "pink"}, {9, "purple"}, {6, "red"} };
	std::vector<Information> v = { {10, "blue"}, {9, "green"},{12, "green"},{13, "green"},{14, "green"}, {7, "yellow"}, {6, "pink"}, {8, "purple"}, {11, "red"}, {1, "white"} };

	for (size_t i = 0; i < v.size(); ++i) {
		Information info;
		tree->insert(v[i]);
	}

	int max_height = 0;
	getHeight(tree->GetRoot(), 0, max_height);

	std::cout << max_height << "\n\n";

	tree->view();

	Information inf = { 1, "red" };
	tree->search(inf);

	tree->minKey();
	tree->maxKey();

	tree->clear(tree->GetRoot());

	tree->view();

	return 0;
}