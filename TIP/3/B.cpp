#include <iostream>
#include <cmath>

using namespace std;

class Fraction
{
    int a, b;

    int gcd(int m, int n)
    {
        if (n == 0)
        {
            return m;
        }
        else
        {
            return gcd(n, m % n);
        }
    }

    void fix()
    {
        if (a >= b)
        {
            a = a % b;
        }

        if (a == 0)
        {
            b = 1;
            return;
        }

        int d = gcd(a, b);
        a /= d;
        b /= d;
    }

public:
    Fraction() : a(0), b(1) {}

    Fraction(int a, int b)
    {
        this->a = a;
        this->b = b;
        fix();
    }

    void print()
    {
        cout << a << "/" << b << endl;
    }

    int get_a()
    {
        return a;
    }

    int get_b()
    {
        return b;
    }

    Fraction operator+(Fraction f)
    {
        int n, d;
        if (b == f.get_b())
        {
            n = a + f.get_a();
            d = b + f.get_b();
        }
        else
        {
            n = a * f.get_b() + f.get_a() * b;
            d = b * f.get_b();
        }
        return Fraction(n, d);
    }

    Fraction operator*(Fraction f)
    {
        return Fraction(a * f.get_a(), b * f.get_b());
    }

    Fraction operator/(Fraction f)
    {
        return Fraction(a * f.get_b(), b * f.get_a());
    }
};