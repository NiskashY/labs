// cos(x) graphic
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
int main(void)
{
	for (int i = 0; i < 10; i++)
		std::cout << "\n";
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	MoveToEx(hDC, 0, 85, NULL);
	LineTo(hDC, 200, 85);
	MoveToEx(hDC, 100, 0, NULL);
	LineTo(hDC, 100, 170);
	int  b = 1, n;
	for (double x = -8.0; x <= 8.0; x += 0.01) // O(100,85) - центр
	{
		double recurrence, sum, k;
		for (sum = recurrence = k = 1; k <= 10; ++k)
		{
			recurrence *= (-1) * x * x / ((2 * k - 1) * (2 * k));
			sum += recurrence;
		}
		MoveToEx(hDC, 10 * x + 100, -10 * sum + 85, NULL);//
		LineTo(hDC, 10 * x + 100, -10 * sum + 85);
	}

}