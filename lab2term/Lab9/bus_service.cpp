#include "bus_service.h"

BusFlight CreateBusFlight() {	// TODO
	BusFlight tmp_bus_flight;
	tmp_bus_flight.bus_number_ = InputBusNumber();
	InputDestination(tmp_bus_flight.destination_);
	InputDeparture(tmp_bus_flight.departure_time_);
	InputArrival(tmp_bus_flight.arrival_time_);
	return tmp_bus_flight;
}

void BusViewer::ShowDelimLine() {
	std::cout << std::setw((width + strlen(kSeparator)) * 4 + 6) << std::setfill('-') << '-' << std::setfill(' ') << '\n';
}

void BusViewer::ShowViewHeader() {
	ShowDelimLine();
	std::cout << ' ' << std::setw(3) << "pos" << " | ";
	std::cout << std::fixed << std::left
		<< std::setw(width) << "FLight Number"<< kSeparator
		<< std::setw(width) << "Destination" << kSeparator
		<< std::setw(width) << "Departure Time" << kSeparator
		<< std::setw(width) << "Arrival Time" << kSeparator << '\n';
	ShowDelimLine();
}

void BusViewer::ShowBusFlight(const BusFlight& bus_flight, const int& i) {
	std::cout << std::fixed << '#' << std::setw(3) << i + 1 << " | ";
	std::cout << std::left
		<< std::setw(width) << bus_flight.bus_number_ << kSeparator
		<< std::setw(width) << bus_flight.destination_ << kSeparator
		<< std::setw(width) << bus_flight.departure_time_ << kSeparator
		<< std::setw(width) << bus_flight.arrival_time_ << kSeparator << '\n';
	++amount_of_viewed_flights;
}

void BusViewer::ShowAllBusFlights(BusFlight*& arr_flight, const int& right, int left) {
	for (left; left < right; ++left) {
		ShowBusFlight(arr_flight[left], left);
	}
}

bool operator<= (const BusFlight& lhs, const BusFlight& rhs) {
	return lhs.arrival_time_ <= rhs.arrival_time_;
}

bool operator<= (const BusFlight& lhs, const int& rhs) {
	return lhs.arrival_time_ <= rhs;
}

bool operator< (const BusFlight& lhs, const BusFlight& rhs) {
	return lhs.arrival_time_ < rhs.arrival_time_;
}

bool operator< (const BusFlight& lhs, const int& rhs) {
	return lhs.arrival_time_ < rhs;
}
