#pragma once

#include <cstdio>
#include <iostream>

#include "bus_service.h"

class Reader {
private:
	const char* kFileName = nullptr;
	FILE* file_pointer = nullptr;

public:
	Reader() : kFileName("bus_flights.txt") {}	// default contructor

	Reader(const char* file_name) : kFileName(file_name) {} // constructor with parameters

	~Reader(); // destructor - close file

	FILE* getFilePointer() const;

	void close();

	bool OpenFile(const char* mode);

	int GetAmountOfInformation(const int& information_size);

};

int ReadFromFile(BusFlight*&); // read data into arr_flights and return number of readen info

void AddBusFlight();

void LinearSearch(const int& key);

