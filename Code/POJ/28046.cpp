#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<std::string> words(n);
  std::unordered_map<std::string, std::vector<int>> bucket;
  for (int i = 0; i < n; ++i) {
    std::cin >> words[i];

    for (int j = 0; j < 4; ++j) {
      auto pattern = words[i];
      pattern[j] = '*';
      bucket[pattern].emplace_back(i);
    }
  }

  std::string start, end;
  std::cin >> start >> end;
  const int start_ptr =
                std::find(words.begin(), words.end(), start) - words.begin(),
            end_ptr =
                std::find(words.begin(), words.end(), end) - words.begin();

  std::queue<int> q;
  std::vector<bool> visited(n, false);
  std::vector<int> parent(n, -1);
  visited[start_ptr] = true;
  q.emplace(start_ptr);

  while (!q.empty()) {
    auto ptr = q.front();
    q.pop();

    if (ptr == end_ptr)
      break;

    for (int i = 0; i < 4; ++i) {
      auto pattern = words[ptr];
      pattern[i] = '*';

      auto ptrs = bucket[pattern];
      for (auto &&p : ptrs) {
        if (!visited[p]) {
          visited[p] = true;
          parent[p] = ptr;
          q.emplace(p);
        }
      }
    }
  }

  if (!visited[end_ptr]) {
    std::cout << "NO";
  } else {
    std::vector<std::string> path;
    for (int ptr = end_ptr; ptr != -1; ptr = parent[ptr]) {
      path.emplace_back(words[ptr]);
    }

    std::reverse(path.begin(), path.end());
    for (auto &&str : path) {
      std::cout << str << ' ';
    }
  }
}