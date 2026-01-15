#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int minPrice = 1e9, profit = 0;
        for (const auto &p : prices)
        {
            minPrice = min(minPrice, p);
            profit = max(profit, p - minPrice);
        }
        return profit;
    }
};

int main()
{
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    Solution sol;
    cout << sol.maxProfit(prices) << '\n';
    return 0;
}