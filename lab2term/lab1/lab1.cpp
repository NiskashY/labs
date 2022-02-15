#include <iostream>
#include <cmath>
#include <iomanip>

double MinSearch(double& a, double& b, double& e);
double loop(double& a, double& b, double& e);
bool IsALessB(double a, double b);
void InputAB(double& a, double& b);
double InputNum();


int main() {
    double a, b, e;

    InputAB(a, b);
    e = InputNum();

    std::cout << std::fixed << std::setprecision(15) << MinSearch(a, b, e) << std::endl;
    std::cout << std::fixed << std::setprecision(15) << loop(a, b, e) << std::endl;


    return 0;
}

/*
double MinSearch(double& a, double& b, double& e) {
    /// данна€ переменна€ объ€вл€етс€ только один раз,
    /// а далее она измен€етс€ и видна только в пределах этой функции
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

double MinSearch(double& a, double& b, double& e) {
    static double min = 7 * sin(a) * sin(a);

    if (b - a <= e) {
        return min;
    }

    double mid = (b + a) / 2;
    double left = 7 * sin(mid - e) * sin(mid - e);
    double right = 7 * sin(mid + e) * sin(mid + e);

    if (left < right) {
        min = left;
        MinSearch(a, mid, e);
    }
    else {
        min = right;
        MinSearch(mid, b, e);
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
