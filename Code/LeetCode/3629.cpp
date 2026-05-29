#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

class Solution {
public:
  auto minJumps(std::vector<int> &nums) -> int {
    if (nums.size() == 1) {
      return 0;
    }

    int max_num = *std::max_element(nums.begin(), nums.end());
    std::vector<int> smallest_prime(max_num + 1, 0);
    for (int i = 2; i <= max_num; ++i) {
      if (smallest_prime[i] == 0) {
        smallest_prime[i] = i;
        if (1LL * i * i <= max_num) {
          for (long long j = 1LL * i * i; j <= max_num; j += i) {
            if (smallest_prime[j] == 0) {
              smallest_prime[j] = i;
            }
          }
        }
      }
    }

    int n = static_cast<int>(nums.size());
    std::unordered_map<int, std::vector<int>> to;
    to.reserve(n * 3);
    for (int i = 0; i < n; ++i) {
      int x = nums[i];
      while (x > 1) {
        int p = smallest_prime[x];
        to[p].emplace_back(i);
        while (x % p == 0) {
          x /= p;
        }
      }
    }

    std::queue<int> q;
    std::vector<bool> visited(n, false);
    q.emplace(0);
    visited[0] = true;

    int step = 0;
    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        int u = q.front();
        q.pop();

        if (u == n - 1) {
          return step;
        }

        if (u + 1 < n && !visited[u + 1]) {
          visited[u + 1] = true;
          q.emplace(u + 1);
        }
        if (u - 1 >= 0 && !visited[u - 1]) {
          visited[u - 1] = true;
          q.emplace(u - 1);
        }

        if (nums[u] >= 2 && smallest_prime[nums[u]] == nums[u]) {
          auto it = to.find(nums[u]);
          if (it != to.end()) {
            for (int v : it->second) {
              if (!visited[v]) {
                visited[v] = true;
                q.emplace(v);
              }
            }
            it->second.clear();
          }
        }
      }
      ++step;
    }

    return -1;
  }
};
