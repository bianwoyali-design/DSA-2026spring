#include <iostream>
using namespace std;

using ll = long long;
class Solution {
private:
  auto get_Sk_len(ll k) -> ll {
    ll len = 0;
    for (ll start = 1, digits = 1; start <= k; start *= 10, digits++) {
      ll end = start * 10 - 1;
      if (end > k)
        end = k;
      len += (end - start + 1) * digits;
    }
    return len;
  }

  auto get_total_len(ll k) -> ll {
    ll total = 0;
    for (ll start = 1, digits = 1; start <= k; start *= 10, digits++) {
      ll end = start * 10 - 1;
      if (end > k)
        end = k;

      ll first_Sk_len = get_Sk_len(start);
      ll last_Sk_len = get_Sk_len(end);
      ll n = (end - start + 1);

      total += (first_Sk_len + last_Sk_len) * n / 2;
    }
    return total;
  }

public:
  auto solve(int x) -> char;
};
auto Solution::solve(int x) -> char {
  ll l = 1, r = 31268, k = 1;
  while (l <= r) {
    ll mid = l + (r - l) / 2;
    if (get_total_len(mid) >= x) {
      k = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  x -= get_total_len(k - 1);

  l = 1, r = k;
  ll num = 1;
  while (l <= r) {
    ll mid = l + (r - l) / 2;
    if (get_Sk_len(mid) >= x) {
      num = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  x -= get_Sk_len(num - 1);
  string s = to_string(num);
  return s[x - 1];
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  Solution sol;
  while (t--) {
    ll x;
    cin >> x;
    cout << sol.solve(x) << '\n';
  }
  return 0;
}