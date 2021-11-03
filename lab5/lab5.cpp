//4.	Сумму элементов массива, расположенных между первым и последним положительными элементами

#include <iostream>

using namespace std;

int sizeInput();
bool isInputOrRandom();

int searchFirstPositiveElement(int*, int);
int searchLastPositiveElement(int*, int);

void randomArray(int*, int);
void inputArray(int*, int);

void sumBetweenPositive(int*, int, int);

double enterAndCheckNum();

int main() {

	int size = sizeInput();
	int *arr = new int[size];


	if (isInputOrRandom()) {
		inputArray(arr, size);
	}
	else {
		randomArray(arr, size);
	}

	int first_positive = searchFirstPositiveElement(arr, size);
	int last_positive = searchLastPositiveElement(arr, size);

	if (last_positive - first_positive <= 1) cout << "Error! No sum between positive elements";
	else {
		sumBetweenPositive(arr, first_positive, last_positive);
	}

	delete[] arr;	
	return 0;
}

int sizeInput() {
	int size;

	do {
		cout << "Enter array size from 1 to 100\t";
		size = enterAndCheckNum();
	} while (size < 1 || size > 100);

	return size;
}

bool isInputOrRandom() {
	int choice;

	do {
		cout << "Do you want to use random numbers or enter them yourself ? \t 1 - random 2 - enter\n";
		choice = enterAndCheckNum();
	} while (choice != 1 && choice != 2);

	if (choice == 2) { 
		return 1; 
	}
	return 0;
}

void inputArray(int* arr, int size) {
	cout << "Input Array:\n";
	for (int i = 0; i < size; ++i) {
		cin >> arr[i];
	}
	/* 
	Этот код с проверкой, но есть минус в виде ввода только через enter иначе будет всегда выдавать ошибку!
	for (int i = 0; i < size; ++i) {
		arr[i] = enterAndCheckNum();
	}*/
}

//Рандомный массив
void randomArray(int* arr, int size) {
	srand(time(0));
	cout << "Enter range for random numbers [a;b]:\na - ";
	int a = enterAndCheckNum();
	cout << "b - ";
	int b = enterAndCheckNum();
	cout << "\nArray:	";
	for (int i = 0; i < size; ++i) {
		arr[i] = rand() % (b - a + 1) + a;
		cout << arr[i] << " ";
	}
	cout << '\n';
}

//Сумма между положительными элементами
void sumBetweenPositive(int* arr, int first, int last) {
	int sum = 0;
	for (int i = first + 1; i <= last - 1; i++) {
		sum += arr[i];
	}
	cout << "Sum =  " << sum;
}
//Поиск первого положительного элемента
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

//Поиск последнего положительного элемента
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

//Функция чтобы вводить переменную и проверять на корректный ввод
double enterAndCheckNum() {
	double var;
	bool local_check = 1;

	while (local_check)
	{
		cin >> var;
		if (cin.get() != '\n')
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Error! Something go wrong ReEnter: ";
		}
		else local_check = 0;
	}

	return var;
}
