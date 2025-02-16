#include <iostream>
#include <cmath>

using namespace std;

class Triangle {
public:
    double a, b, c;

    Triangle(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
        if (!exst_tr()) {
            this->a = 3;
            this->b = 4;
            this->c = 5;
        }
    }
    
    bool exst_tr() {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    void show() {
        std::cout << "A = " << a << ", B = " << b << ", C = " << c << std::endl;
    }

    double perimetr() {
        return a + b + c;
    }

    double square() {
        int p = perimetr() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};