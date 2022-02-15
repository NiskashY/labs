#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

//Прототипы функций

void chooseStandart_abh_orNot(double&, double&, double&);
void chooseOutRez(int, double, double, double, bool*);
double calcResultFunctionS(int, double);
double calcResultFunctionY(int, double);
double difference(int, double);
void outRez(int, double, double, double, double (*function)(int, double));
double checkNum();
template <typename T> bool isAlessB(T, T);
void setIntervalABH(double&, double&, double&);
void showABH(double, double, double);
template <typename T> double  MyAbs(T);

int main() {
	int n;
	double a = 0.1, b = 1, h = 0.1;

	chooseStandart_abh_orNot(a, b, h);
	cout << "\nEnter n: ";
	n = checkNum();

	bool status = 1;
	do {
		chooseOutRez(n, a, b, h, &status);
	} while (status);

	cout << '\n';
	system("pause");
	return 0;
}

void chooseOutRez(int n, double a, double b, double h, bool* status) {
	const char* MENU_TMP = "\nInput:\n1 - for function F(x) = S(x)\n2 - for function F(x) = Y(x)\n3 - for function F(x) = |S(x) - Y(x)|\n4 - change a, b, h\nelse - quit\n";
	cout << MENU_TMP;

	char choice = _getch();
	cout << choice << '\n';

	switch (choice) {
		case '1': {
			cout << "F(x) = S(x)\n"; 
			outRez(n, a, b, h, calcResultFunctionS);
			break;
		}
		case '2': {
			cout << "F(x) = Y(x)\n";
			outRez(n, a, b, h, calcResultFunctionY);
			break;
		}
		case '3': {
			cout << "F(x) = |S(x) - Y(x)|\n";
			outRez(n, a, b, h, difference);
			break;
		}
		case '4': {
			chooseStandart_abh_orNot(a, b, h);
			break;
		}
		default: {
			cout << "Bye!\n";
			*status = 0;
		}
	}
}
void chooseStandart_abh_orNot(double& a, double& b, double& h) {
	int check = 1;

	while (check)
	{
		cout << "You want to use  default settings or enter your own values?\n1 - use default\nelse - enter values\n";
		char term = _getch();
		if (term == '1') //Стандартный набор чисел 
		{
			showABH(a, b, h);
			check = 0;
		}
		else //Пользователь сам вводит переменные a,b,h
		{
			setIntervalABH(a, b, h);
			showABH(a, b, h);
			check = 0;
		}
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
double calcResultFunctionY(int n, double x) {
	return cos(x);
}
double difference(int n, double x) {
	return MyAbs(calcResultFunctionS(n, x) - calcResultFunctionY(n, x));
}
void outRez(int n, double a, double b, double h, double (*function)(int, double)) {
	for (double x = a; x <= b; x += h) {
		cout << fixed; //fixed - выводит в нотации с зафиксированным кол-вом чисел после запятой. кол-во цифр задаётся через setprecision.
		cout << setprecision(1) << "x = " << x;
		cout << scientific <<  setprecision(5) << "\tF(x) = " << function(n, x) << '\n'; //scientific - выводит в научной нотации, т.е XX.XXXeN
	}
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
template <typename T> double  MyAbs(T value) {
	return (value >= 0 ? value : -value);
}
template <typename T> bool isAlessB(T a, T b) {
	if (a >= b)
		cout << "\na should be less then b\n";
	return (a >= b);
}
