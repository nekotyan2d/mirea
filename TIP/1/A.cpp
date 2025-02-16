#include <iostream>
#include <cmath>

using namespace std;

class Triangle {
public:
    double a, b, c;

    void set(double a1, double b1, double c1) {
        this->a = a1;
        this->b = b1;
        this->c = c1;
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