#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
private:
    map<int, int, greater<int>> mp;

public:
    void init()
    {
        int x, y;
        while (cin >> x >> y)
        {
            if (y < 0)
                break;
            mp[y] += x;
        }
    }

    void output()
    {
        bool first = true;
        for (auto &m : mp)
        {
            if (m.second == 0)
                continue;
            if (!first)
                cout << " ";
            cout << "[ " << m.second << " " << m.first << " ]";
            first = false;
        }
        cout << '\n';
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--)
    {
        Solution sol;
        sol.init();
        sol.init();
        sol.output();
    }

    return 0;
}