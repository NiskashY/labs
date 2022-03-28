#pragma once
#include <iostream>

struct Information {
	int age = 0;
	std::string favorite_color;
};

std::istream& operator>>(std::istream&, Information&);