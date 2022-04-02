#include <iostream>
#include <vector>
#include "information.h"
#include "tree.h"

int main() {
	Tree* tree = new Tree();
	
	std::vector<Information> v = { {10, "blue"}, {11, "green"}, {7, "yellow"}, {8, "pink"}, {9, "purple"}, {6, "red"} };
	//std::vector<Information> v = { {10, "blue"}, {9, "green"},{12, "green"},{13, "green"},{14, "green"}, {7, "yellow"}, {6, "pink"}, {8, "purple"}, {11, "red"}, {1, "white"} };
	//std::vector<Information> v = { {1, "blue"}, {2, "green"},{3, "green"},{4, "green"},{5, "green"} , { 6, "yellow" }, { 7, "pink" }, { 8, "purple" }, { 9, "red" } };//, { 10, "white" }, { 11, "white" }, { 12, "white" }, { 13, "white" }, { 14, "white" }, { 15, "white" }


	for (int i = 1; i < 1025; ++i) {
		Information inf = { i, "" };
		tree->insert(inf);
	}

	int max_height = getHeight(tree->GetRoot());

	std::cout << max_height << "\n\n";

	tree->view();

	Information inf = { 1, "red" };
	tree->search(inf);

	tree->minKey();
	tree->maxKey();
	Information inf1 = { 5, "" };
	tree->remove(inf1);

	tree->view();


	tree->clear(tree->GetRoot());

	tree->view();

	return 0;
}