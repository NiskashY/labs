#pragma once

#include <cstdio>
#include <iostream>

#include <io.h> // directory for _chsize <- truncate file
#include <fcntl.h>


#include "bus_service.h"

class Reader {
private:
	const char* kFileName = nullptr;
	FILE* file_pointer = nullptr;
	const size_t kSize = sizeof(BusFlight);
	const char* mode_ = nullptr;

public:
	Reader() : kFileName("bus_flights.txt") {}	// default contructor

	Reader(const char* file_name) : kFileName(file_name) {} // constructor with parameters

	~Reader(); // destructor - close file

	FILE* getFilePointer() const;

	void close();

	bool OpenFile(const char* mode);

	int GetAmountOfInformation(const int& information_size);

	size_t write(BusFlight& bus, int amount = 1);

	size_t write(BusFlight*& bus, int amount = 1);

	size_t read(BusFlight& bus, int amount = 1);

	size_t read(BusFlight*& bus, int amount = 1);

	int seek(long int offset, int whence);

	void resize(size_t offset);

};

int ReadFromFile(BusFlight*&); // read data into arr_flights and return number of readen info

void AddBusFlight();

void DeleteBusFlight(const int&);

void LinearSearch(const int&);
