#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string path;
  std::cin >> path;

  std::stack<std::string> files;

  for (int i = 0; i < path.size();) {
    if (path[i] == '/') {
      while (path[i] == '/' && i < path.size()) {
        ++i;
      }
    } else {
      std::string cache;
      while (path[i] != '/' && i < path.size()) {
        cache += path[i++];
      }

      if (cache == ".") {
        continue;
      } else if (cache == "..") {
        if (!files.empty()) {
          files.pop();
        }
      } else {
        files.emplace(cache);
      }
    }
  }

  std::vector<std::string> res;
  while (!files.empty()) {
    res.emplace_back(files.top());
    files.pop();
  }
  if (res.empty()) {
    std::cout << '/';
  } else {
    std::reverse(res.begin(), res.end());
    for (int i = 0; i < res.size(); ++i) {
      std::cout << '/' << res[i];
    }
  }
  std::cout << '\n';
}