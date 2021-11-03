/*Задана матрица размером NxM. Определить количество «особых» элементов матрицы, считая элемент 
  «особым», если он больше суммы остальных элементов своего столбца.*/


#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

//Прототипы функций
double checkNum();
int inputMatrixRows();
int inputMatrixColumns();
int initializeMatrix(int**, int, int);
void printMatrix(int**, int, int);
int countingSpecialNumbers(int**, int, int);
int randomMatrix(int, int, int**);

int main() {

	int row, column, row_count, columns_count, input_attempts = 1;
	int** matrix;

	do {
		if (input_attempts > 1) {
			cout << "Re-enter!" << "\n";
		}
		input_attempts++;

		row_count = inputMatrixRows();
		columns_count = inputMatrixColumns();

		cout << endl;
	} while ((row_count < 1 || row_count>9) || (columns_count < 1 || columns_count>9));

	matrix = new int* [row_count];
	for (row = 0; row < row_count; row++) {
		matrix[row] = new int[columns_count];
	}

	cout << "Random matrix or enter elements of  matrix: 1 - random, 2 - enter";
	while (true) {
		char randomOrNot = _getch();
		cout << " " << randomOrNot;
		if (randomOrNot == '1') {
			randomMatrix(row_count, columns_count, matrix);
			break;
		}
		else if (randomOrNot == '2') {
			cout << "\nEnter the matrix:\n";
			initializeMatrix(matrix, row_count, columns_count);
			break;
		}
		else {
			cout << "... Repeat.\n";
		}
	}

	cout << "___________\n\n";
	printMatrix(matrix, row_count, columns_count);

	cout << "The number of 'special' matrix elements: ";
	cout << countingSpecialNumbers(matrix, row_count, columns_count);
	
	delete[] matrix;
	system("pause");
	return 0;
}


// Ввод и проверка элемента на корректный ввод
double checkNum() {
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
		else
			local_check = 0;
	}
	return var;
}

//Ввод количества строк матрицы
int inputMatrixRows() {
	cout << "Enter the number of matrix rows (from 1 to 9): ";
	return  checkNum();
}

//Ввод количества столбцов матрицы
int inputMatrixColumns() {
	cout << "Enter the number of columns in the matrix (from 1 to 9): ";
	return checkNum();
}

//Random matrix
int randomMatrix(int row_count, int columns_count, int** matrix) {
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
	return **matrix;
}
//Ввод элементов матрицы
int initializeMatrix(int** matrix, int row_count, int columns_count) {
	for (int row = 0; row < row_count; row++) {
		cout << "line #" << row + 1 << ": ";
		for (int column = 0; column < columns_count; column++) {
			cin >> matrix[row][column];
		}
	}
	return **matrix;
}

//Вывод матрицы на экран
void printMatrix(int** matrix, int row_count, int columns_count) {
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

