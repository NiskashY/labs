#include "information.h"

std::istream& operator>>(std::istream& in, Information& info) {
	std::cout << "Input Year: ";
	in >> info.age; // Need validation.
	std::cout << "Input Favorite Color: ";
	in >> info.favorite_color;
	return in;
}
