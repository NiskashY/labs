#include <iostream>
#include <conio.h>

using namespace std;

//Прототипы функций
double calcResultFunctionS(int n, double x);
double calcResultFunctionY(double x);
void outRez(int n, double x, double a, int b, double h, double (*calcResultFunctiony)(double), double(*calcResultFunctions)(int, double));
double checkNum();

int main() {
	int  b, n;
	double  k, x, a, h, sum, y, recurrence;
	bool check = 1;
	while (check)
	{
		cout << "You want to use  default settings or enter your own values?\n1 - use default\n2 - enter values\n";
		char term = _getch();
		if (term == '1') //Стандартный набор чисел 
		{
			a = h = 0.1; b = 1;
			cout << "a = " << a << " b = " << b << " h = " << h << endl;
			check = 0;
		}
		else if (term == '2') //Пользователь сам вводит переменные a,b,h
		{
			cout << "Enter a\n";
			a = checkNum();
			cout << "Enter b\n";
			b = checkNum();
			cout << "Enter h\n";
			h = checkNum();
			cout << "a = " << a << " b = " << b << " h = " << h << endl;
			check = 0;
		}
		else cout << "Error! Reenter \n";

	}

	cout << "\nEnter n: ";
	n = checkNum();

	for (double x = a; x <= b; x += h) {
		outRez(n, x, a, b, h, calcResultFunctionY, calcResultFunctionS);
	}
		
}


//рекурентная формула для нахождения суммы
double calcResultFunctionS(int n, double x) {

	double sum, recurrence, k;

	for (sum = recurrence = k = 1; k <= n; ++k)
	{
		recurrence *= (-1) * x * x / ((2 * k - 1) * (2 * k));
		sum += recurrence;
	}

	return sum;
}

//формула для нахождения cos(x)
double calcResultFunctionY(double x) {
	return cos(x);
}

//Функция для вывода результата
void outRez(int n, double x, double a, int b, double h, double (* calcResultFunctiony)(double), double(* calcResultFunctions)(int, double) )  {
	cout << "x = " << x << "\t\tY(x) = " << calcResultFunctiony(x) << "\t\tS(x) = " << calcResultFunctions(n, x) << "\t\t|Y(x) - S(x)| = " << fabs(calcResultFunctions(n, x) - calcResultFunctiony(x)) << endl << endl;
}

//Функция, чтобы вводить переменную и проверять на корректный ввод
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
