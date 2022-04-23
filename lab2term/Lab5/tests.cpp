#include "tests.h"

void RunTests() {
	Test1();
	std::cout << '\n';
	Test2();
}

void Test1() {
	std::cout << "-------TEST1----\n\n";

	std::cout << "\x1b[31m" << "WARNING: You want to run this test? It will take about 2 min to complete test. YES - 3 ( hehe :) ), NO - else:\x1b[0m ";
	int choice = CheckNum();
	if (choice != 3) {
		std::cout << "Skipped!\n";
		return;
	}

	Tree* tree = new Tree();
	int amount = 1 << 16 - 1;
	clock_t start = clock();

	for (int i = 0; i < amount; ++i) {
		Information inf = { i, "" };
		tree->insert(inf);
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Insert seconds: " << seconds << '\n';

	int max_height = GetHeight(tree->GetRoot());

	std::cout << max_height << "\n\n";

	start = clock();
	tree->view();
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "View seconds: " << seconds << '\n';

	std::cout << "Show LEFT-ROOT-RIGHT: ";
	ShowLeftRootRight(tree->GetRoot());
	std::cout << '\n';
	std::cout << "Show ROOT-LEFT-RIGHT: ";
	ShowRootLeftRight(tree->GetRoot());
	std::cout << '\n';
	std::cout << "Show LEFT-RIGHT-ROOT: ";
	ShowLeftRightRoot(tree->GetRoot());
	std::cout << '\n';

	Information inf = { rand() % (1 << 16), "" };
	tree->search(inf);
	tree->minKey();
	tree->maxKey();
	Information inf1 = { rand() % (1 << 16), "" };
	tree->remove(inf1);

	tree->view();
}

void Test2() {
	std::cout << "-------TEST2----\n\n";

	Tree* tree = new Tree();
	int amount = 100;
	clock_t start = clock();

	srand(time(NULL));

	for (int i = 0; i < amount; ++i) {
		int tmp = rand() % 100 + 1;
		Information inf = { tmp, "" };
		tree->insert(inf);
	}

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Insert seconds: " << seconds << '\n';
	int max_height = GetHeight(tree->GetRoot());
	std::cout << "Height = " << max_height << " Amount of elements = " << amount << "\n\n";
	start = clock();
	tree->view();
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "View seconds: " << seconds << '\n';

	std::cout << "Show LEFT-ROOT-RIGHT: ";
	ShowLeftRootRight(tree->GetRoot());
	std::cout << '\n';
	std::cout << "Show ROOT-LEFT-RIGHT: ";
	ShowRootLeftRight(tree->GetRoot());
	std::cout << '\n';
	std::cout << "Show LEFT-RIGHT-ROOT: ";
	ShowLeftRightRoot(tree->GetRoot());
	std::cout << '\n';
	Information inf = { rand() % 100 + 1, "" };
	tree->search(inf);
	tree->minKey(true);
	tree->maxKey(true);
	Information inf1 = { rand() % 100 + 1, "" };
	tree->remove(inf1);
	tree->view();
}
