#define _USE_MATH_DEFINES
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

    bool is_similar(Triangle& t2) {
        return (t2.a / a) == (t2.b / b) && (t2.b / b) == (t2.c / c) && (t2.a / a) == (t2.c / c);
    }

    void show() {
        std::cout << "A = " << a << ", B = " << b << ", C = " << c << std::endl;
    }

    double perimetr() {
        return a + b + c;
    }

    double square() {
        double p = perimetr() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    double get_a() {
        return a;
    }

    double get_b() {
        return b;
    }

    double get_c() {
        return c;
    }
};

class Circle {
public:
    float r, x, y;
    Circle(float r, float x, float y) {
        this->r = r;
        this->x = x;
        this->y = y;
    }

    void set_circle(float r, float x, float y) {
        this->r = r;
        this->x = x;
        this->y = y;
    }

    bool triangle_around(Triangle& t) {
        return r == ((t.get_a() * t.get_b() * t.get_c()) / (4 * t.square()));
    }

    bool triangle_in(Triangle& t) {
        return r == t.square() / (t.perimetr() / 2);
    }

    bool check_circle(Circle& c) {
        float d = sqrt(pow(c.x - x, 2) + pow(c.y - y, 2));
        return d <= r + c.r && d >= abs(r - c.r);
    }

    float square() {
        return M_PI * r * r;
    }
};