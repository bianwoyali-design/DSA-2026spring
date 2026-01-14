#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    string s;
    while (cin >> s)
    {
        string t = s;
        reverse(s.begin(), s.end());
        if (s == t)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}