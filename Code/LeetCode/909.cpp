#include <iostream>
#include <queue>
#include <vector>

class Solution {
  auto _build_targets(const std::vector<std::vector<int>> &board)
      -> std::vector<int> {
    const int side = board.size();
    std::vector<int> targets(side * side);
    int index = 0;

    bool left_to_right = true;
    for (int row = side - 1; row >= 0; --row) {
      if (left_to_right) {
        for (int col = 0; col < side; ++col) {
          targets[index] = board[row][col] == -1 ? index : board[row][col] - 1;
          ++index;
        }
      } else {
        for (int col = side - 1; col >= 0; --col) {
          targets[index] = board[row][col] == -1 ? index : board[row][col] - 1;
          ++index;
        }
      }
      left_to_right = !left_to_right;
    }

    return targets;
  }

public:
  auto snakesAndLadders(const std::vector<std::vector<int>> &board) -> int {
    const auto targets = _build_targets(board);
    const int n = targets.size();

    std::queue<int> q;
    std::vector<int> dist(n, -1);
    q.emplace(0);
    dist[0] = 0;

    while (!q.empty()) {
      int front = q.front();
      q.pop();

      if (front == n - 1) {
        return dist[front];
      }

      for (int step = 1; step <= 6 && front + step < n; ++step) {
        int next = targets[front + step];

        if (dist[next] == -1) {
          dist[next] = dist[front] + 1;
          q.emplace(next);
        }
      }
    }

    return -1;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<std::vector<int>> board = {
      {-1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1, -1}, {-1, 35, -1, -1, 13, -1},
      {-1, -1, -1, -1, -1, -1}, {-1, 15, -1, -1, -1, -1}};
  std::cout << sol.snakesAndLadders(board) << '\n';
}
