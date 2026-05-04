#include <array>
#include <bit>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

class Solution {
public:
  auto solveSudoku(std::vector<std::vector<char>> &board) -> void {
    constexpr std::uint16_t full_mask = (1 << 9) - 1;
    std::array<std::uint16_t, 9> row_mask{};
    std::array<std::uint16_t, 9> col_mask{};
    std::array<std::uint16_t, 9> box_mask{};
    std::array<std::uint8_t, 81> empty_box{};
    int empty_count = 0;

    auto box_id = [](int i, int j) -> int { return i / 3 * 3 + j / 3; };

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          empty_box[empty_count++] = static_cast<std::uint8_t>(i * 9 + j);
        } else {
          int num = static_cast<int>(board[i][j] - '1');
          auto bit = static_cast<std::uint16_t>(1 << num);
          row_mask[i] |= bit;
          col_mask[j] |= bit;
          box_mask[box_id(i, j)] |= bit;
        }
      }
    }

    auto get_candidates = [&](int i, int j) -> std::uint16_t {
      return static_cast<std::uint16_t>(
          full_mask & ~(row_mask[i] | col_mask[j] | box_mask[box_id(i, j)]));
    };

    auto dfs = [&](this auto &&self, int index) -> bool {
      if (index == empty_count) {
        return true;
      }

      int best_index = index;
      std::uint16_t best_candidates = 0;
      int best_count = 10;
      for (int k = index; k < empty_count; ++k) {
        int i = empty_box[k] / 9;
        int j = empty_box[k] % 9;
        std::uint16_t candidates = get_candidates(i, j);
        int count = std::popcount(static_cast<unsigned>(candidates));
        if (count < best_count) {
          best_index = k;
          best_candidates = candidates;
          best_count = count;
          if (count == 1) {
            break;
          }
        }
      }

      if (best_count == 0) {
        return false;
      }

      std::swap(empty_box[index], empty_box[best_index]);
      int i = empty_box[index] / 9;
      int j = empty_box[index] % 9;
      int box = box_id(i, j);
      std::uint16_t candidates = best_candidates;

      while (candidates != 0) {
        auto bit = static_cast<std::uint16_t>(candidates & -candidates);
        int num = std::countr_zero(static_cast<unsigned>(bit));
        board[i][j] = static_cast<char>('1' + num);
        row_mask[i] |= bit;
        col_mask[j] |= bit;
        box_mask[box] |= bit;

        if (self(index + 1)) {
          return true;
        }

        row_mask[i] ^= bit;
        col_mask[j] ^= bit;
        box_mask[box] ^= bit;
        candidates ^= bit;
      }

      std::swap(empty_box[index], empty_box[best_index]);
      return false;
    };

    dfs(0);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<char>> board{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
  };
  Solution sol;
  sol.solveSudoku(board);

  for (auto &&row : board) {
    for (auto [i, v] : std::views::zip(std::views::iota(0), row)) {
      std::cout << v << " \n"[i == 8];
    }
  }
}
