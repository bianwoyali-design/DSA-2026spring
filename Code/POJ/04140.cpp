#include <iostream>
#include <cmath>
using namespace std;

double eps = 1e-9;

double f(double x) // f(x)
{
    return x * x * x - 5 * x * x + 10 * x - 80;
}

double f_(double x) // f'(x)
{
    return 3 * x * x - 10 * x + 10;
}

int main()
{
    double x = 0, y = x - f(x) / f_(x);
    while (abs(y - x) >= eps)
    {
        x = y;
        y = x - f(x) / f_(x);
    }

    printf("%.9lf\n", y);
    return 0;
}