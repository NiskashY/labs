#include <iostream>
#include <vector>
#include "information.h"
#include "tree.h"


int main() {
	Tree* tree = new Tree();

	std::vector<Information> v = { {10, "blue"}, {11, "green"}, {7, "yellow"}, {8, "pink"}, {9, "purple"}, {6, "red"} };
	for (int i = 0; i < v.size(); ++i) {
		Information info;
		tree->insert(v[i]);
	}

	delete tree;

	return 0;
}