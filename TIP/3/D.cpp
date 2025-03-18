#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class SuperFraction
{
    T a, b;

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
            a = (int)a % (int)b;
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
    SuperFraction() : a(0), b(1) {}

    SuperFraction(T a, T b)
    {
        this->a = floor(a);
        this->b = floor(b);
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

template <typename T>
class SuperExtraMegaWowOfFractions
{
    vector<SuperFraction<T>> f;

public:
    bool isEmpty()
    {
        return f.empty();
    }

    void append(SuperFraction<T> a)
    {
        for (SuperFraction<T> ff : f)
        {
            if (ff.get_a() == a.get_a() && ff.get_b() == a.get_b())
            {
                return;
            }
        }
        f.push_back(a);
    }

    void exclude(SuperFraction<T> a)
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

    SuperFraction<T> sum()
    {
        if (isEmpty())
        {
            return SuperFraction<T>();
        }

        int n = 0;
        int d = 1;

        for (SuperFraction<T> &ff : f)
        {
            n = n * ff.get_b() + ff.get_a() * d;
            d = d * ff.get_b();

            SuperFraction<T> t(n, d);
            n = t.get_a();
            d = t.get_b();
        }

        return SuperFraction<T>(n, d);
    }
};