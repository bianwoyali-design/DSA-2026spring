#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string_view>

enum class WarriorType : std::uint8_t {
  DRAGON = 0,
  NINJA,
  ICEMAN,
  LION,
  WOLF,
  COUNT
};

constexpr int WARRIOR_COUNT = static_cast<int>(WarriorType::COUNT);

constexpr std::array<std::string_view, WARRIOR_COUNT> WARRIOR_NAMES = {
    "dragon", "ninja", "iceman", "lion", "wolf"};

constexpr std::array<WarriorType, 5> RED_ORDER = {
    WarriorType::ICEMAN, WarriorType::LION, WarriorType::WOLF,
    WarriorType::NINJA, WarriorType::DRAGON};

constexpr std::array<WarriorType, 5> BLUE_ORDER = {
    WarriorType::LION, WarriorType::DRAGON, WarriorType::NINJA,
    WarriorType::ICEMAN, WarriorType::WOLF};

class Headquarter {
public:
  Headquarter(std::string_view name, int initial_m,
              const std::array<int, WARRIOR_COUNT> &hp_costs,
              const std::array<WarriorType, 5> &build_order)
      : m_name(name), m_total_m(initial_m), m_costs(hp_costs),
        m_order(build_order) {}

  void step(int time) {
    if (m_stopped)
      return;

    for (int i = 0; i < 5; ++i) {
      WarriorType type = m_order[m_iter];
      int cost = m_costs[static_cast<int>(type)];

      if (m_total_m >= cost) {
        m_total_m -= cost;
        m_counts[static_cast<int>(type)]++;
        m_total_count++;

        log_production(time, type, cost);

        m_iter = (m_iter + 1) % 5;
        return;
      }

      m_iter = (m_iter + 1) % 5;
    }

    m_stopped = true;
    log_stop(time);
  }

  [[nodiscard]] auto is_stopped() const noexcept -> bool { return m_stopped; }

private:
  std::string_view m_name;
  int m_total_m;
  const std::array<int, WARRIOR_COUNT> &m_costs;
  const std::array<WarriorType, 5> &m_order;

  std::array<int, WARRIOR_COUNT> m_counts{0};
  int m_total_count{0};
  int m_iter{0};
  bool m_stopped{false};

  void print_time(int time) const {
    std::cout << std::setfill('0') << std::setw(3) << time << ' ';
  }

  void log_production(int time, WarriorType type, int cost) const {
    print_time(time);
    auto type_idx = static_cast<int>(type);
    std::cout << m_name << ' ' << WARRIOR_NAMES[type_idx] << ' '
              << m_total_count << " born with strength " << cost << ','
              << m_counts[type_idx] << ' ' << WARRIOR_NAMES[type_idx] << " in "
              << m_name << " headquarter\n";
  }

  void log_stop(int time) const {
    print_time(time);
    std::cout << m_name << " headquarter stops making warriors\n";
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  if (!(std::cin >> t))
    return 0;

  for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
    int M;
    std::cin >> M;
    std::array<int, WARRIOR_COUNT> warrior_HP;
    for (int &hp : warrior_HP) {
      std::cin >> hp;
    }

    std::cout << "Case:" << caseIdx << '\n';

    Headquarter red("red", M, warrior_HP, RED_ORDER);
    Headquarter blue("blue", M, warrior_HP, BLUE_ORDER);

    int time = 0;
    while (!red.is_stopped() || !blue.is_stopped()) {
      red.step(time);
      blue.step(time);
      time++;
    }
  }
}