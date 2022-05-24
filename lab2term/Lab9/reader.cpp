#include "reader.h"
#include <vector>

void Reader::close() {
	fclose(file_pointer);
}

Reader::~Reader() { // destructor close file 
	fclose(file_pointer);
}

FILE* Reader::getFilePointer() const {	// maybe this will call problems later!!!!!!!!!!
	return file_pointer;
}

bool Reader::OpenFile(const char* mode) {
	fopen_s(&file_pointer, kFileName, mode);
	if (!file_pointer) { // file == nullptr
		const char kErrorMessage[] = "Error open file!";
		std::cout << '\n' << kErrorMessage << '\n';
		return false;
	}
	return true;
}

int Reader::GetAmountOfInformation(const int& information_size) {
	fseek(file_pointer, 0, SEEK_END);
	int file_size = ftell(file_pointer);
	fseek(file_pointer, 0, SEEK_SET);
	return file_size / information_size;
}


int ReadFromFile(BusFlight*& arr_flights) { // read data into arr_flights and return number of readen info
	Reader reader;
	const char* mode = "r+b";
	if (!reader.OpenFile(mode)) {
		return 0;
	}

	const int kSizeOfStruct = sizeof(BusFlight);
	int number_of_records = reader.GetAmountOfInformation(kSizeOfStruct);
	arr_flights = new BusFlight[number_of_records];
	fread(arr_flights, kSizeOfStruct, number_of_records, reader.getFilePointer());

	return number_of_records;
}

void AddBusFlight() {
	Reader reader;
	if (!reader.OpenFile("a+b")) {
		return;
	}

	BusFlight flight = CreateBusFlight();
	fwrite(&flight, sizeof(BusFlight), 1, reader.getFilePointer());
}

void LinearSearch(const int& key) {
	Reader reader;
	if (!reader.OpenFile("r+b")) {
		return;
	}

	int number_of_records = reader.GetAmountOfInformation(sizeof(BusFlight));
	BusFlight tmp;
	for (int i = 0; i < number_of_records; ++i) {
		fread(&tmp, sizeof(BusFlight), 1, reader.getFilePointer());
		if (tmp.arrival_time_ == key) {
			ShowBusFlight(tmp);
		}
	}
}

