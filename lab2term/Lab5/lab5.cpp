#include <iostream>
#include <vector>

#include "information.h"
#include "tree.h"
#include "tests.h"

/*
4. Task: getHeight of the tree.
*/

bool ShowEmptyMenu(Tree*&);
bool ShowMenu(Tree*&);
void InsertInMenu(Tree*&);
void SearchInMenu(Tree*&);
void RemoveInMenu(Tree*&);
void TraversalInMenu(Tree*&, const std::string&);

// for 2^17 elements - 107 second for view.
// for 10 elements - 0.007 seconds for view;
// for 2^17 elements - 0.835 seconds for INSERT!!!;

int main() {
	Tree* tree = new Tree();
	bool isNeedToExit = false;
	while (!isNeedToExit) {
		system("cls");
		if (tree->empty()) {
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

bool ShowEmptyMenu(Tree*& tree) {
	const std::string TASK = "\t\t\tTASK: Get height of the tree";
	const std::string EMPTY_MENU = TASK + "\n\n0 - RunTest(Random, 2^10 elements)\n1 - Insert.\nelse - Exit.\nYour Choice: ";

	std::cout << "Tree is empty.\n";
	std::cout << EMPTY_MENU;
	int choice = CheckNum();

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

bool ShowMenu(Tree*& tree) {
	const std::string TASK = "\t\t\tTASK: Get height of the tree";
	const std::string MENU = TASK + "\n\n0 - RunTest(Random, 2^10 elements)\n1 - Insert.\n2 - Search.\n3 - Remove.\n4 - View.\n5 - Clear.\n6 - Traversal.\n7 - Individual.\nelse - Exit.\nYour Choice: ";
	std::cout << MENU;
	int choice = CheckNum();

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
			tree->view();
			break;
		}
		case 5: {
			tree->clear(tree->GetRoot());
			break;
		}
		case 6: {
			TraversalInMenu(tree, TASK);
			break;
		}
		case 7: {
			std::cout << "Height of the tree - " << GetHeight(tree->GetRoot()) << '\n';
			break;
		}
		default: {
			std::cout << std::setw(50) << "Bye!\n";
			return true;
		}
	}
	return false;
}

void InsertInMenu(Tree*& tree) {
	Information information;
	std::cout << "Input amount of information you want to insert: ";
	int amount = CheckNum();
	std::cout << "Input information for insert:\n";

	while (amount--) {
		std::cout << "\n#" << amount + 1 << "\n";
		std::cin >> information;

		if (!tree->insert(information))
			std::cout << "Done!";
	}
}

void SearchInMenu(Tree*& tree) {
	std::cout << "Input key for search:\n";
	int key;
	key = CheckNum();

	Information tmp = { key, "" };
	tree->search(tmp);
}

void RemoveInMenu(Tree*& tree) {
	std::cout << "Input key for remove:\n";
	int key;
	key = CheckNum();

	Information tmp = { key, "" };
	std::cout << "Removed node with key " << tmp.age << '\n';
	tree->remove(tmp);
}

void TraversalInMenu(Tree*& tree, const std::string& TASK) {
	system("cls");
	std::cout << TASK + "\n\nShow LEFT-ROOT-RIGHT - 1\nShow ROOT-LEFT-RIGHT - 2\nShow LEFT-RIGHT-ROOT - 3\nBack - else\nYour choice: ";
	int choice_tmp = CheckNum();

	switch (choice_tmp) {
	case 1: {
		std::cout << "Show LEFT-ROOT-RIGHT: ";
		ShowLeftRootRight(tree->GetRoot());
		break;
	}
	case 2: {
		std::cout << "Show ROOT-LEFT-RIGHT: ";
		ShowRootLeftRight(tree->GetRoot());
		break;
	}
	case 3: {
		std::cout << "Show LEFT-RIGHT-ROOT: ";
		ShowLeftRightRoot(tree->GetRoot());
		break;
	}
	}
	std::cout << '\n';
}
