#include <iterator>
#include <list>
#include <print>
#include <unordered_map>
#include <utility>

class LRUCache {
public:
  explicit LRUCache(int capacity) : capacity(capacity) {}

  auto get(int key) -> int {
    auto it = hash.find(key);
    if (it == hash.end())
      return -1;
    cache.splice(cache.begin(), cache, it->second);
    return it->second->second;
  }

  void put(int key, int value) {
    auto it = hash.find(key);
    if (it != hash.end()) {
      it->second->second = value;
      cache.splice(cache.begin(), cache, it->second);
    } else {
      if (cache.size() == capacity) {
        auto del = std::prev(cache.end());
        hash.erase(del->first);
        cache.pop_back();
      }
      hash[key] = cache.emplace(cache.begin(), key, value);
    }
  }

private:
  int capacity;
  std::list<std::pair<int, int>> cache;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> hash;
};

auto main() -> int {
  auto *lRUCache = new LRUCache(2);
  lRUCache->put(1, 1);                  // 缓存是 {1=1}
  lRUCache->put(2, 2);                  // 缓存是 {1=1, 2=2}
  std::println("{}", lRUCache->get(1)); // 返回 1
  lRUCache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  std::println("{}", lRUCache->get(2)); // 返回 -1 (未找到)
  lRUCache->put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  std::println("{}", lRUCache->get(1)); // 返回 -1 (未找到)
  std::println("{}", lRUCache->get(3)); // 返回 3
  std::println("{}", lRUCache->get(4)); // 返回 4
}
