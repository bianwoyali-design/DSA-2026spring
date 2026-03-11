#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    string s;
    cin >> s;
    int maxLen = 0;
    int left = 0;
    vector<int> last(26, -1);
    for (int right = 0; right < s.length(); ++right)
    {
        int char_idx = s[right] - 'a';
        if (last[char_idx] >= left)
            left = last[char_idx] + 1;

        last[char_idx] = right;
        maxLen = max(maxLen, right - left + 1);
    }

    cout << maxLen << '\n';
    return 0;
}