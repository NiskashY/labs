#include <iostream>
#include <conio.h>

using namespace std;

double checkNum() {//Функция чтобы вводить переменную и проверять на корректный ввод
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
		cout << "x = " << x << "\t\tY(x) = " << y << "\t\tS(x) = " << sum << "\t\t|Y(x) - S(x)| = " << fabs(y - sum) << endl << endl;
	}

	system("pause");
	return 0;
}