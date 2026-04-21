#include <iostream>
#include <utility>
#include <vector>

template <typename Type> class BinaryHeap {
private:
  std::vector<Type> heap;

  auto get_min_child(auto &&i) -> int {
    if (2 * i + 2 >= heap.size()) {
      return 2 * i + 1;
    }
    if (heap[2 * i + 1] < heap[2 * i + 2]) {
      return 2 * i + 1;
    }
    return 2 * i + 2;
  }

  auto perc_up(auto &&i) -> void {
    while (i > 0) {
      const int parent = (i - 1) / 2;
      if (heap[i] < heap[parent]) {
        std::swap(heap[i], heap[parent]);
      } else {
        break;
      }
      i = parent;
    }
  }

  auto perc_down(auto &&i) -> void {
    while (2 * i + 1 < heap.size()) {
      const int sm_child = get_min_child(i);
      if (heap[i] > heap[sm_child]) {
        std::swap(heap[i], heap[sm_child]);
      } else {
        break;
      }
      i = sm_child;
    }
  }

public:
  auto insert(auto &&item) -> void {
    heap.push_back(item);
    perc_up(static_cast<int>(heap.size() - 1));
  }

  auto pop_root() -> int {
    if (heap.empty()) {
      return 0;
    }

    std::swap(heap.front(), heap.back());
    const int result = heap.back();
    heap.pop_back();
    perc_down(0);
    return result;
  }

  auto heapify() -> std::vector<Type> {
    int i = (heap.size() >> 1) - 1;
    while (i >= 0) {
      perc_down(i);
      --i;
    }
    return heap;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  BinaryHeap<int> priority_queue;
  while (n--) {
    int ops, value;
    std::cin >> ops;
    switch (ops) {
    case 1:
      std::cin >> value;
      priority_queue.insert(value);
      continue;
    case 2:
      std::cout << priority_queue.pop_root() << '\n';
      continue;
    default:
      break;
    }
  }
}