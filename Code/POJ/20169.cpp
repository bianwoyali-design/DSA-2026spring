#include <iostream>
#include <vector>
using namespace std;

class Disjoint
{
    vector<int> pa;

public:
    Disjoint(int n) : pa(n + 1)
    {
        for (int i = 1; i <= n; ++i)
            pa[i] = i;
    }

    int find(int x)
    {
        return pa[x] == x ? x : pa[x] = find(pa[x]);
    }

    void unite(int i, int j)
    {
        int irep = find(i);
        int jrep = find(j);
        if (irep == jrep)
            return;
        pa[irep] = jrep;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        Disjoint dsu(n);
        while (m--)
        {
            int i, j;
            cin >> i >> j;
            dsu.unite(i, j);
        }

        for (int i = 1; i <= n; ++i)
            cout << dsu.find(i) << ' ';
        cout << '\n';
    }

    return 0;
}