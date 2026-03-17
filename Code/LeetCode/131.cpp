#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  auto partition(string s) -> vector<vector<string>> {
    auto n = s.length();
    vector<vector<string>> ans;
    vector<string> a;

    auto dfs = [&](this auto &&dfs, int i) -> void {
      if (i == n) {
        ans.emplace_back(a);
        return;
      }

      for (int j = i; j < n; ++j) {
        string sub = s.substr(i, j - i + 1);
        if (isPanlindromic(sub)) {
          a.emplace_back(sub);
          dfs(j + 1);
          a.pop_back();
        }
      }
    };

    dfs(0);
    return ans;
  }

private:
  inline auto isPanlindromic(const string &s) -> bool {
    int l = 0, r = int(s.length() - 1);
    while (l < r)
      if (s[l++] != s[r--])
        return false;
    return true;
  }
};

auto main() -> int { 
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Solution sol;
  string s = "aab";
  for (const auto &i : sol.partition(s)) {
    for (const auto &j : i)
      cout << j << ' ';
    cout << '\n';
  }
  return 0;
}