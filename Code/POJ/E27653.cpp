#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Fraction
{
public:
    void plus(int a, int b, int c, int d)
    {
        int numerator = a * d + b * c;
        int lcm = b * d;
        int gcd2 = abs(__gcd(lcm, numerator));
        if (lcm / gcd2 != 1)
            cout << numerator / gcd2 << '/' << lcm / gcd2 << '\n';
        else
            cout << numerator / gcd2 << '\n';
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Fraction frac;
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    frac.plus(a, b, c, d);
    return 0;
}