#include "tests.h"

void Test1() {
	std::string request, result;
	request = "a+b*(c-d)/e+f";
	result = CreateReversePolishNotation(request);
	if (result != "abcd-*e/+f+")
		std::cout << "Test1.\t" << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void Test2() {
	std::string request, result;
	request = "a/(b-c)*(d+e)";
	result = CreateReversePolishNotation(request);
	if (result != "abc-/de+*")
		std::cout << "Test2.\t" << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void Test3() {
	std::string request, result;
	request = "(a+b)*(c-d)/e";
	result = CreateReversePolishNotation(request);
	if (result != "ab+cd-*e/")
		std::cout << "Test3.\t" << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void Test4() {
	std::string request, result;
	request = "a-(b+c*d)/e";
	result = CreateReversePolishNotation(request);
	if (result != "abcd*+e/-")
		std::cout << "Test4.\t" << "Request: " + request + ". Result: " + result + "\tError!\n";
}

void RunTests() {
	Test1();
	Test2();
	Test3();
	Test4();
}