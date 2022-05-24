#include <iostream>
#include "reader.h"
#include "my_functions.h"


// add colors.h from airlines ticket sales

void MenuSectionView();
void MenuSectionSearch(int&);
void MenuSectionSort(int&);

int main() {
	const char kMenu[] = "1 - Add\n2 - View\n3 - Search\n4 - Sort\nelse - exit\nYour Choice: ";

	while (true) {
		system("cls");
		int choice = 0;
		std::cout << kMenu;
		CheckNum(choice);
		
		switch (choice) {
		case 1: {
			AddBusFlight();
			break;
		}
		case 2: {
			MenuSectionView();
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
		system("pause");
	}
	return 0;
}

void MenuSectionView() {
	BusFlight* buses = nullptr;
	int number_of_records = ReadFromFile(buses);
	ShowAllBusFlights(buses, number_of_records);
	delete[] buses;
	buses = nullptr;
}

void MenuSectionSearch(int& choice) {
	const char kMenuSearch[] = "\n1 - linear\nelse - binary\nYour Choice: ";
	std::cout << kMenuSearch;
	CheckNum(choice);

	std::cout << "(KEY FOR SEARCH) ";
	int time_tmp = 0;
	InputArrival(time_tmp);

	if (choice == 1) {
		LinearSearch(time_tmp);
	}
	else {
		BusFlight* buses = nullptr;
		int number_of_records = ReadFromFile(buses);
		my::QuickSort(buses, 0, number_of_records);
		my::BinarySearch(buses, 0, number_of_records, time_tmp);
		delete[] buses;
		buses = nullptr;
	}
}

void MenuSectionSort(int& choice) {
	const char kMenuSort[] = "\n1 - Selection\nelse - Quick\nYour Choice: ";
	std::cout << kMenuSort;
	CheckNum(choice);
	BusFlight* buses = nullptr;
	int number_of_records = ReadFromFile(buses);

	if (choice == 1) {
		my::Sort(buses, number_of_records);
	}
	else {
		my::QuickSort(buses, 0, number_of_records);
	}

	ShowAllBusFlights(buses, number_of_records);
	delete[] buses;
	buses = nullptr;

}
