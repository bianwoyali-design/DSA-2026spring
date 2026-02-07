#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class MedianFinder
{
public:
    MedianFinder() : sz_low(0), sz_up(0) {}

    void add(int x)
    {
        fifo_q.push(x);
        if (low.empty() || x <= low.top())
        {
            low.push(x);
            sz_low++;
        }
        else
        {
            up.push(x);
            sz_up++;
        }
        balance();
    }

    void del()
    {
        if (fifo_q.empty())
            return;
        int x = fifo_q.front();
        fifo_q.pop();

        delayed[x]++;
        // 判断 x 在哪个堆的逻辑范围内
        if (!low.empty() && x <= low.top())
            sz_low--;
        else
            sz_up--;

        // 逻辑删除后，堆顶可能是无效的，由于后面 balance 会调用 clean，此处可省略
        balance();
    }

    double query()
    {
        clean(low);
        clean(up);
        if ((sz_low + sz_up) % 2 == 1)
            return low.top();
        else
            // 必须除以 2.0 保证浮点运算
            return (low.top() + (double)up.top()) / 2.0;
    }

private:
    priority_queue<int> low;                           // 大根堆，维护左半部分
    priority_queue<int, vector<int>, greater<int>> up; // 小根堆，维护右半部分
    unordered_map<int, int> delayed;                   // 记录待删除元素的频率
    queue<int> fifo_q;                                 // 维护 add 的先后顺序以支持 del
    int sz_low, sz_up;                                 // 逻辑大小

    // 辅助函数：弹出堆顶所有已标记删除的无效元素
    template <typename T>
    void clean(T &heap)
    {
        while (!heap.empty() && delayed[heap.top()] > 0)
        {
            delayed[heap.top()]--;
            heap.pop();
        }
    }

    void balance()
    {
        // 保持 sz_low == sz_up 或 sz_low == sz_up + 1
        if (sz_low > sz_up + 1)
        {
            clean(low); // 转移前确保堆顶有效
            up.push(low.top());
            low.pop();
            sz_low--;
            sz_up++;
        }
        else if (sz_up > sz_low)
        {
            clean(up);
            low.push(up.top());
            up.pop();
            sz_up--;
            sz_low++;
        }
        // 再次清理确保后续操作安全
        clean(low);
        clean(up);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    MedianFinder mf;
    while (n--)
    {
        string op;
        cin >> op;
        if (op == "add")
        {
            int x;
            cin >> x;
            mf.add(x);
        }
        else if (op == "del")
            mf.del();
        else if (op == "query")
            cout << mf.query() << "\n";
    }

    return 0;
}