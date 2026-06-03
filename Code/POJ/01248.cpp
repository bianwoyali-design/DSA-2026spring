#include <algorithm>
#include <iostream>
#include <string>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int target;
  std::string s;
  while (std::cin >> target >> s && target != 0 && s != "END") {
    int n = s.length();
    bool found = false;
    std::string res = "no solution";

    std::sort(s.rbegin(), s.rend());

    for (int v = 0; v < n && !found; ++v) {
      for (int w = 0; w < n && !found; ++w) {
        if (v == w) {
          continue;
        }
        for (int x = 0; x < n && !found; ++x) {
          if (x == w || x == v) {
            continue;
          }
          for (int y = 0; y < n && !found; ++y) {
            if (y == x || y == w || y == v) {
              continue;
            }
            for (int z = 0; z < n && !found; ++z) {
              if (z == y || z == x || z == w || z == v) {
                continue;
              }

              int vv = s[v] - 'A' + 1;
              int vw = s[w] - 'A' + 1;
              int vx = s[x] - 'A' + 1;
              int vy = s[y] - 'A' + 1;
              int vz = s[z] - 'A' + 1;

              found = (vv - vw * vw + vx * vx * vx - vy * vy * vy * vy +
                           vz * vz * vz * vz * vz ==
                       target);

              if (found) {
                res = "";
                res += s[v];
                res += s[w];
                res += s[x];
                res += s[y];
                res += s[z];
              }
            }
          }
        }
      }
    }

    std::cout << res << '\n';
  }
}