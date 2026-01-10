#include <iostream>
#include <climits>
#include <stack>
using namespace std;

class MinStack
{
private:
    stack<int> st;
    stack<int> min_st;
public:
    MinStack()
    {
        min_st.push(INT_MAX);
    }

    void push(int val)
    {
        st.push(val);
        min_st.push(min(min_st.top(), val));
    }

    void pop()
    {
        st.pop();
        min_st.pop();
    }

    int top()
    {
        return st.top();
    }

    int getMin()
    {
        return min_st.top();
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << '\n';
    minStack.pop();
    cout << minStack.top() << '\n';
    cout << minStack.getMin() << '\n';
    return 0;
}