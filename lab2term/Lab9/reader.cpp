#include "reader.h"

#pragma region ReaderFunctions

void Reader::close() {
	fclose(file_pointer);
}

Reader::~Reader() { // destructor close file 
	fclose(file_pointer);
}

FILE* Reader::getFilePointer() const {
	return file_pointer;
}

bool Reader::OpenFile(const char* mode) {
	fopen_s(&file_pointer, kFileName, mode);
	mode_ = mode;
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

size_t Reader::write(BusFlight& bus, int amount) {
	return fwrite(&bus, kSize, amount, file_pointer);
}

size_t Reader::write(BusFlight*& bus, int amount) {
	return fwrite(bus, kSize, amount, file_pointer);
}

size_t Reader::read(BusFlight& bus, int amount) {
	return fread(&bus, kSize, amount, file_pointer);
}

size_t Reader::read(BusFlight*& bus, int amount) {
	return fread(bus, kSize, amount, file_pointer);
}

int Reader::seek(long int offset, int whence) {
	return fseek(file_pointer, offset, whence);
}

void Reader::resize(size_t offset) {
	int file_descriptor = 0;
	close();	// close the file to work with the file descriptor
   // Open a file \ sopen - return file descriptor
   if (_sopen_s(&file_descriptor, kFileName, _O_RDWR | _O_CREAT, _SH_DENYNO,
	   _S_IREAD | _S_IWRITE) == 0) {
	   _chsize(file_descriptor, offset);
	   _close(file_descriptor);
   }
   OpenFile(mode_);	// reopen file
}

#pragma endregion

int ReadFromFile(BusFlight*& arr_flights) { // read data into arr_flights and return number of readen info
	Reader reader;
	const char* mode = "r+b";
	if (!reader.OpenFile(mode)) {
		return 0;
	}

	const int kSizeOfStruct = sizeof(BusFlight);
	int number_of_records = reader.GetAmountOfInformation(kSizeOfStruct);
	if (arr_flights) {
		delete[] arr_flights;
	}
	arr_flights = new BusFlight[number_of_records];
	reader.read(arr_flights, number_of_records);
	return number_of_records;
}

void AddBusFlight() {
	Reader reader;
	if (!reader.OpenFile("a+b")) {
		return;
	}

	BusFlight flight = CreateBusFlight();
	reader.write(flight);
}

void DeleteBusFlight(const int& pos) {
	Reader reader;
	if (!reader.OpenFile("r+b")) {	// reading && writing
		return;
	}

	const int kBusFlightSize = sizeof(BusFlight);
	int number_of_records = reader.GetAmountOfInformation(kBusFlightSize);

	if (pos > number_of_records) {
		std::cout << "No such position in file!" << '\n';
		return;
	}

	BusFlight tmp{};

	for (int i = pos; i < number_of_records; ++i) {
		int pos_of_line = (i - 1) * kBusFlightSize;
		int pos_after = i * kBusFlightSize;
		reader.seek(pos_after, SEEK_SET);
		reader.read(tmp);
		reader.seek(pos_of_line, SEEK_SET);
		reader.write(tmp);
	}

	reader.resize((number_of_records - 1) * kBusFlightSize);
}


void LinearSearch(const int& key) {
	Reader reader;
	if (!reader.OpenFile("r+b")) {
		return;
	}

	int number_of_records = reader.GetAmountOfInformation(sizeof(BusFlight));
	BusFlight tmp;
	BusViewer viewer;
	for (int i = 0; i < number_of_records; ++i) {
		reader.read(tmp);
		if (tmp.arrival_time_ == key) {
			viewer.ShowBusFlight(tmp, i);
		}
	}
}
