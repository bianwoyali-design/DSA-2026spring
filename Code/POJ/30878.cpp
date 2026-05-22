#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template <typename Type, typename Func> class SegTree {
private:
  size_t size;
  size_t base;
  size_t height;
  Type query_default;
  Type lazy_default;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _apply(size_t p, const Type &value) -> void {
    tree[p] += value;
    if (p < base) {
      lazy[p] += value;
      has_lazy[p] = true;
    }
  }

  auto _push(size_t p) -> void {
    for (size_t s = height; s > 0; --s) {
      const size_t i = p >> s;
      if (!has_lazy[i]) {
        continue;
      }

      _apply(i << 1, lazy[i]);
      _apply(i << 1 | 1, lazy[i]);
      lazy[i] = lazy_default;
      has_lazy[i] = false;
    }
  }

  auto _pull(size_t p) -> void {
    for (p >>= 1; p > 0; p >>= 1) {
      tree[p] = func(tree[p << 1], tree[p << 1 | 1]);
      if (has_lazy[p]) {
        tree[p] += lazy[p];
      }
    }
  }

public:
  explicit SegTree(const std::vector<Type> &data, Func f = Func{},
                   const Type &query_de = Type(), const Type &lazy_de = Type())
      : size(data.size()), query_default(query_de), lazy_default(lazy_de),
        func(f) {
    base = 1;
    height = 0;
    while (base < size) {
      base <<= 1;
      ++height;
    }

    tree.assign(base << 1, query_default);
    lazy.assign(base << 1, lazy_default);
    has_lazy.assign(base << 1, false);

    for (size_t i = 0; i < size; ++i) {
      tree[base + i] = data[i];
    }
    for (size_t i = base - 1; i > 0; --i) {
      tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  auto add_range(size_t l, size_t r, const Type &value) -> void {
    if (size == 0 || l > r || r >= size) {
      return;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    const size_t left_origin = left;
    const size_t right_origin = right;

    _push(left_origin);
    _push(right_origin - 1);

    while (left < right) {
      if (left & 1) {
        _apply(left++, value);
      }
      if (right & 1) {
        _apply(--right, value);
      }
      left >>= 1;
      right >>= 1;
    }

    _pull(left_origin);
    _pull(right_origin - 1);
  }

  auto query_range(size_t l, size_t r) -> Type {
    if (size == 0 || l > r || r >= size) {
      return query_default;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    _push(left);
    _push(right - 1);

    auto left_res = query_default;
    auto right_res = query_default;
    while (left < right) {
      if (left & 1) {
        left_res = func(left_res, tree[left++]);
      }
      if (right & 1) {
        right_res = func(right_res, tree[--right]);
      }
      left >>= 1;
      right >>= 1;
    }

    return func(left_res, right_res);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, Q;
  std::cin >> N >> Q;

  std::vector<long long> data(N, 0);

  auto max_value = [](long long a, long long b) -> long long {
    return std::max(a, b);
  };

  SegTree segtree(data, max_value, std::numeric_limits<long long>::lowest(),
                  0LL);

  while (Q--) {
    std::string operation;
    int l, r;
    std::cin >> operation;

    if (operation == "Add") {
      long long v;
      std::cin >> l >> r >> v;
      segtree.add_range(l - 1, r - 1, v);
    }
    if (operation == "Query") {
      std::cin >> l >> r;
      std::cout << segtree.query_range(l - 1, r - 1) << '\n';
    }
  }
}
