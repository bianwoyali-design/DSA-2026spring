#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  auto countSubstrings(const string &s) -> int {
    string t = "^#";
    for (char c : s) {
      t += c;
      t += "#";
    }
    t += "$";

    int n = int(t.size());
    int ans = 0;
    vector<int> p(n);
    int r = 0, c = 0;
    for (int i = 1; i < n - 1; ++i) {
      if (i < r)
        p[i] = min(p[(c << 1) - i], r - i);
      else
        p[i] = 1;
      while (t[i - p[i]] == t[i + p[i]])
        ++p[i];
      if (i + p[i] > r)
        r = i + p[i], c = i;
      ans += p[i] / 2;
    }

    return ans;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  string s = "aaa";
  cout << sol.countSubstrings(s) << '\n';
  return 0;
}