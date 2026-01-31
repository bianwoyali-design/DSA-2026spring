#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    static constexpr int inf = numeric_limits<int>::max() / 2;

public:
    long long minimumCost(string source, string target,
                          vector<char> &original, vector<char> &changed, vector<int> &cost)
    {
        int n = source.size();
        int m = cost.size();

        vector<vector<int>> g(26, vector<int>(26, inf));

        for (int i = 0; i < 26; ++i)
            g[i][i] = 0;

        for (int i = 0; i < m; ++i)
        {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            g[u][v] = min(g[u][v], cost[i]);
        }

        for (int k = 0; k < 26; ++k)
            for (int i = 0; i < 26; ++i)
                for (int j = 0; j < 26; ++j)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            if (g[u][v] == inf)
                return -1;
            ans += g[u][v];
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string source = "abcd", target = "acbe";
    vector<char> original = {'a', 'b', 'c', 'c', 'e', 'd'}, changed = {'b', 'c', 'b', 'e', 'b', 'e'};
    vector<int> cost = {2, 5, 5, 1, 2, 20};
    cout << sol.minimumCost(source, target, original, changed, cost) << '\n';
    return 0;
}