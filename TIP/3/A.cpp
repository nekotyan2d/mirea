#include <iostream>
#include <vector>
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
};

class SetOfFractions
{
    vector<Fraction> f;

public:
    bool isEmpty()
    {
        return f.empty();
    }

    void append(Fraction a)
    {
        for (Fraction ff : f)
        {
            if (ff.get_a() == a.get_a() && ff.get_b() == a.get_b())
            {
                return;
            }
        }
        f.push_back(a);
    }

    void exclude(Fraction a)
    {
        for (auto it = f.begin(); it != f.end(); ++it)
        {
            if ((*it).get_a() == a.get_a() && (*it).get_b() == a.get_b())
            {
                f.erase(it);
                return;
            }
        }
    }

    Fraction sum()
    {
        if (isEmpty())
        {
            return Fraction();
        }

        int n = 0;
        int d = 1;

        for (Fraction &ff : f)
        {
            n = n * ff.get_b() + ff.get_a() * d;
            d = d * ff.get_b();

            Fraction t(n, d);
            n = t.get_a();
            d = t.get_b();
        }

        return Fraction(n, d);
    }
};