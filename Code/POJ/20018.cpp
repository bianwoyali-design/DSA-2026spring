#include <iostream>
#include <vector>
#include <algorithm>
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
            i += (i & -i);
        }
    }

    long long query(int i)
    {
        long long s = 0;
        while (i > 0)
        {
            s += tree[i];
            i &= i - 1;
        }
        return s;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> v(N), vals(N);
    for (int i = 0; i < N; ++i)
    {
        int ipt;
        cin >> ipt;
        v[i] = ipt, vals[i] = ipt;
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    Fenwick BIT(N);

    long long ans = 0;
    for (const auto &x : vals)
    {
        int r = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        ans += BIT.query(r - 1);
        BIT.update(r);
    }

    cout << ans << '\n';
    return 0;
}