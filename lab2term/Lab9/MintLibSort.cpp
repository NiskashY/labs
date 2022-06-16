#include "MintLibSort.h"

int MintLib::RandomizedSplit(BusFlight*& arr_flights, const int& left_boarder, const int& right_boarder) {
	int i = rand() % (right_boarder - left_boarder + 1) + left_boarder;
	MintLib::swap(arr_flights[i], arr_flights[right_boarder]);
	return Split(arr_flights, left_boarder, right_boarder);
}

int MintLib::Split(BusFlight*& arr_flights, const int& left_boarder, const int& right_boarder) {
	int pivot_boarder = left_boarder;
	const BusFlight& pivot_bus_flight = arr_flights[right_boarder]; // 'opornii element'

	for (int i = left_boarder; i < right_boarder; ++i) {
		if (arr_flights[i] <= pivot_bus_flight) {
			MintLib::swap(arr_flights[i], arr_flights[pivot_boarder]);
			pivot_boarder++;
		}
	}
	// swap our pivot element with element that behind our pivot_boarder
	MintLib::swap(arr_flights[pivot_boarder], arr_flights[right_boarder]);
	return pivot_boarder;
}

void MintLib::QuickSort(BusFlight*& arr_flights, const int left_boarder, const int right_boarder) {
	if (left_boarder < right_boarder) {
		int split_boarder = MintLib::RandomizedSplit(arr_flights, left_boarder, right_boarder);
		MintLib::QuickSort(arr_flights, left_boarder, split_boarder - 1);
		MintLib::QuickSort(arr_flights, split_boarder + 1, right_boarder);
	}
}

void MintLib::Sort(BusFlight*& arr_flights, const int& right_boarder) {
	for (int i = 0; i < right_boarder - 1; i++) {
		int i_min = i;
		for (int j = i + 1; j < right_boarder; j++) {
			if (arr_flights[j] < arr_flights[i_min]) {
				i_min = j;
			}
		}
		MintLib::swap(arr_flights[i_min], arr_flights[i]);
	}
}
