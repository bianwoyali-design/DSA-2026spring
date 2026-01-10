#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    map<string, vector<string>> mp;
    while (n--)
    {
        string str;
        cin >> str;
        int it = str.find("-");
        string first = str.substr(0, it);
        string second = str.substr(it + 1);
        mp[first].push_back(second);
    }

    for (auto &sub : mp)
    {
        sort(sub.second.begin(), sub.second.end(), [](const string &a, const string &b) {
            if (a.back() == b.back())
                return stod(a.substr(0, a.size() - 1)) < stod(b.substr(0, b.size() - 1));
            return a.back() > b.back();
        });
        cout << sub.first << ": ";
        for (int i = 0; i < sub.second.size(); i++)
        {
            cout << sub.second[i];
            if (i != sub.second.size() - 1)
                cout << ", ";
            else
                cout << '\n';
        }
    }
    return 0;
}
