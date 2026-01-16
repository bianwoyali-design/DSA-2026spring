#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    unordered_map<string, set<int>> hash;
    for (int i = 1; i <= n; ++i)
    {
        int a;
        cin >> a;
        while (a--)
        {
            string s;
            cin >> s;
            hash[s].emplace(i);
        }
    }

    int m;
    cin >> m;
    while (m--)
    {
        string s;
        cin >> s;
        if (hash[s].empty())
            cout << "NOT FOUND\n";
        else
            for (const auto &h : hash[s])
                cout << h << ' ';
        cout << '\n';
    }

    return 0;
}