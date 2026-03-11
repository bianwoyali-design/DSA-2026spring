#include <iostream>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    if (n == 0)
    {
        cout << 1 << '\n';
        return 0;
    }

    int w = 32 - __builtin_clz(n);
    int MASK = (1 << w) - 1;
    cout << (n ^ MASK) << '\n';
    return 0;
}