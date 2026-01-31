#include <iostream>
#include <vector>
using namespace std;

class Trie
{
public:
    Trie *children[26];
    int id;

    Trie() : id(-1)
    {
        for (auto &c : children)
            c = nullptr;
    }

    auto add(const string &word, int &index)
    {
        Trie *node = this;
        for (const auto &ch : word)
        {
            int i = ch - 'a';
            if (node->children[i] == nullptr)
                node->children[i] = new Trie();
            node = node->children[i];
        }
        if (node->id == -1)
            node->id = ++index;
        return node->id;
    }
};

class Solution
{
public:
    long long minimumCost(string source, string target,
                          vector<string> &original, vector<string> &changed, vector<int> &cost)
    {
        int n = source.size();
        int m = original.size();
        Trie *root = new Trie();

        int p = -1;
        vector<vector<int>> g(m * 2, vector<int>(m * 2, inf));
        for (int i = 0; i < m * 2; ++i)
            g[i][i] = 0;

        for (int i = 0; i < m; ++i)
        {
            int u = root->add(original[i], p);
            int v = root->add(changed[i], p);
            g[u][v] = min(g[u][v], cost[i]);
        }

        for (int k = 0; k <= p; ++k)
            for (int i = 0; i <= p; ++i)
            {
                if (g[i][k] == inf)
                    continue;
                for (int j = 0; j <= p; ++j)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }

        vector<long long> dp(n, -1);
        for (int j = 0; j < n; ++j)
        {
            if (j > 0 && dp[j - 1] == -1)
                continue;
            long long base = (j == 0 ? 0 : dp[j - 1]);
            if (source[j] == target[j])
                dp[j] = (dp[j] == -1 ? base : min(dp[j], base));

            Trie *u = root;
            Trie *v = root;
            for (int i = j; i < n; ++i)
            {
                u = u->children[source[i] - 'a'];
                v = v->children[target[i] - 'a'];
                if (!u || !v)
                    break;
                if (u->id != -1 && v->id != -1 && g[u->id][v->id] != inf)
                    dp[i] = (dp[i] == -1 ? base + g[u->id][v->id] : min(dp[i], base + g[u->id][v->id]));
            }
        }

        return dp.back();
    }

private:
    static constexpr int inf = numeric_limits<int>::max() / 2;
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string source = "abcdefgh", target = "acdeeghh";
    vector<string> original = {"bcd", "fgh", "thh"}, changed = {"cde", "thh", "ghh"};
    vector<int> cost = {1, 3, 5};
    cout << sol.minimumCost(source, target, original, changed, cost) << '\n';
    return 0;
}