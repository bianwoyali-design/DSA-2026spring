#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache
{
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key)
    {
        if (mp.contains(key))
        {
            auto it = mp[key];
            cache.splice(cache.begin(), cache, it);
            return it->second;
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (mp.contains(key))
        {
            auto it = mp[key];
            cache.splice(cache.begin(), cache, it);
            it->second = value;
        }
        else
        {
            if (cache.size() == capacity)
            {
                auto it = prev(cache.end());
                mp.erase(it->first);
                cache.pop_back();
            }
            mp[key] = cache.emplace(cache.begin(), key, value);
        }
    }

private:
    const int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> mp;
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    LRUCache *lRUCache = new LRUCache(2);
    lRUCache->put(1, 1);              // 缓存是 {1=1}
    lRUCache->put(2, 2);              // 缓存是 {1=1, 2=2}
    cout << lRUCache->get(1) << '\n'; // 返回 1
    lRUCache->put(3, 3);              // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << lRUCache->get(2) << '\n'; // 返回 -1 (未找到)
    lRUCache->put(4, 4);              // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << lRUCache->get(1) << '\n'; // 返回 -1 (未找到)
    cout << lRUCache->get(3) << '\n'; // 返回 3
    cout << lRUCache->get(4) << '\n'; // 返回 4
    return 0;
}