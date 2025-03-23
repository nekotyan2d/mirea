#include <iostream>
#include <cmath>

using namespace std;

class Triangle
{
public:
    double a, b, c;

    class WrongTriangleSideException
    {
    };

    Triangle(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        if (!exst_tr())
        {
            throw WrongTriangleSideException();
        }
    }

    bool exst_tr()
    {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    void show()
    {
        std::cout << "A = " << a << ", B = " << b << ", C = " << c << std::endl;
    }

    double perimetr()
    {
        return a + b + c;
    }

    double square()
    {
        int p = perimetr() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

#include "main4_1.cpp"