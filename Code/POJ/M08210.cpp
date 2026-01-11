#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int L, N, M;
    cin >> L >> N >> M;
    vector<int> dist(N + 2);
    dist[0] = 0, dist[N + 1] = L;
    for (int i = 1; i <= N; ++i)
        cin >> dist[i];

    int l = 1, r = L; // 最小距离为1，最大距离为总长
    int mid, ans;
    while (l < r)
    {
        mid = l + (r - l) / 2;
        int curr = dist[0];
        int cnt = 0;
        for (int i = 1; i <= N + 1; ++i)
            if (dist[i] - curr < mid) // 距离比所假定的距离短，要移除
            {
                cnt++;
                if (cnt > M)
                    break;
            }
            else
                curr = dist[i];
        if (cnt <= M) // 最小值最大化
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid;
    }

    cout << ans << '\n';
    return 0;
}
