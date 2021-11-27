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
void inputMatrix(int**, int, int);
void printMatrix(int**, int, int);
int countingSpecialNumbers(int**, int, int);


int main() {

	int row_count, columns_count;

	row_count = inputRows();
	columns_count = inputColumns();

	int** matrix = new int* [row_count];
	for (int row = 0; row < row_count; row++) {
		matrix[row] = new int[columns_count];
	}

	generateMatrix(matrix, row_count, columns_count);
	printMatrix(matrix, row_count, columns_count);

	cout << "The number of 'special' matrix elements: " << countingSpecialNumbers(matrix, row_count, columns_count);
	
	delete[] matrix;
	cout << '\n';
	system("pause");
	return 0;
}


// Ввод и проверка элемента на корректный ввод
double checkNum() {
	double var;
	while (!(cin >> var) || cin.get() != '\n') {
		cout << "Error! Something go wrong ReEnter: ";
		cin.clear();
		while (cin.get() != '\n');
	}
	return var;
}

//Ввод количества строк матрицы
int inputRows() {
	int rows, columns, input_attempts = 1;
	do {
		if (input_attempts == 1) {
			cout << "Enter the number of rows in the matrix (from 1 to 9): ";
		}
		if (input_attempts > 1) {
			cout << "incorrect size! repeat" << "\n";
		}
		input_attempts++;
		
		rows = checkNum();
		cout << endl;
	} while ((rows < 1 || rows>9));

	return rows;
}

//Ввод количества столбцов матрицы
int inputColumns() {
	int columns, input_attempts = 1;
	do {
		if (input_attempts == 1) {
			cout << "Enter the number of columns in the matrix (from 1 to 9): ";
		}
		if (input_attempts > 1) {
			cout << "incorrect size! repeat" << "\n";
		}
		input_attempts++;

		columns = checkNum();
		cout << endl;
	} while ((columns < 1 || columns>9));

	return columns;
}

//Random matrix
void randomMatrix(int** matrix, int row_count, int columns_count) {
	int a, b;
	cout << "\nset the interval for random numbers( must be b > a):\n";
	
	do {
		cout << "a: ";
		a = checkNum();
		cout << "b: ";
		b = checkNum();
	} while (b < a);


	srand(time(0));
	for (int row = 0; row < row_count; row++) {
		for (int column = 0; column < columns_count; column++) {
			matrix[row][column] = rand() % (b - a + 1) + a;
		}
	}
}

//Ввод элементов матрицы
void inputMatrix(int** matrix, int row_count, int columns_count) {
	for (int row = 0; row < row_count; row++) {
		cout << "line #" << row + 1 << ": ";
		for (int column = 0; column < columns_count; column++) {
			cin >> matrix[row][column];
		}
	}
}

//Выбор между рандомной и ссвоей матрицой и ввод матрицы
void generateMatrix(int** matrix, int row_count, int columns_count) {

	cout << "Choose Random matrix or enter elements of matrix: 1 - random, 2 - enter";
	while (true) {
		char randomOrNot = _getch();
		cout << " " << randomOrNot;
		if (randomOrNot == '1') {
			return randomMatrix(matrix, row_count, columns_count);
		}
		else if (randomOrNot == '2') {
			cout << "\nEnter the matrix:\n";
			return inputMatrix(matrix, row_count, columns_count);
		}
		else {
			cout << "... Repeat.\n";
		}
	}

}

//Вывод матрицы на экран
void printMatrix(int** matrix, int row_count, int columns_count) {
	cout << "___________\n\n";
	for (int row = 0; row < row_count; row++) {

		for (int column = 0; column < columns_count; column++) {
			cout << setw(5) << matrix[row][column] << " ";
		}
		cout << "\n";
	}
}

//Подсчет количества 'особых' элементов матрицы
int countingSpecialNumbers(int** matrix, int row_count, int columns_count) {
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
			}
		}
	}
	return amount_of_special;
}

