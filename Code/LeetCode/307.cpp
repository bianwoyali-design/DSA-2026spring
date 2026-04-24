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

  virtual auto update(size_t i, const Type &value) -> void = 0;
  virtual auto query(size_t l, size_t r) -> Type = 0;
  virtual ~SegmentTree() = default;
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

  auto update(size_t i, const Type &value) -> void override {
    _update(1, 0, this->n - 1, i, value);
  }

  auto query(size_t l, size_t r) -> Type override {
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

  auto update(size_t i, const Type &value) -> void override {
    i += this->n;
    this->tree[i] = value;

    while (i > 1) {
      this->tree[i >> 1] = this->func(this->tree[i], this->tree[i ^ 1]);
      i >>= 1;
    }
  }

  auto query(size_t l, size_t r) -> Type override {
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
