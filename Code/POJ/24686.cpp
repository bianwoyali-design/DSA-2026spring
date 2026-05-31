#include <iostream>
#include <vector>

class SegTree {
private:
  int n;
  std::vector<int> tree;
  std::vector<int> lazy;

  auto _perc_down(int node, int start, int end) -> void {
    if (!lazy[node] || start == end) {
      return;
    }

    const int left = node << 1;
    const int right = node << 1 | 1;
    const int mid = start + ((end - start) >> 1);
    const int value = lazy[node];

    lazy[left] += value;
    tree[left] += value * (mid - start + 1);

    lazy[right] += value;
    tree[right] += value * (end - mid);

    lazy[node] = 0;
  }

  auto _update_range(int node, int start, int end, int l, int r, int value)
      -> void {
    if (l <= start && end <= r) {
      lazy[node] += value;
      tree[node] += value * (end - start + 1);
      return;
    }

    _perc_down(node, start, end);

    const int mid = start + ((end - start) >> 1);
    if (l <= mid) {
      _update_range(node << 1, start, mid, l, r, value);
    }
    if (r > mid) {
      _update_range(node << 1 | 1, mid + 1, end, l, r, value);
    }

    tree[node] = tree[node << 1] + tree[node << 1 | 1];
  }

  auto _query_range(int node, int start, int end, int l, int r) -> int {
    if (l <= start && end <= r) {
      return tree[node];
    }

    _perc_down(node, start, end);
    const int mid = start + ((end - start) >> 1);
    if (r <= mid) {
      return _query_range(node << 1, start, mid, l, r);
    }
    if (l > mid) {
      return _query_range(node << 1 | 1, mid + 1, end, l, r);
    }

    return _query_range(node << 1, start, mid, l, r) +
           _query_range(node << 1 | 1, mid + 1, end, l, r);
  }

public:
  explicit SegTree(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

  auto update_range(int l, int r, int value) -> void {
    _update_range(1, 0, n - 1, l, r, value);
  }

  auto query_range(int l, int r) -> int {
    return _query_range(1, 0, n - 1, l, r);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int k, n;
  std::cin >> k >> n;
  SegTree segtree(1 << k);

  for (int i = 0; i < n; ++i) {
    int ops;
    std::cin >> ops;
    if (ops == 1) {
      int root, value;
      std::cin >> root >> value;

      int depth = 32 - __builtin_clz(root);
      for (int level = depth; level <= k; ++level) {
        int len = 1 << (level - depth);
        int left = root * len;
        int right = (root + 1) * len - 1;
        segtree.update_range(left, right, value);
      }
    } else {
      int root;
      int sum = 0;
      std::cin >> root;

      int depth = 32 - __builtin_clz(root);
      for (int level = depth; level <= k; ++level) {
        int len = 1 << (level - depth);
        int left = root * len;
        int right = (root + 1) * len - 1;
        sum += segtree.query_range(left, right);
      }

      std::cout << sum << '\n';
    }
  }
}