#include "my_functions.h"

int my::Split(BusFlight*& arr_flights, const int& left_boarder, const int& right_boarder, const BusFlight& bus_flight) {
	int pivot_boarder = left_boarder;

	for (int i = left_boarder; i < right_boarder; ++i) {
		if (arr_flights[i] <= bus_flight) {
			my::swap(arr_flights[i], arr_flights[pivot_boarder]);
			++pivot_boarder;
		}
	}

	return pivot_boarder;
}

// TODO:
void my::QuickSort(BusFlight*& arr_flights, const int& left_boarder, const int& right_boarder) {
	if (right_boarder - left_boarder < 1) {
		return;
	}

	BusFlight pivot = arr_flights[(right_boarder + left_boarder) / 2]; // rand() % (right_boarder - left_boarder)

	int split_boarder = my::Split(arr_flights, left_boarder, right_boarder, pivot);

	my::QuickSort(arr_flights, left_boarder, split_boarder - 1);
	my::QuickSort(arr_flights, split_boarder, right_boarder);
}

void my::BinarySearch(BusFlight*& arr_flight, int left_boarder, int right_boarder, const int& key) {
	while (left_boarder + 1 < right_boarder) {
		int mid = (right_boarder + left_boarder) / 2;

		if (arr_flight[mid].arrival_time_ == key) {
			ShowBusFlight(arr_flight[mid]);
			return;
		}

		if (arr_flight[mid].arrival_time_ < key) {
			left_boarder = mid;
		}
		else {
			right_boarder = mid;
		}
	}
}


void my::Sort(BusFlight*& arr_flights, const int& right_boarder) {
	for (int i = 0; i < right_boarder - 1; i++) {
		int i_min = i;
		for (int j = i + 1; j < right_boarder; j++) {
			if (arr_flights[j] < arr_flights[i_min]) {
				i_min = j;
			}
		}
		my::swap(arr_flights[i_min], arr_flights[i]);
	}
}
