#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    bool hasAllCodes(string s, int k)
    {
        if (s.size() < (1 << k) + k - 1)
            return false;

        int num = stoi(s.substr(0, k), nullptr, 2);
        unordered_set<int> hash = {num};

        for (int i = 1; i + k <= s.size(); ++i)
        {
            num = (num - ((s[i - 1] - '0') << (k - 1))) * 2 + (s[i + k - 1] - '0');
            hash.insert(num);
        }

        return hash.size() == (1 << k);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "0110";
    int k = 2;
    cout << sol.hasAllCodes(s, k) << '\n';
    return 0;
}