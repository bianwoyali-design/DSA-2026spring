#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    string url;
    Node *prev;
    Node *next;

    Node(string init) : url(init), prev(nullptr), next(nullptr) {}
};

class BrowserHistory
{
private:
    Node *current;

public:
    BrowserHistory(string homepage)
    {
        Node *newNode = new Node(homepage);
        current = newNode;
    }

    void visit(string url)
    {
        Node *newNode = new Node(url);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }

    string back(int steps)
    {
        while (steps && current->prev)
        {
            current = current->prev;
            --steps;
        }
        return current->url;
    }

    string forward(int steps)
    {
        while (steps && current->next)
        {
            current = current->next;
            --steps;
        }
        return current->url;
    }
};

int main()
{
    BrowserHistory *browserHistory = new BrowserHistory("leetcode.com");

    browserHistory->visit("google.com");
    browserHistory->visit("facebook.com");
    browserHistory->visit("youtube.com");

    std::cout << browserHistory->back(1) << std::endl;    // facebook.com
    std::cout << browserHistory->back(1) << std::endl;    // google.com
    std::cout << browserHistory->forward(1) << std::endl; // facebook.com

    browserHistory->visit("linkedin.com"); // 此时 facebook 之后的 youtube 记录会被清理

    std::cout << browserHistory->forward(2) << std::endl; // linkedin.com (无法进一步前进)
    std::cout << browserHistory->back(2) << std::endl;    // google.com
    std::cout << browserHistory->back(7) << std::endl;    // leetcode.com (退到头了)

    delete browserHistory;
    return 0;
}

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */