#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<set<int>> index(n);
    for (int i = 0; i < n; ++i)
    {
        int c;
        cin >> c;
        while (c--)
        {
            int idx;
            cin >> idx;
            index[i].insert(idx);
        }
    }

    int m;
    cin >> m;
    while (m--)
    {
        vector<int> stat(n);
        for (auto &s : stat)
            cin >> s;

        set<int> result;
        for (int i = 0; i < n; ++i)
            if (stat[i] == 1)
            {
                if (result.empty())
                    result = index[i];
                else
                {
                    set<int> intersection;
                    set_intersection(
                        result.begin(), result.end(),
                        index[i].begin(), index[i].end(),
                        inserter(intersection, intersection.begin()));
                    result.swap(intersection);
                }
                if (result.empty())
                    break;
            }

        if (!result.empty())
            for (int i = 0; i < n; ++i)
                if (stat[i] == -1)
                {
                    set<int> difference;
                    set_difference(
                        result.begin(), result.end(),
                        index[i].begin(), index[i].end(),
                        inserter(difference, difference.begin()));
                    result.swap(difference);
                    if (result.empty())
                        break;
                }

        if (result.empty())
            cout << "NOT FOUND";
        else
            for (const auto &a : result)
                cout << a << ' ';
        cout << '\n';
    }

    return 0;
}