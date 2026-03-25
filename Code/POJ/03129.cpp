#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
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
  Headquarter(int initial_m, const std::array<int, WARRIOR_COUNT> &hp_costs)
      : m_total_m(initial_m), m_costs(hp_costs) {}

  virtual ~Headquarter() = default;

  [[nodiscard]] virtual auto get_name() const noexcept -> std::string_view = 0;
  [[nodiscard]] virtual auto
  get_order() const noexcept -> const std::array<WarriorType, 5> & = 0;

  void step(int time) {
    if (m_stopped)
      return;

    const auto &order = get_order();

    for (int i = 0; i < 5; ++i) {
      WarriorType type = order[m_iter];
      int cost = m_costs[static_cast<int>(type)];

      if (m_total_m >= cost) {
        m_total_m -= cost;
        ++m_counts[static_cast<int>(type)];
        ++m_total_count;

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

protected:
  int m_total_m;
  const std::array<int, WARRIOR_COUNT> &m_costs;

  std::array<int, WARRIOR_COUNT> m_counts{0};
  int m_total_count{0};
  int m_iter{0};
  bool m_stopped{false};

private:
  void print_time(int time) const {
    std::cout << std::setfill('0') << std::setw(3) << time << ' ';
  }

  void log_production(int time, WarriorType type, int cost) const {
    print_time(time);
    auto type_idx = static_cast<int>(type);
    std::cout << get_name() << ' ' << WARRIOR_NAMES[type_idx] << ' '
              << m_total_count << " born with strength " << cost << ','
              << m_counts[type_idx] << ' ' << WARRIOR_NAMES[type_idx] << " in "
              << get_name() << " headquarter\n";
  }

  void log_stop(int time) const {
    print_time(time);
    std::cout << get_name() << " headquarter stops making warriors\n";
  }
};

class RedHeadquarter : public Headquarter {
public:
  using Headquarter::Headquarter;

  [[nodiscard]] auto get_name() const noexcept -> std::string_view override {
    return "red";
  }
  [[nodiscard]] auto
  get_order() const noexcept -> const std::array<WarriorType, 5> & override {
    return RED_ORDER;
  }
};

class BlueHeadquarter : public Headquarter {
public:
  using Headquarter::Headquarter;

  [[nodiscard]] auto get_name() const noexcept -> std::string_view override {
    return "blue";
  }
  [[nodiscard]] auto
  get_order() const noexcept -> const std::array<WarriorType, 5> & override {
    return BLUE_ORDER;
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

    std::array<std::unique_ptr<Headquarter>, 2> bases = {
        std::make_unique<RedHeadquarter>(M, warrior_HP),
        std::make_unique<BlueHeadquarter>(M, warrior_HP)};

    int time = 0;
    while (!bases[0]->is_stopped() || !bases[1]->is_stopped()) {
      for (auto &base : bases) {
        base->step(time);
      }
      time++;
    }
  }
}