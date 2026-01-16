#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<string> findOcurrences(string text, string first, string second)
    {
        vector<string> words;
        int s = 0, e = 0, len = text.length();
        while (true)
        {
            while (s < len && text[s] == ' ')
                ++s;
            if (s >= len)
                break;
            e = s + 1;
            while (e < len && text[e] != ' ')
                ++e;
            words.push_back(text.substr(s, e - s));
            s = e + 1;
        }
        vector<string> ret;
        for (int i = 2; i < words.size(); i++)
            if (words[i - 2] == first && words[i - 1] == second)
                ret.push_back(words[i]);
        return ret;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    string text = "alice is aa good girl she is a good student", first = "a", second = "good";
    Solution sol;
    vector<string> ans = sol.findOcurrences(text, first, second);
    for (const auto &a : ans)
        cout << a << ' ';
    return 0;
}