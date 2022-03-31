#pragma once
#include <iostream>

struct Information {
	int age = 0;
	std::string favorite_color;
};

double CheckNum();

std::istream& operator>>(std::istream&, Information&);

std::ostream& operator<<(std::ostream& out, Information& info);

bool operator<(Information& lhs, Information& rhs);

bool operator==(Information& lhs, Information& rhs);