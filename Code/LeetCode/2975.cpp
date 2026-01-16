#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
private:
    unordered_set<int> getEdge(vector<int> &fences, int end)
    {
        unordered_set<int> edge;
        fences.push_back(end);
        fences.push_back(1);
        ranges::sort(fences);
        for (int i = 0; i < fences.size() - 1; ++i)
            for (int j = i + 1; j < fences.size(); ++j)
                edge.insert(fences[j] - fences[i]);
        return edge;
    }

public:
    int maximizeSquareArea(int m, int n, vector<int> &hFences, vector<int> &vFences)
    {
        auto hEdge = getEdge(hFences, m);
        auto vEdge = getEdge(vFences, n);

        int res = 0;
        for (const auto &e : hEdge)
            if (vEdge.contains(e))
                res = max(res, e);

        if (res == 0)
            return -1;
        else
            return 1ll * (res % 1000000007) * (res % 1000000007) % 1000000007;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<int> hFences = {2, 3}, vFences = {2};
    int m = 4, n = 3;
    Solution sol;
    cout << sol.maximizeSquareArea(m, n, vFences, hFences) << '\n';
    return 0;
}