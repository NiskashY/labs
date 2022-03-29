#include "information.h"
#include "tree.h"

std::istream& operator>>(std::istream& in, Information& info) {
	std::cout << "Input Year: ";
	in >> info.age; // Need validation.
	std::cout << "Input Favorite Color: ";
	in >> info.favorite_color;
	return in;
}

bool operator<(Information& lhs, Information& rhs) {
	if (lhs.age == rhs.age)
		return lhs.favorite_color < rhs.favorite_color;

	return lhs.age < rhs.age;
}

bool operator==(Information& lhs, Information& rhs) {
	return lhs.age == rhs.age && lhs.favorite_color == rhs.favorite_color;
}