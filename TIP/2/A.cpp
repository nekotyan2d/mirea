#include <iostream>
#include <cmath>

using namespace std;

class Figure {
    public:
        virtual double square() = 0;
};

class Triangle : public Figure {
    private:
        double a, b, c;
    public:
        Triangle(double a, double b, double c) : a(a), b(b), c(c) {};
        double square() {
            double p = (a + b + c) / 2;
            return sqrt(p * (p - a) * (p - b) * (p - c));
        };
};

class Rectangle : public Figure {
    private:
        double a, b, c;
    public:
        Rectangle(double a, double b) : a(a), b(b) {};
        double square() {
            return a * b;
        };
};

class Trapezoid : public Figure {
    private:
        double a, b, h;
    public:
        Trapezoid(double a, double b, double h) : a(a), b(b), h(h) {};
        double square() {
            return 0.5 * (a + b) * h;
        };
};