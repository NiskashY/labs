#pragma once
#include <iostream>
#include "bus_service.h"

namespace my {
	template <class T>
	void swap(T& lhs, T& rhs) {
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	int Split(BusFlight*& arr_flights, const int& left_boarder, const int& right_boarder, const BusFlight& bus_flight);

	void QuickSort(BusFlight*& arr_flights, const int& left_boarder, const int& right_boarder);

	void BinarySearch(BusFlight*& arr_flight, int left_boarder, int right_boarder, const int& key);

	void Sort(BusFlight*& arr_flights, const int& right_boarder);
}
