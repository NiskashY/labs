//4.	????? ????????? ???????, ????????????? ????? ?????? ? ????????? ?????????????? ??????????

#include <iostream>

using namespace std;

int SIZEInput();
bool isInputOrRandom();
int searchFirstPositiveElement(int*, int);
int searchLastPositiveElement(int*, int);
void randomArray(int*, int);
void inputArray(int*, int);
void sumBetweenPositive(int*, int, int);
bool isAlessB(int, int);
double checkNum();

int main() {

	int SIZE = SIZEInput();
	int *arr = new int[SIZE];

	if (isInputOrRandom()) {
		inputArray(arr, SIZE);
	}
	else {
		randomArray(arr, SIZE);
	}
	int first_positive = searchFirstPositiveElement(arr, SIZE);
	int last_positive = searchLastPositiveElement(arr, SIZE);
	if (last_positive - first_positive <= 1) {
		cout << "Error! No sum between positive elements";
	}
	else {
		sumBetweenPositive(arr, first_positive, last_positive);
	}

	delete[] arr;
	cout << '\n';
	system("pause");
	return 0;
}

int SIZEInput() {
	int SIZE;

	do {
		cout << "Enter array SIZE from 1 to 100\t";
		SIZE = checkNum();
	} while (SIZE < 1 || SIZE > 100);

	return SIZE;
}
double checkNum() {
	double var;
	while (!(cin >> var) || cin.get() != '\n') {
		cout << "Error! Something go wrong ReEnter: ";
		cin.clear();
		while (cin.get() != '\n');
	}
	return var;
}

bool isInputOrRandom() {
	int choice;

	do {
		cout << "Do you want to use random numbers or enter them yourself ? \t 1 - random 2 - enter\n";
		choice = checkNum();
	} while (choice != 1 && choice != 2);

	return (choice == 2);
}
bool isAlessB(int a, int b) {
	if (a >= b)
		cout << "\na should be less then b\n";
	return (a >= b);
}
void setInterval(int& a, int& b) {
	do {
		cout << "a - ";
		a = checkNum();
		cout << "b - ";
		b = checkNum();
	} while (isAlessB(a, b));
}
void randomArray(int* arr, int SIZE) {
	srand(time(0));
	cout << "Enter range for random numbers [a;b]:\n";
	int a, b;
	setInterval(a, b);
	cout << "\nArray:	";
	for (int i = 0; i < SIZE; ++i) {
		arr[i] = rand() % (b - a + 1) + a;
		cout << arr[i] << " ";
	}
	cout << '\n';
}
void inputArray(int* arr, int SIZE) {
	cout << "Input Array:\n";
	for (int i = 0; i < SIZE; ++i) {
		cin >> arr[i];
	}
	/* 
	???? ??? ? ?????????, ?? ???? ????? ? ???? ????? ?????? ????? enter ????? ????? ?????? ???????? ??????!
	for (int i = 0; i < SIZE; ++i) {
		arr[i] = checkNum();
	}*/
}

void sumBetweenPositive(int* arr, int first, int last) {
	int sum = 0;
	for (int i = first + 1; i <= last - 1; i++) {
		sum += arr[i];
	}
	cout << "Sum =  " << sum;
}
int searchFirstPositiveElement(int* arr, int n) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > 0) {
			j = i;
			break;
		}
	}
	return j;
}
int searchLastPositiveElement(int* arr, int n) {
	int g = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (arr[i] > 0) {
			g = i;
			break;
		}
	}
	return g;
}