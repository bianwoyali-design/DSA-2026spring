#include <array>
#include <cstdint>
#include <iomanip>
#include <ios>
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

enum class WeaponType : std::uint8_t { SWORD = 0, BOMB, ARROW, COUNT };

constexpr int WEAPON_COUNT = static_cast<int>(WeaponType::COUNT);

constexpr std::array<std::string_view, WEAPON_COUNT> WEAPON_NAMES = {
    "sword", "bomb", "arrow"};

struct Config {
  int id;
  int hp;
  int res_m;
};

class Warrior {
public:
  Warrior(const Config &cfg) : m_id(cfg.id), m_hp(cfg.hp) {}

  virtual ~Warrior() = default;

  virtual void print_extra_info() const noexcept = 0;

protected:
  int m_id;
  int m_hp;
};

class Dragon : public Warrior {
public:
  Dragon(const Config &cfg) : Warrior(cfg) {
    m_morale = static_cast<double>(cfg.res_m) / cfg.hp;
    m_weapon = static_cast<WeaponType>(cfg.id % 3);
  }

  void print_extra_info() const noexcept override {
    std::cout << "It has a " << WEAPON_NAMES[static_cast<int>(m_weapon)]
              << ",and it's morale is " << std::fixed << std::setprecision(2)
              << m_morale << '\n';
  }

private:
  double m_morale;
  WeaponType m_weapon;
};

class Ninja : public Warrior {
public:
  Ninja(const Config &cfg) : Warrior(cfg) {
    m_weapon1 = static_cast<WeaponType>(cfg.id % 3);
    m_weapon2 = static_cast<WeaponType>((cfg.id + 1) % 3);
  }

  void print_extra_info() const noexcept override {
    std::cout << "It has a " << WEAPON_NAMES[static_cast<int>(m_weapon1)]
              << " and a " << WEAPON_NAMES[static_cast<int>(m_weapon2)] << '\n';
  }

private:
  WeaponType m_weapon1;
  WeaponType m_weapon2;
};

class Iceman : public Warrior {
public:
  Iceman(const Config &cfg) : Warrior(cfg) {
    m_weapon = static_cast<WeaponType>(cfg.id % 3);
  }

  void print_extra_info() const noexcept override {
    std::cout << "It has a " << WEAPON_NAMES[static_cast<int>(m_weapon)]
              << '\n';
  }

private:
  WeaponType m_weapon;
};

class Lion : public Warrior {
public:
  Lion(const Config &cfg) : Warrior(cfg) { m_loyalty = cfg.res_m; }

  void print_extra_info() const noexcept override {
    std::cout << "It's loyalty is " << m_loyalty << '\n';
  }

private:
  int m_loyalty;
};

class Wolf : public Warrior {
public:
  using Warrior::Warrior;
  void print_extra_info() const noexcept override {}
};

class Headquarter {
public:
  Headquarter(int initial_m, const std::array<int, WARRIOR_COUNT> &hp_costs)
      : m_total_m(initial_m), m_costs(hp_costs) {}

  virtual ~Headquarter() = default;

  [[nodiscard]] virtual auto get_name() const noexcept -> std::string_view = 0;
  [[nodiscard]] virtual auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & = 0;

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
        int id = ++m_total_count;

        auto warrior = create_warrior(id, type, cost);

        log_production(time, type, cost);

        warrior->print_extra_info();

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

  [[nodiscard]] auto create_warrior(int id, WarriorType type,
                                    int cost) const noexcept
      -> std::unique_ptr<Warrior> {
    Config cfg = {.id = id, .hp = cost, .res_m = m_total_m};

    switch (type) {
    case WarriorType::DRAGON:
      return std::make_unique<Dragon>(cfg);
    case WarriorType::NINJA:
      return std::make_unique<Ninja>(cfg);
    case WarriorType::ICEMAN:
      return std::make_unique<Iceman>(cfg);
    case WarriorType::LION:
      return std::make_unique<Lion>(cfg);
    case WarriorType::WOLF:
      return std::make_unique<Wolf>(cfg);
    default:
      return nullptr;
    }
  }
};

class RedHeadquarter : public Headquarter {
public:
  using Headquarter::Headquarter;

  [[nodiscard]] auto get_name() const noexcept -> std::string_view override {
    return "red";
  }
  [[nodiscard]] auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & override {
    return RED_ORDER;
  }
};

class BlueHeadquarter : public Headquarter {
public:
  using Headquarter::Headquarter;

  [[nodiscard]] auto get_name() const noexcept -> std::string_view override {
    return "blue";
  }
  [[nodiscard]] auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & override {
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