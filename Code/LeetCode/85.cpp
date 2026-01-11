#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int n = matrix[0].size();
        int ans = 0;
        vector<int> height(n + 1, 0);

        for (const auto &submat : matrix)
        {
            for (int i = 0; i < n; ++i)
                if (submat[i] == '1')
                    ++height[i];
                else
                    height[i] = 0;

            stack<int> st;
            st.push(-1);
            for (int i = 0; i <= n; ++i)
            {
                while (st.top() != -1 && height[st.top()] > height[i])
                {
                    int top = st.top();
                    st.pop();
                    ans = max(ans, height[top] * (i - st.top() - 1));
                }
                st.push(i);
            }
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    Solution sol;
    cout << sol.maximalRectangle(matrix) << '\n';
    return 0;
}