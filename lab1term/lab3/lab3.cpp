#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

double checkNum() {
	double var;
	while (!(cin >> var) || cin.get() != '\n') {
		cout << "Error! Something go wrong ReEnter: ";
		cin.clear();
		while (cin.get() != '\n');
	}
	return var;
}

int main()
{
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
	for (x = a; x <= b; x += h) 	//рекурентная формула для нахождения суммы 
	{
		y = cos(x);
		for (sum = recurrence = k = 1; k <= n; ++k)
		{
			recurrence *= (-1) * x * x / ((2 * k - 1) * (2 * k));
			sum += recurrence;
		}
		cout << fixed; //fixed - выводит в нотации с зафиксированным кол-вом чисел после запятой. кол-во цифр задаётся через setprecision.
		cout << setprecision(1) << "x = " << x;
		cout << setprecision(7) << "\t\tY(x) = " << y;
		cout << "\tS(x) = " << sum;
		cout << scientific << setprecision(3) << "\t|Y(x) - S(x)| = " << fabs(y - sum) << endl << endl; //scientific - выводит в научной нотации, т.е XX.XXXeN
	}

	system("pause");
	return 0;
}