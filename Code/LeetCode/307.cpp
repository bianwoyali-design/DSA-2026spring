#include <iostream>
#include <vector>
using namespace std;

class NumArray
{
private:
    vector<int> tree;
    vector<int> &nums;

    int lowBit(int x)
    {
        return x & -x;
    }

    void add(int index, int val)
    {
        while (index < tree.size())
        {
            tree[index] += val;
            index += lowBit(index);
        }
    }

    int prefixSum(int index)
    {
        int sum = 0;
        while (index > 0)
        {
            sum += tree[index];
            index -= lowBit(index);
        }
        return sum;
    }

public:
    NumArray(vector<int> &nums) : tree(nums.size() + 1), nums(nums)
    {
        for (int i = 0; i < nums.size(); i++)
            add(i + 1, nums[i]);
    }

    void update(int index, int val)
    {
        add(index + 1, val - nums[index]);
        nums[index] = val;
    }

    int sumRange(int left, int right)
    {
        return prefixSum(right + 1) - prefixSum(left);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<int> nums = {1, 3, 5};
    int left = 0, right = 2;
    int index = 1, val = 2;
    NumArray *obj = new NumArray(nums);
    int param_1 = obj->sumRange(left, right);
    obj->update(index, val);
    int param_2 = obj->sumRange(left, right);
    cout << param_1 << ' ' << param_2 << '\n';
    return 0;
}
