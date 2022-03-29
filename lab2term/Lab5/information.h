#pragma once
#include <iostream>

struct Information {
	int age = 0;
	std::string favorite_color;
};

std::istream& operator>>(std::istream&, Information&);

bool operator<(Information& lhs, Information& rhs);

bool operator==(Information& lhs, Information& rhs);