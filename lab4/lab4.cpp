#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

//Прототипы функций

void chooseStandart_abh_OrNot(double&, double&, double&);
double calcResultFunctionS(int n, double x);
double calcResultFunctionY(double x);
void outRez(int n, double x, double a, int b, double h, double (*calcResultFunctiony)(double), double(*calcResultFunctions)(int, double));
double checkNum();
bool isAlessB(int, int);
template <typename My_Type> My_Type MyAbs(My_Type value);

int main() {
	int n;
	double  k, x, a = 0.1, b = 1, h = 0.1, sum, y, recurrence;

	chooseStandart_abh_OrNot(a, b, h);
	cout << "\nEnter n: ";
	n = checkNum();

	for (double x = a; x <= b; x += h) {
		outRez(n, x, a, b, h, calcResultFunctionY, calcResultFunctionS);
	}

	cout << '\n';
	system("pause");
	return 0;
}

bool isAlessB(int a, int b) {
	if (a >= b)
		cout << "\na should be less then b\n";
	return (a >= b);
}
void chooseStandart_abh_OrNot(double& a, double& b, double& h) {

	int check = 1;

	while (check)
	{
		cout << "You want to use  default settings or enter your own values?\n1 - use default\n2 - enter values\n";
		char term = _getch();
		if (term == '1') //Стандартный набор чисел 
		{
			cout << "a = " << a << " b = " << b << " h = " << h << endl;
			check = 0;
		}
		else if (term == '2') //Пользователь сам вводит переменные a,b,h
		{
			do {
				cout << "a - ";
				a = checkNum();
				cout << "b - ";
				b = checkNum();
			} while (isAlessB(a, b));

			cout << "h - \n";
			h = checkNum();
			cout << "a = " << a << " b = " << b << " h = " << h << endl;
			check = 0;
		}
		else cout << "Error! Reenter \n";
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
void outRez(int n, double x, double a, int b, double h, double (*calcResultFunctiony)(double), double(*calcResultFunctions)(int, double)) {
	cout << setprecision(1) << "x = " << x << setprecision(12) << fixed << "\t\tY(x) = " << calcResultFunctiony(x) << "\t\tS(x) = " << calcResultFunctions(n, x) << "\t\t|Y(x) - S(x)| = " << MyAbs(calcResultFunctions(n, x) - calcResultFunctiony(x))  << endl << endl;
}

//Функция, чтобы вводить переменную и проверять на корректный ввод
double checkNum() {
	double var;
	while (!(cin >> var) || cin.get() != '\n') {
		cout << "Error! Something go wrong ReEnter: ";
		cin.clear();
		while (cin.get() != '\n');
	}
	return var;
}

//собственная функция для абсол.тного щначения числа. Используется шаблон для того, чтобы можно было произвольный тип данных передать
template <typename My_Type> My_Type MyAbs(My_Type value) {
	return (value >= 0 ? value : -value);
}