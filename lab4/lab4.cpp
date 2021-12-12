#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

//Прототипы функций

void chooseStandart_abh_orNot(double&, double&, double&);
double calcResultFunctionS(int n, double x);
double calcResultFunctionY(double x);
void outRez(int n, double x, double a, int b, double h, double (*calcResultFunctiony)(double), double(*calcResultFunctions)(int, double));
double checkNum();
bool isAlessB(int, int);
void setIntervalABH(double&, double&, double&);
void showABH(double, double, double);
double MyAbs(double value);

int main() {
	int n;
	double  k, x, a = 0.1, b = 1, h = 0.1;

	chooseStandart_abh_orNot(a, b, h);
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
void chooseStandart_abh_orNot(double& a, double& b, double& h) {
	int check = 1;

	while (check)
	{
		cout << "You want to use  default settings or enter your own values?\n1 - use default\n2 - enter values\n";
		char term = _getch();
		if (term == '1') //Стандартный набор чисел 
		{
			showABH(a, b, h);
			check = 0;
		}
		else if (term == '2') //Пользователь сам вводит переменные a,b,h
		{
			setIntervalABH(a, b, h);
			showABH(a, b, h);
			check = 0;
		}
		else cout << "Error! Reenter \n";
	}

}
void showABH(double a, double b, double h) {
	cout << "a = " << a << " b = " << b << " h = " << h << endl;
}
void setIntervalABH(double& a, double& b, double& h) {
	do {
		cout << "a - ";
		a = checkNum();
		cout << "b - ";
		b = checkNum();
		cout << "h - \n";
		h = checkNum();
	} while (isAlessB(a, b));
}
double calcResultFunctionS(int n, double x) {

	double sum, recurrence, k;

	for (sum = recurrence = k = 1; k <= n; ++k)
	{
		recurrence *= (-1) * x * x / ((2 * k - 1) * (2 * k));
		sum += recurrence;
	}

	return sum;
}
double calcResultFunctionY(double x) {
	return cos(x);
}
void outRez(int n, double x, double a, int b, double h, double (*calcResultFunctiony)(double), double(*calcResultFunctions)(int, double)) {
	cout << fixed; //fixed - выводит в нотации с зафиксированным кол-вом чисел после запятой. кол-во цифр задаётся через setprecision.
	cout << setprecision(1) << "x = " << x;
	cout << setprecision(7) << "\t\tY(x) = " << calcResultFunctiony(x);
	cout << "\tS(x) = " << calcResultFunctions(n, x);
	cout << scientific << "\t|Y(x) - S(x)| = " << MyAbs(calcResultFunctions(n, x) - calcResultFunctiony(x)) << endl << endl; //scientific - выводит в научной нотации, т.е XX.XXXeN
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
double MyAbs(double value) {
	return (value >= 0 ? value : -value);
}