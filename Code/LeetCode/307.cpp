#include <cstddef>
#include <iostream>
#include <vector>

class NumArray {
private:
  std::vector<int> tree;
  std::vector<int> &nums;

  auto lowBit(int x) -> int { return x & -x; }

  void add(int index, int val) {
    while (index < tree.size()) {
      tree[index] += val;
      index += lowBit(index);
    }
  }

  auto prefixSum(int index) -> int {
    int sum = 0;
    while (index > 0) {
      sum += tree[index];
      index -= lowBit(index);
    }
    return sum;
  }

public:
  NumArray(std::vector<int> &nums) : tree(nums.size() + 1), nums(nums) {
    for (int i = 0; i < nums.size(); i++)
      add(i + 1, nums[i]);
  }

  void update(int index, int val) {
    add(index + 1, val - nums[index]);
    nums[index] = val;
  }

  auto sumRange(int left, int right) -> int {
    return prefixSum(right + 1) - prefixSum(left);
  }
};

template <typename Type, typename Func> class SegmentTree {
protected:
  size_t n;
  Func func;
  Type default_val;
  std::vector<Type> tree;

public:
  explicit SegmentTree(const std::vector<Type> &data, Func func = Func{},
                       const Type &de = Type())
      : n(data.size()), func(func), default_val(de) {}

  ~SegmentTree() = default;
};

template <typename Type, typename Func>
class RecursiveSegmentTree : public SegmentTree<Type, Func> {
private:
  auto _build(const std::vector<Type> &data, size_t node, size_t start,
              size_t end) -> void {
    if (start == end) {
      this->tree[node] = data[start];
      return;
    }

    auto mid = start + ((end - start) >> 1);
    auto left = node << 1;
    auto right = node << 1 | 1;

    _build(data, left, start, mid);
    _build(data, right, mid + 1, end);

    this->tree[node] = this->func(this->tree[left], this->tree[right]);
  }

  auto _update(size_t node, size_t start, size_t end, size_t i,
               const Type &value) -> void {
    if (start == end) {
      this->tree[node] = value;
      return;
    }

    auto mid = start + ((end - start) >> 1);

    if (i <= mid) {
      _update(node << 1, start, mid, i, value);
    } else {
      _update(node << 1 | 1, mid + 1, end, i, value);
    }

    this->tree[node] =
        this->func(this->tree[node << 1], this->tree[node << 1 | 1]);
  }

  auto _query(size_t node, size_t start, size_t end, size_t l, size_t r)
      -> Type {
    if (l <= start && end <= r) {
      return this->tree[node];
    }
    auto mid = start + ((end - start) >> 1);
    if (r <= mid)
      return _query(node << 1, start, mid, l, r);
    if (l > mid)
      return _query(node << 1 | 1, mid + 1, end, l, r);

    return this->func(_query(node << 1, start, mid, l, r),
                      _query(node << 1 | 1, mid + 1, end, l, r));
  }

public:
  explicit RecursiveSegmentTree(const std::vector<Type> &data,
                                Func func = Func{}, const Type &de = Type())
      : SegmentTree<Type, Func>(data, func, de) {
    this->tree.assign(4 * this->n, this->default_val);
    _build(data, 1, 0, this->n - 1);
  }

  auto update(size_t i, const Type &value) -> void {
    _update(1, 0, this->n - 1, i, value);
  }

  auto query(size_t l, size_t r) -> Type {
    return _query(1, 0, this->n - 1, l, r);
  }
};

template <typename Type, typename Func>
class ZWKSegmentTree : public SegmentTree<Type, Func> {
public:
  explicit ZWKSegmentTree(const std::vector<Type> &data, Func func = Func{},
                          const Type &de = Type())
      : SegmentTree<Type, Func>(data, func, de) {
    this->tree.assign(2 * this->n, this->default_val);
    for (int i = 0; i < this->n; ++i) {
      this->tree[i + this->n] = data[i];
    }
    for (int i = this->n - 1; i > 0; --i) {
      this->tree[i] = this->func(this->tree[i << 1], this->tree[i << 1 | 1]);
    }
  }

  auto update(size_t i, const Type &value) -> void {
    i += this->n;
    this->tree[i] = value;

    while (i > 1) {
      this->tree[i >> 1] = this->func(this->tree[i], this->tree[i ^ 1]);
      i >>= 1;
    }
  }

  auto query(size_t l, size_t r) -> Type {
    Type res = this->default_val;
    l += this->n;
    r += this->n;

    while (l < r) {
      if (l & 1) {
        res = this->func(res, this->tree[l++]);
      }
      if (r & 1) {
        res = this->func(res, this->tree[--r]);
      }
      l >>= 1;
      r >>= 1;
    }
    return res;
  }
};

template <typename Type, typename Func> class LazySegTree {
private:
  size_t n;
  Type default_val;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _perc_down(size_t node, size_t start, size_t end) -> void {
    if (start == end || !has_lazy[node]) {
      return;
    }

    if (has_lazy[node]) {
      const auto mid = start + ((end - start) >> 1);
      const auto left = node << 1;
      const auto right = node << 1 | 1;

      lazy[left] = lazy[node];
      has_lazy[left] = true;
      tree[left] = lazy[node] * (mid + 1 - start);

      lazy[right] = lazy[node];
      has_lazy[right] = true;
      tree[right] = lazy[node] * (end - mid);

      lazy[node] = 0;
      has_lazy[node] = false;
    }
  }

  auto _build(const std::vector<Type> &data, size_t node, size_t start,
              size_t end) -> void {
    if (start == end) {
      tree[node] = data[start];
      return;
    }

    const auto mid = start + ((end - start) >> 1);
    _build(data, node << 1, start, mid);
    _build(data, node << 1 | 1, mid + 1, end);

    tree[node] = func(tree[node << 1], tree[node << 1 | 1]);
  }

  auto _update_range(size_t node, size_t start, size_t end, size_t l, size_t r,
                     Type value) -> void {
    if (l <= start && end <= r) {
      lazy[node] = value;
      has_lazy[node] = true;
      tree[node] = (end - start + 1) * value;
      return;
    }

    _perc_down(node, start, end);

    const auto mid = start + ((end - start) >> 1);
    if (l <= mid) {
      _update_range(node << 1, start, mid, l, r, value);
    }
    if (r > mid) {
      _update_range(node << 1 | 1, mid + 1, end, l, r, value);
    }

    tree[node] = func(tree[node << 1], tree[node << 1 | 1]);
  }

  auto _query_range(size_t node, size_t start, size_t end, size_t l, size_t r)
      -> Type {
    if (l <= start && end <= r) {
      return tree[node];
    }

    _perc_down(node, start, end);
    const auto mid = start + ((end - start) >> 1);
    if (r <= mid) {
      return _query_range(node << 1, start, mid, l, r);
    }
    if (l > mid) {
      return _query_range(node << 1 | 1, mid + 1, end, l, r);
    }

    return func(_query_range(node << 1, start, mid, l, r),
                _query_range(node << 1 | 1, mid + 1, end, l, r));
  }

public:
  explicit LazySegTree(const std::vector<Type> &data, Func func = Func{},
                       const Type &de = Type())
      : n(data.size()), default_val(de), func(func) {
    tree.assign(4 * n, default_val);
    lazy.assign(4 * n, default_val);
    has_lazy.assign(4 * n, false);
    if (n > 0) {
      _build(data, 1, 0, n - 1);
    }
  }

  auto update_range(size_t l, size_t r, Type value) -> void {
    if (n == 0 || l > r) {
      return;
    }
    _update_range(1, 0, n - 1, l, r, value);
  }

  auto query_range(size_t l, size_t r) -> Type {
    if (n == 0 || l > r) {
      return default_val;
    }
    return _query_range(1, 0, n - 1, l, r);
  }
};

template <typename Type, typename Func> class ZWKLazySegmentTree {
private:
  size_t size;
  size_t base;
  size_t height;
  Type default_val;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _apply(size_t p, const Type &value, size_t len) -> void {
    tree[p] = value * static_cast<Type>(len);
    if (p < base) {
      lazy[p] = value;
      has_lazy[p] = true;
    }
  }

  auto _push(size_t p) -> void {
    for (size_t s = height; s > 0; --s) {
      const size_t i = p >> s;
      if (!has_lazy[i]) {
        continue;
      }

      const size_t len = static_cast<size_t>(1) << (s - 1);
      _apply(i << 1, lazy[i], len);
      _apply(i << 1 | 1, lazy[i], len);
      has_lazy[i] = false;
    }
  }

  auto _pull(size_t p) -> void {
    size_t len = 2;
    for (p >>= 1; p > 0; p >>= 1, len <<= 1) {
      if (has_lazy[p]) {
        tree[p] = lazy[p] * static_cast<Type>(len);
      } else {
        tree[p] = func(tree[p << 1], tree[p << 1 | 1]);
      }
    }
  }

public:
  explicit ZWKLazySegmentTree(const std::vector<Type> &data,
                                  Func f = Func{}, const Type &de = Type())
      : size(data.size()), default_val(de), func(f) {
    base = 1;
    height = 0;
    while (base < size) {
      base <<= 1;
      ++height;
    }

    tree.assign(base << 1, default_val);
    lazy.assign(base << 1, default_val);
    has_lazy.assign(base << 1, false);

    for (size_t i = 0; i < size; ++i) {
      tree[base + i] = data[i];
    }
    for (size_t i = base - 1; i > 0; --i) {
      tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  auto update_range(size_t l, size_t r, const Type &value) -> void {
    if (size == 0 || l > r || r >= size) {
      return;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    const size_t left_origin = left;
    const size_t right_origin = right;

    _push(left_origin);
    _push(right_origin - 1);

    size_t len = 1;
    while (left < right) {
      if (left & 1) {
        _apply(left++, value, len);
      }
      if (right & 1) {
        _apply(--right, value, len);
      }
      left >>= 1;
      right >>= 1;
      len <<= 1;
    }

    _pull(left_origin);
    _pull(right_origin - 1);
  }

  auto query_range(size_t l, size_t r) -> Type {
    if (size == 0 || l > r || r >= size) {
      return default_val;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    _push(left);
    _push(right - 1);

    Type left_res = default_val;
    Type right_res = default_val;
    while (left < right) {
      if (left & 1) {
        left_res = func(left_res, tree[left++]);
      }
      if (right & 1) {
        right_res = func(tree[--right], right_res);
      }
      left >>= 1;
      right >>= 1;
    }

    return func(left_res, right_res);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> nums = {1, 3, 5};
  RecursiveSegmentTree sg(nums, [](int a, int b) -> int { return a + b; }, 0);
  int left = 0, right = 2;
  int index = 1, val = 2;
  int param_1 = sg.query(left, right);
  sg.update(index, val);
  int param_2 = sg.query(left, right);
  std::cout << param_1 << ' ' << param_2 << '\n';
  return 0;
}