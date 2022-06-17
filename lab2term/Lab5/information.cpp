#include "information.h"

std::istream& operator>>(std::istream& in, Information& info) {
	do {
		std::cout << "Input Age [0;100]: ";
		CheckNum(info.age);
	} while (info.age < 0 || info.age > 100);

	std::cout << "Input Favorite Color: ";
	getline(in, info.favorite_color);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Information& info) {
	out << "Age = " << info.age << ". Favorite color: " << info.favorite_color;
	return out;
}

bool operator<(const Information& lhs, const Information& rhs) {
	return lhs.age < rhs.age;
}

bool operator==(const Information& lhs, const Information& rhs) {
	return lhs.age == rhs.age;
}