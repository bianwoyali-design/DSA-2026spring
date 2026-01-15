#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

enum OP
{
    FILL1,
    FILL2,
    DROP1,
    DROP2,
    POUR12,
    POUR21,
    NONE
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;
    queue<pair<int, int>> q;
    map<pair<int, int>, bool> inqueue;
    map<pair<int, int>, pair<pair<int, int>, OP>> path;
    q.push({0, 0});
    inqueue[{0, 0}] = true;
    path[{0, 0}] = {{-1, -1}, NONE};

    int found = -1;
    pair<int, int> endst;
    int steps = 0;
    while (!q.empty() && found == -1)
    {
        int sz = q.size();
        while (sz--)
        {
            auto [v1, v2] = q.front();
            q.pop();
            if (v1 == c || v2 == c)
            {
                found = steps;
                endst = {v1, v2};
                break;
            }
            // FILL(1)
            if (!inqueue[{a, v2}])
            {
                q.push({a, v2});
                inqueue[{a, v2}] = true;
                path[{a, v2}] = {{v1, v2}, FILL1};
            }
            // FILL(2)
            if (!inqueue[{v1, b}])
            {
                q.push({v1, b});
                inqueue[{v1, b}] = true;
                path[{v1, b}] = {{v1, v2}, FILL2};
            }
            // DROP(1)
            if (!inqueue[{0, v2}])
            {
                q.push({0, v2});
                inqueue[{0, v2}] = true;
                path[{0, v2}] = {{v1, v2}, DROP1};
            }
            // DROP(2)
            if (!inqueue[{v1, 0}])
            {
                q.push({v1, 0});
                inqueue[{v1, 0}] = true;
                path[{v1, 0}] = {{v1, v2}, DROP2};
            }
            // POUR(1,2)
            int pour12 = min(v1, b - v2);
            if (!inqueue[{v1 - pour12, v2 + pour12}])
            {
                q.push({v1 - pour12, v2 + pour12});
                inqueue[{v1 - pour12, v2 + pour12}] = true;
                path[{v1 - pour12, v2 + pour12}] = {{v1, v2}, POUR12};
            }
            // POUR(2,1)
            int pour21 = min(v2, a - v1);
            if (!inqueue[{v1 + pour21, v2 - pour21}])
            {
                q.push({v1 + pour21, v2 - pour21});
                inqueue[{v1 + pour21, v2 - pour21}] = true;
                path[{v1 + pour21, v2 - pour21}] = {{v1, v2}, POUR21};
            }
        }
        steps++;
    }

    if (found == -1)
    {
        cout << "impossible\n";
        return 0;
    }
    cout << found << '\n';
    // 回溯操作
    vector<OP> ops;
    pair<int, int> cur = endst;
    while (path[cur].second != NONE)
    {
        ops.push_back(path[cur].second);
        cur = path[cur].first;
    }
    reverse(ops.begin(), ops.end());
    for (auto op : ops)
    {
        if (op == FILL1)
            cout << "FILL(1)\n";
        else if (op == FILL2)
            cout << "FILL(2)\n";
        else if (op == DROP1)
            cout << "DROP(1)\n";
        else if (op == DROP2)
            cout << "DROP(2)\n";
        else if (op == POUR12)
            cout << "POUR(1,2)\n";
        else if (op == POUR21)
            cout << "POUR(2,1)\n";
    }
    return 0;
}