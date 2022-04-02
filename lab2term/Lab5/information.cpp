#include "information.h"

double CheckNum() {
	double var;

	while (!(std::cin >> var) || std::cin.get() != '\n') {
		std::cout << "Error! Something go wrong ReEnter: ";
		std::cin.clear();
		while (std::cin.get() != '\n');
	}

	return var;
}

std::istream& operator>>(std::istream& in, Information& info) {
	do {
		std::cout << "Input Age [0;100]: ";
		info.age = CheckNum();
	} while (info.age < 0 || info.age > 100);

	std::cout << "Input Favorite Color: ";
	getline(in, info.favorite_color);
	return in;
}

std::ostream& operator<<(std::ostream& out, Information& info) {
	out << "Age = " << info.age << ". Favorite color: " << info.favorite_color << '\n';
	return out;
}

bool operator<(Information& lhs, Information& rhs) {
	return lhs.age < rhs.age;
}

bool operator==(Information& lhs, Information& rhs) {
	return lhs.age == rhs.age;
}