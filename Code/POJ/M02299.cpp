#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fenwick
{
    int n;
    vector<int> tree;
    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    void update(int i)
    {
        for (; i <= n; i += i & -i)
            ++tree[i];
    }

    int query(int i)
    {
        int sum = 0;
        for (; i > 0; i &= i - 1)
            sum += tree[i];
        return sum;
    }
};

void solve()
{
    int n;
    while (cin >> n && n != 0)
    {
        vector<int> a(n);
        vector<int> vals(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            vals[i] = a[i];
        }

        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        Fenwick bit(vals.size());
        long long inversion = 0;

        for (int i = n - 1; i >= 0; --i)
        {
            int rank = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
            inversion += bit.query(rank - 1);
            bit.update(rank);
        }

        cout << inversion << '\n';
    }
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}