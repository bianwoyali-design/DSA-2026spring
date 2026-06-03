#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, q;
  std::cin >> n >> q;

  std::vector<long long> need;
  bool has_free = false;

  for (int i = 0; i < n; ++i) {
    long long c;
    std::cin >> c;

    if (c <= 1) {
      // 0 可以继续保持 0 不参与乘积，也可以加到任意正数；
      // 1 可以保持 1，也可以加到任意更大的数。
      // 所以这样的表情位可以吸收最后剩下的乘积因子。
      has_free = true;
    } else {
      // c > 1 的位置已经非零，且只能变大，最终必须参与乘积，
      // 因此要给它分配一个 >= c 的因子。
      need.push_back(c);
    }
  }

  std::sort(need.rbegin(), need.rend());

  // suffix[i] 是 need[i..] 的最小可能乘积。
  // 若 suffix[i] > rest，则剩下这些必须位置无论怎么分配都不可能塞进 rest。
  constexpr long long limit = 1000000001LL;
  std::vector<long long> suffix(need.size() + 1, 1);
  for (int i = static_cast<int>(need.size()) - 1; i >= 0; --i) {
    if (suffix[i + 1] > limit / need[i]) {
      suffix[i] = limit;
    } else {
      suffix[i] = suffix[i + 1] * need[i];
    }
  }

  auto factorize = [](long long x) -> std::vector<std::pair<long long, int>> {
    std::vector<std::pair<long long, int>> factors;

    for (long long p = 2; p * p <= x; ++p) {
      if (x % p != 0) {
        continue;
      }

      int count = 0;
      while (x % p == 0) {
        x /= p;
        ++count;
      }
      factors.emplace_back(p, count);
    }

    if (x > 1) {
      factors.emplace_back(x, 1);
    }

    return factors;
  };

  auto get_divisors = [&](long long x) -> std::vector<long long> {
    auto factors = factorize(x);
    std::vector<long long> divisors{1};

    // 如果 x = p1^a1 * p2^a2 * ...，
    // 所有约数就是每个质因数各选 0..ai 次后的乘积。
    for (auto [p, count] : factors) {
      int size = static_cast<int>(divisors.size());
      long long power = 1;

      for (int e = 1; e <= count; ++e) {
        power *= p;
        for (int i = 0; i < size; ++i) {
          divisors.push_back(divisors[i] * power);
        }
      }
    }

    std::sort(divisors.rbegin(), divisors.rend());
    return divisors;
  };

  while (q-- > 0) {
    long long x;
    std::cin >> x;

    if (suffix[0] > x) {
      std::cout << "No\n";
      continue;
    }

    auto divisors = get_divisors(x);
    std::vector<std::unordered_set<long long>> failed(need.size() + 1);

    auto dfs = [&](auto &&self, int index, long long rest) -> bool {
      if (suffix[index] > rest) {
        return false;
      }

      if (index == static_cast<int>(need.size())) {
        // 所有 c > 1 的位置都分配完了。
        // 如果有 0/1 位置，剩余 rest 可以交给它吸收；
        // 否则必须刚好用完，也就是 rest == 1。
        return has_free || rest == 1;
      }

      if (failed[index].count(rest)) {
        return false;
      }

      // 给 need[index] 分配一个最终值 d。
      // d 必须是 rest 的约数，否则乘积无法刚好变成目标 x；
      // d 还必须 >= need[index]，因为这个位置只能增加不能减少。
      for (long long d : divisors) {
        if (d < need[index]) {
          break;
        }

        if (rest % d != 0) {
          continue;
        }

        if (self(self, index + 1, rest / d)) {
          return true;
        }
      }

      failed[index].insert(rest);
      return false;
    };

    std::cout << (dfs(dfs, 0, x) ? "Yes\n" : "No\n");
  }
}
