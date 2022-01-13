/*Задана матрица размером NxM. Определить количество «особых» элементов матрицы, считая элемент 
  «особым», если он больше суммы остальных элементов своего столбца.*/


#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

//Прототипы функций
double checkNum();
int inputRows();
int inputColumns();
void generateMatrix(int**, int, int);
void randomMatrix(int** ,int, int);
bool isAlessB(int, int);
void setInterval(int& a, int& b);
void inputMatrix(int**, int, int);
int countingSpecialNumbers(int**, int, int, int*);
void printMatrix(int**, int, int);
void printSpecialElem(int*, int);


int main() {
	int row_count = inputRows(), columns_count = inputColumns();

	int* special_elements = new int[columns_count * row_count]; //я умножаю кол-во матриц на столбец, чтобы проходил случай, когда вводятсяотрицательные числа.
	int* pspec_elem = special_elements; /*Устанавливаю указатель на начало массива и в countingSpecialNumbers использую его, 
										для добавления в сам массив, т.к. начальный адрес массива нельзя изменять :( */

	int** matrix = new int* [row_count];
	for (int row = 0; row < row_count; row++) {
		matrix[row] = new int[columns_count];
	}
	
	generateMatrix(matrix, row_count, columns_count);
	printMatrix(matrix, row_count, columns_count);
	int amount_of_special = countingSpecialNumbers(matrix, row_count, columns_count, pspec_elem);
	cout << "The number of 'special' matrix elements: " << amount_of_special;
	printSpecialElem(special_elements, amount_of_special);


	for (int i = 0; i < row_count; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	system("pause");
	return 0;
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
int inputRows() {
	int rows, input_attempts = 1;
	do {
		if (input_attempts > 1) {
			cout << "incorrect size! repeat" << "\n";
		}
		if (input_attempts == 1) {
			cout << "Enter the number of rows in the matrix (from 1 to 9): ";
			input_attempts++;
		}
		
		rows = checkNum();
		cout << endl;
	} while ((rows < 1 || rows>9));

	return rows;
}
int inputColumns() {
	int columns, input_attempts = 1;
	do {
		if (input_attempts > 1) {
			cout << "incorrect size! repeat" << "\n";
		}
		if (input_attempts == 1) {
			cout << "Enter the number of columns in the matrix (from 1 to 9): ";
			input_attempts++;
		}

		columns = checkNum();
		cout << endl;
	} while ((columns < 1 || columns>9));

	return columns;
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

void randomMatrix(int** matrix, int row_count, int columns_count) {
	int a, b;
	cout << "\nset the interval for random numbers:\n";
	setInterval(a, b);
		srand(time(0));
	for (int row = 0; row < row_count; row++) {
		for (int column = 0; column < columns_count; column++) {
			matrix[row][column] = rand() % (b - a + 1) + a;
		}
	}
}
void inputMatrix(int** matrix, int row_count, int columns_count) {
	cout << "\nEnter the matrix:\n";
	for (int row = 0; row < row_count; row++) {
		cout << "line #" << row + 1 << ": ";
		for (int column = 0; column < columns_count; column++) {
			cin >> matrix[row][column];
		}
	}
}

void generateMatrix(int** matrix, int row_count, int columns_count) {
	while (true) {
		cout << "Choose Random matrix or enter elements of matrix: 1 - random, 2 - enter \t";
		char choice = _getch();
		cout << choice << '\n';
		if (choice == '1') {
			randomMatrix(matrix, row_count, columns_count);
		}
		else if (choice == '2') {
			inputMatrix(matrix, row_count, columns_count);
		}
		else {
			cout << "... Repeat.\n";
			continue;
		}
		break;
	}
}
void printMatrix(int** matrix, int row_count, int columns_count) {
	cout << "___________\n\n";
	for (int row = 0; row < row_count; row++) {

		for (int column = 0; column < columns_count; column++) {
			cout << setw(5) << matrix[row][column] << " ";
		}
		cout << "\n";
	}
}
void printSpecialElem(int* special_elem, int amount) {
	if (amount) {
		cout << "\nThis elements are: ";
		for (int i = 0; i < amount; i++) {
			cout << special_elem[i] << ' ';
		}
	}
	cout << '\n';
}
int countingSpecialNumbers(int** matrix, int row_count, int columns_count, int *pspec_elem) {
	int special, sum_of_column, amount_of_special = 0;

	for (int column = 0; column < columns_count; column++) {
		sum_of_column = 0;
		for (int row = 0; row < row_count; row++) {
			sum_of_column += matrix[row][column];
		}
		for (int row = 0; row < row_count; row++) {
			special = matrix[row][column];
			if (special > (sum_of_column - special)) {
				amount_of_special++;
				*pspec_elem = special;//добавляю в массив special_elements особый элемент через указатели
				pspec_elem++;
			}
		}
	}
	return amount_of_special;
}
