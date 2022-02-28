//6. Найти  методом  деления   отрезка   пополам  минимум  функции f(x) = = 7sin2(x) на отрезке [2, 6] с заданной точностью  (например 0,01). 
#include <iostream>
#include <cmath>
#include <iomanip>

double MinSearch(double& a, double& b, double& e, double& min);
double loop(double& a, double& b, double& e);
bool IsALessB(double a, double b);
void InputAB(double& a, double& b);
double InputNum();


int main() {
    double a, b, e;

    InputAB(a, b);
    std::cout << "Input e: ";
    e = InputNum();
    std::cout << "\n";
    double min = 7 * sin(a) * sin(a);
//    std::cout << std::fixed << std::setprecision(15) << MinSearch(a, b, e) << std::endl;
    std::cout << std::fixed << std::setprecision(15) << MinSearch(a, b, e, min) << std::endl;
    std::cout << std::fixed << std::setprecision(15) << loop(a, b, e) << std::endl;


    return 0;
}

//double MinSearch(double& a, double& b, double& e) {
   // static double min = 7 * sin(a) * sin(a);
double MinSearch(double& a, double& b, double& e, double& min) {
    if (b - a <= e) {
        return min;
    }

    double mid = (b + a) / 2;
    double left = 7 * sin(mid - e) * sin(mid - e);
    double right = 7 * sin(mid + e) * sin(mid + e);

    if (left < right) {
        min = left;
        MinSearch(a, mid, e, min);
    }
    else {
        min = right;
        MinSearch(mid, b, e, min);
    }

    return min;
}

double loop(double& a, double &b, double& e){
    double min = 7 * sin(a) * sin(a);

    while (b - a > e) {
        double mid = (b + a) / 2;
        double left = 7 * sin(mid - e) * sin(mid - e);
        double right = 7 * sin(mid + e) * sin(mid + e);

        if (left < right) {
            min = left;
            b = mid;
        }
        else {
            min = right;
            a = mid;
        }
    }

    return min;
}

bool IsALessB(double a, double b) {
    return (a > b);
}

void InputAB(double& a, double& b) {
    do {
        std::cout << "Input a: ";
        a = InputNum();
        std::cout << "\nInput b: ";
        b = InputNum();
        std::cout << "\n";
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

/*
double MinSearch(double& a, double& b, double& e) {
    /// данная переменная объявляется только один раз,
    /// а далее она изменяется и видна только в пределах этой функции
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
}*/