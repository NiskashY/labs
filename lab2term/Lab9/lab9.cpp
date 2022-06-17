#include <iostream>
#include "reader.h"
#include "MintLibSort.h"
#include "bus_service.h"

// add colors.h from airlines ticket sales

namespace mtl = MintLib;

void View();
void MenuSectionSearch(int&);
void MenuSectionSort(int&);

int main() {
	srand(time(NULL));	// for QuickSort();
	const char kMenu[] = "1 - Add\n2 - Delete\n3 - Search\n4 - Sort\nelse - exit\nYour Choice: ";
	const char kDone[] = "Done!";

	while (true) {
		system("cls");
		View();
		std::cout << '\n';

		int choice = 0;
		std::cout << kMenu;
		CheckNum(choice);
		std::cout << '\n';

		switch (choice) {
		case 1: {
			AddBusFlight();
			std::cout << kDone << '\n';
			break;
		}
		case 2: {
			DeleteBusFlight(InputPosition());
			std::cout << kDone << '\n';
			break;
		}
		case 3: {
			MenuSectionSearch(choice);
			break;
		}
		case 4: {
			MenuSectionSort(choice);
			break;
		}
		default: {
			std::cout << "\n\t\t\tBye!1!\n";
			return 0;
		}
		}
		std::cout << '\n';
		system("pause");
	}
	return 0;
}
	
void View() {
	BusViewer viewer;
	BusFlight* buses = nullptr;
	int number_of_records = ReadFromFile(buses);
	viewer.ShowAllBusFlights(buses, number_of_records);
	delete[] buses;
	buses = nullptr;
}

void MenuSectionSearch(int& choice) {
	const char kMenuSearch[] = "1 - linear\nelse - binary\nYour Choice: ";
	std::cout << kMenuSearch;
	CheckNum(choice);

	std::cout << "\n(KEY FOR SEARCH) ";
	int time_tmp = 0;
	InputArrival(time_tmp);
	std::cout << '\n';

	if (choice == 1) {
		LinearSearch(time_tmp);
	}
	else {	// TODO: lower_bound, upper_bound
		BusViewer viewer;
		BusFlight* buses = nullptr;
		int number_of_records = ReadFromFile(buses);
		mtl::QuickSort(buses, 0, number_of_records);
		mtl::pair<int, int> boarder = mtl::BinarySearch(buses, 0, number_of_records, time_tmp);
		viewer.ShowAllBusFlights(buses, boarder.second, boarder.first);
		delete[] buses;
		buses = nullptr;
	}
}

void MenuSectionSort(int& choice) {
	const char kMenuSort[] = "1 - Selection\nelse - Quick\nYour Choice: ";
	std::cout << kMenuSort;
	CheckNum(choice);

	BusFlight* buses = nullptr;
	int number_of_records = ReadFromFile(buses);

	if (choice == 1) {
		mtl::Sort(buses, number_of_records);
	}
	else {
		mtl::QuickSort(buses, 0, number_of_records - 1);
	}

	std::cout << '\n' << std::right << std::setw(50) << "-------AfterSort-------" << '\n';
	BusViewer viewer;
	viewer.ShowAllBusFlights(buses, number_of_records);
	
	delete[] buses;
	buses = nullptr;
}
