#include <iostream>

#include "information.h"
#include "tree.h"
#include "tests.h"

/*
4. Task: getHeight of the tree.
*/

bool ShowEmptyMenu(Tree&);
bool ShowMenu(Tree&);
void InsertInMenu(Tree&);
void SearchInMenu(Tree&);
void RemoveInMenu(Tree&);
void TraversalInMenu(Tree&, const char* const&);
void RandomElements(Tree&, int);

// for 2^17 elements - 107 second for VIEW.
// for 10 elements - 0.007 seconds for VIEW;
// for 2^17 elements - 0.835 seconds for INSERT;

int main() {
	Tree tree;

	bool isNeedToExit = false;
	while (!isNeedToExit) {
		system("cls");
		if (tree.empty()) {
			isNeedToExit = ShowEmptyMenu(tree);
		}
		else {
			isNeedToExit = ShowMenu(tree);
		}
		std::cout << '\n';
		if (!isNeedToExit)
			system("pause");
	}
	
	return 0;
}

bool ShowEmptyMenu(Tree& tree) {
	const char* const kTask = "\t\t\tTASK: Get height of the tree";
	const char* const  kEmptyMenu = "0 - RunTest(Random, 2 ^ 10 elements)\n1 - Insert.\nelse - Exit.\n\nYour Choice : ";

	std::cout << kTask << "\n\n";
	tree.view();
	std::cout << '\n' << kEmptyMenu;
	int choice = 0;
	CheckNum(choice);
	std::cout << '\n';

	switch (choice) {
		case 0: {
			RunTests();
			break;
		}
		case 1: {
			InsertInMenu(tree);
			break;
		}
		default: {
			std::cout << std::setw(50) << "Bye!\n";
			return true;
		}
	}

	return false;
}

bool ShowMenu(Tree& tree) {
	const char* const kTask = "\t\t\tTASK: Get height of the tree";
	const char* const kMenu = "0 - RunTest(Random, 2 ^ 10 elements)\n1 - Insert.\n2 - Search.\n3 - Remove.\n4 - Clear.\n5 - Traversal.\n6 - Individual.\n7 - Invert\nelse - Exit.\n\nYour Choice : ";

	std::cout << kTask << "\n\n";
	tree.view();
	std::cout << '\n' << kMenu;
	int choice = 0;
	CheckNum(choice);
	std::cout << '\n';

	switch (choice) {
		case 0: {
			RunTests();
			break;
		}
		case 1: {
			InsertInMenu(tree);
			break;
		}
		case 2: {
			SearchInMenu(tree);
			break;
		}
		case 3: {
			RemoveInMenu(tree);
			break;
		}
		case 4: {
			tree.clear();
			std::cout << "Cleared!\n";
			break;
		}
		case 5: {
			TraversalInMenu(tree, kTask);
			break;
		}
		case 6: {
			std::cout << "Height of the tree - " << GetHeight(tree.GetRoot()) << '\n';
			break;
		}
		case 7: {
			tree.invert();
			break;
		}
		default: {
			std::cout << std::setw(50) << "Bye!\n";
			return true;
		}
	}
	return false;
}

void RandomElements(Tree& tree, int amount) {
	while (amount--) {
		int tmp = rand() % 100 + 1;
		std::cout << "Insert key = " << tmp << "...\n";
		Information inf = { tmp, "some color..." };
		tree.insert(inf);
	}
}

void InsertInMenu(Tree& tree) {
	Information information;
	std::cout << "Input amount of information you want to insert: ";
	int amount = 0;
	CheckNum(amount);

	if (amount > 10) { // Suggest the user to fill the tree with random elements
		std::cout << "Do you want to insert " << amount << " random elements? YES - 1, NO - else: ";
		int choice = 0;
		CheckNum(choice);
		if (choice == 1) {
			srand(time(NULL));
			RandomElements(tree, amount);
			return;
		}
	}
	std::cout << "Input information for insert:\n";

	while (amount--) {
		std::cout << "\n#" << amount + 1 << "\n";
		std::cin >> information;

		if (!tree.insert(information))
			std::cout << "Done!";
	}
}

void SearchInMenu(Tree& tree) {
	std::cout << "Input key for search:\n";
	int key = 0;
	CheckNum(key);

	Information tmp = { key, "" };
	tree.search(tmp);
}

void RemoveInMenu(Tree& tree) {
	std::cout << "Input key for remove:\n";
	int key = 0;
	CheckNum(key);

	Information tmp = { key, "" };
	tree.remove(tmp);
}

void TraversalInMenu(Tree& tree, const char* const& TASK) {
	system("cls");
	std::cout << TASK << "\n\nShow LEFT-ROOT-RIGHT - 1\nShow ROOT-LEFT-RIGHT - 2\nShow LEFT-RIGHT-ROOT - 3\nBack - else\nYour choice: ";
	int choice_tmp = 0;
	CheckNum(choice_tmp);

	switch (choice_tmp) {
	case 1: {
		std::cout << "Show LEFT-ROOT-RIGHT: ";
		ShowLeftRootRight(tree.GetRoot());
		break;
	}
	case 2: {
		std::cout << "Show ROOT-LEFT-RIGHT: ";
		ShowRootLeftRight(tree.GetRoot());
		break;
	}
	case 3: {
		std::cout << "Show LEFT-RIGHT-ROOT: ";
		ShowLeftRightRoot(tree.GetRoot());
		break;
	}
	}
	std::cout << '\n';
}
