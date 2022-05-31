#pragma once
#include <iostream>
#include <string>

struct Information {
	int age = 0;
	std::string favorite_color;
};

template <class T>
void CheckNum(T& var) {
	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
}

std::istream& operator>>(std::istream&, Information&);

std::ostream& operator<<(std::ostream& out, Information& info);

bool operator<(Information& lhs, Information& rhs);

bool operator==(Information& lhs, Information& rhs);