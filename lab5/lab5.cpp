#include <iostream>

using namespace std;

double enterAndCheckNum();

int main() {
	int a, b, i, j = 0, g = 0, n, sum = 0, choice;

	do {
		cout << "Enter array size from 1 to 100\t";
		n = enterAndCheckNum();
	} while (n < 1 || n>100);

	int *arr = new int[n];

	do{
		cout << "Do you want to use random numbers or enter them yourself ? \t 1 - random 2 - enter\n";
		choice = enterAndCheckNum();
	} while (choice != 1 && choice != 2);

	if (choice == 2){
		//Ввод своих чисел в массив
		for (i = 0; i < n; ++i)
			cin >> arr[i];
	}
	else {
		//Рандомные числа в массив
		srand(time(0));
		cout << "Enter range for random numbers [a;b]:\na - ";
		cin >> a;
		cout << "b - ";
		cin >> b;
		for (i = 0; i < n; ++i) {
			arr[i] = rand() % (b - a + 1) + a;
			cout << arr[i] << " ";
		}
	}
	//Ищем первый положительный элемент
	for (i = 0; i < n; i++) {
		if (arr[i] > 0) {
			j = i; 
			break;
		}
	}
	//Ищем последний положительный элемент, начиная с конца
	for(i = n-1; i>=j; i--){
		if (arr[i] > 0) {
			g = i;
			break;
		}
	}
	if (abs(g - j) <= 1) cout << "Error!";
	else {
		for (i = j+1; i <= g-1; i++) {
			sum += arr[i];
		}
		cout << "Sum =  " << sum;
	}
	delete[] arr;	
	return 0;
}

double enterAndCheckNum() {//Функция чтобы вводить переменную и проверять на корректный ввод
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
