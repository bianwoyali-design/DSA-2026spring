#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    char nextGreatestLetter(vector<char> &letters, char target)
    {
        return target < letters.back() ? *upper_bound(letters.begin(), letters.end() - 1, target) : letters[0];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<char> letters = {'x', 'x', 'y', 'y'};
    char target = 'z';
    cout << sol.nextGreatestLetter(letters, target) << '\n';
    return 0;
}