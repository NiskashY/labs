#pragma once
#include <iostream>
#include "bus_service.h"

namespace MintLib {

	template<class T1, class T2>
	struct pair {
		T1 first{};
		T2 second{};
	};

	template <class T>
	void swap(T& lhs, T& rhs) {
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	int RandomizedSplit(BusFlight*&, const int&, const int&);

	int Split(BusFlight*&, const int&, const int&);

	void QuickSort(BusFlight*&, const int, const int);

	void Sort(BusFlight*&, const int&);

	template<class T1, class T2>
	int lower_bound(T1*& arr, int left, int right, const T2& key) {
		while (left < right) {
			int mid = (left + right) / 2;

			if (arr[mid] < key) {
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
		return left;
	}

	template<class T1, class T2>
	int upper_bound(T1*& arr, int left, int right, const T2& key) {
		while (left < right) {
			int mid = (left + right) / 2;

			if (arr[mid] <= key) {
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
		return right;
	}

	template<class T1, class T2>
	MintLib::pair<int, int> BinarySearch(T1*& arr, const int& left, const int& right, const T2& key) {
		return { MintLib::lower_bound(arr, left, right, key),
		MintLib::upper_bound(arr, left, right, key) };
	}

}
