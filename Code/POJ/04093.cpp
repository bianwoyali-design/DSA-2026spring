#include <bitset>
#include <iostream>
#include <vector>

class InvertedIndex {
  int n;
  constexpr static int MAXN = 10001;
  std::vector<std::bitset<MAXN>> files;

public:
  InvertedIndex(const InvertedIndex &) = default;
  InvertedIndex(InvertedIndex &&) = default;
  auto operator=(const InvertedIndex &) -> InvertedIndex & = default;
  auto operator=(InvertedIndex &&) -> InvertedIndex & = default;
  explicit InvertedIndex(int n) : n(n), files(n) {}

  auto init() -> void;

  auto search() -> void;
};

auto InvertedIndex::init() -> void {
  for (int i = 0; i < n; ++i) {
    int c;
    std::cin >> c;
    while (c--) {
      int id;
      std::cin >> id;
      files[i].set(id);
    }
  }
}

auto InvertedIndex::search() -> void {
  std::vector<int> query(n);

  int first = -1;
  for (int i = 0; i < n; ++i) {
    std::cin >> query[i];
    if (first == -1 && query[i] == 1)
      first = i;
  }

  std::bitset<MAXN> a;
  if (first != -1) {
    a = files[first];
    for (int i = first + 1; i < n; ++i)
      if (query[i] == 1)
        a &= files[i];
  }

  std::bitset<MAXN> b;
  for (int i = 0; i < n; ++i)
    if (query[i] == -1)
      b |= files[i];

  std::bitset<MAXN> c = a & (~b);

  if (c.none())
    std::cout << "NOT FOUND\n";
  else {
    for (int i = 0; i < MAXN; ++i) {
      if (c[i])
        std::cout << i << ' ';
    }
    std::cout << '\n';
  }
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  InvertedIndex II(n);

  II.init();
  
  int m;
  std::cin >> m;
  while (m--)
    II.search();
}