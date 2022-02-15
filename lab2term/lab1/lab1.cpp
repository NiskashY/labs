#include <iostream>
#include <cmath>
#include <iomanip>

double MinSearch(double& a, double& b, double& e);
bool IsALessB(double a, double b);
void InputAB(double& a, double& b);
double InputNum();


int main() {
    double a, b, e;

    InputAB(a, b);
    e = InputNum();

    std::cout << std::fixed << std::setprecision(15) << MinSearch(a, b, e);

    return 0;
}


double MinSearch(double& a, double& b, double& e) {
    /// ������ ���������� ����������� ������ ���� ���,
    /// � ����� ��� ���������� � ����� ������ � �������� ���� �������
    static double min = 7 * sin(a) * sin(a);

    if (a > b) {
        return min;
    }

    double tmp = 7 * sin(a) * sin(a);
    if (tmp < min) {
        min = tmp;
    }
    a += e;
    MinSearch(a, b, e);

    return min;
}

bool IsALessB(double a, double b) {
    return (a > b);
}

void InputAB(double& a, double& b) {
    do {
        a = InputNum();
        b = InputNum();

    } while (IsALessB(a, b));
}

double InputNum() {
    double var;
    while (!(std::cin >> var) || std::cin.get() != '\n') {
        std::cout << "Error! Something go wrong ReEnter: ";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
    return var;
}
