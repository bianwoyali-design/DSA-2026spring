#include <iostream>
#include <vector>
using namespace std;

class Fenwick
{
private:
    int n;
    vector<int> tree;

public:
    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    void update(int i)
    {
        while (i <= n)
        {
            ++tree[i];
            i = i + (i & -i);
        }
    }

    int query(int i)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += tree[i];
            i &= i - 1;
        }
        return sum;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    int sz = n * n;
    vector<int> matrix;
    int bottom_up;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            int x;
            cin >> x;
            if (x == 0)
                bottom_up = n - i;
            else
                matrix.push_back(x);
        }

    Fenwick bit(sz);
    long long cnt = 0;

    for (int i = matrix.size() - 1; i >= 0; --i)
    {
        cnt += bit.query(matrix[i] - 1);
        bit.update(matrix[i]);
    }

    bool flag = false;
    if (n % 2 != 0)
    {
        if (cnt % 2 == 0)
            flag = true;
    }
    else
    {
        if ((cnt + bottom_up) % 2 == 1)
            flag = true;
    }

    cout << (flag == true ? "yes\n" : "no\n");
    return 0;
}