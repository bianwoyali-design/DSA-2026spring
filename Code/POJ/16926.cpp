#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ios>
#include <iostream>
#include <memory>
#include <string_view>
#include <vector>

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
  int atk;
  int res_m;
  WarriorType type;
  std::string_view headquarter;
};

class Warrior {
public:
  explicit Warrior(const Config &cfg)
      : m_id(cfg.id), m_hp(cfg.hp), m_atk(cfg.atk),
        m_headquarter(cfg.headquarter), m_type(cfg.type) {}

  virtual ~Warrior() = default;

  void get_damage(int damage) {
    m_hp -= damage;
    if (m_hp < 0)
      m_hp = 0;
  }

  [[nodiscard]] auto get_id() const noexcept -> int { return m_id; }
  [[nodiscard]] auto get_hp() const noexcept -> int { return m_hp; }
  [[nodiscard]] auto get_atk() const noexcept -> int { return m_atk; }
  [[nodiscard]] auto get_type() const noexcept -> WarriorType { return m_type; }
  [[nodiscard]] auto get_headquarter_name() const noexcept -> std::string_view {
    return m_headquarter;
  }

  [[nodiscard]] auto get_weapons_state() const noexcept -> int {
    int state = 0;
    for (const auto &w : m_weapons)
      state += w.usage;
    return state;
  }

  struct WeaponInfo {
    WeaponType type;
    int usage;
    WeaponInfo(WeaponType t, int c) : type(t), usage(c) {}
  };
  std::vector<WeaponInfo> m_weapons;

  void before_fight() {
    std::sort(m_weapons.begin(), m_weapons.end(),
              [](const WeaponInfo a, const WeaponInfo b) -> bool {
                if (a.type == b.type)
                  return a.usage < b.usage; // Arrow用过的排前面
                return a.type < b.type;
              });
  }

  void cleanup_weapons() {
    m_weapons.erase(std::remove_if(m_weapons.begin(), m_weapons.end(),
                                   [](const WeaponInfo &w) -> bool {
                                     return w.usage <= 0;
                                   }),
                    m_weapons.end());
    m_iter = 0;
  }

  void loot(Warrior *obj) {
    if (!obj)
      return;
    int size = static_cast<int>(obj->m_weapons.size());
    int i = 0;
    for (; i < size && m_weapons.size() < m_max_weapons &&
           obj->m_weapons[i].type != WeaponType::ARROW;
         ++i) {
      m_weapons.emplace_back(obj->m_weapons[i]);
    }
    for (int j = size - 1; j >= i && m_weapons.size() < m_max_weapons &&
                           obj->m_weapons[j].type == WeaponType::ARROW;
         --j) {
      m_weapons.emplace_back(obj->m_weapons[j]);
    }
  }

  void report_weapons(std::string_view time) const noexcept {
    std::array<int, 3> counts{0, 0, 0};
    for (const auto &w : m_weapons) {
      if (w.usage > 0)
        ++counts[static_cast<int>(w.type)];
    }
    std::cout << time << " " << get_headquarter_name() << " "
              << WARRIOR_NAMES[static_cast<int>(get_type())] << " " << m_id
              << " has " << counts[0] << " sword " << counts[1] << " bomb "
              << counts[2] << " arrow and " << m_hp << " elements\n";
  }

  virtual void print_extra_info() const noexcept = 0;

  virtual void attack(Warrior *obj) noexcept {
    if (!obj || m_weapons.empty() || m_hp == 0)
      return;

    int n = static_cast<int>(m_weapons.size());
    for (int i = 0; i < n; ++i) {
      auto &weapon = m_weapons[m_iter];

      if (weapon.usage > 0) {
        int damage = weapon_damage(weapon.type);
        obj->get_damage(damage);

        if (weapon.type == WeaponType::BOMB) {
          if (m_type != WarriorType::NINJA) {
            m_hp -= (damage / 2);
            if (m_hp < 0)
              m_hp = 0;
          }
          weapon.usage = 0;
        } else if (weapon.type == WeaponType::ARROW) {
          --weapon.usage;
        }

        m_iter = (m_iter + 1) % n;
        return;
      }
      m_iter = (m_iter + 1) % n;
    }
  }

  void reset_iter() { m_iter = 0; }
  virtual void yell(std::string_view time, int pos) const noexcept {}

protected:
  int m_id;
  int m_hp;
  int m_atk;
  WarriorType m_type;
  const int m_max_weapons = 10;
  std::string_view m_headquarter;
  int m_iter{0};

  [[nodiscard]] auto weapon_damage(WeaponType type) const noexcept -> int {
    switch (type) {
    case WeaponType::ARROW:
      return m_atk * 3 / 10;
    case WeaponType::BOMB:
      return m_atk * 4 / 10;
    case WeaponType::SWORD:
      return m_atk * 2 / 10;
    default:
      return 0;
    }
  }
};

class Dragon : public Warrior {
public:
  explicit Dragon(const Config &cfg) : Warrior(cfg) {
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
  }
  void yell(std::string_view time, int pos) const noexcept override {
    std::cout << time << ' ' << get_headquarter_name() << " dragon " << get_id()
              << " yelled in city " << pos << '\n';
  }
  void print_extra_info() const noexcept override {}
};

class Ninja : public Warrior {
public:
  explicit Ninja(const Config &cfg) : Warrior(cfg) {
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
    m_weapons.emplace_back(
        static_cast<WeaponType>((cfg.id + 1) % 3),
        static_cast<WeaponType>((cfg.id + 1) % 3) == WeaponType::ARROW ? 2 : 1);
  }
  void print_extra_info() const noexcept override {}
};

class Iceman : public Warrior {
public:
  explicit Iceman(const Config &cfg) : Warrior(cfg) {
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
  }

  void move_take_blood() { m_hp -= m_hp / 10; }
  void print_extra_info() const noexcept override {}
};

int K;
class Lion : public Warrior {
public:
  explicit Lion(const Config &cfg) : Warrior(cfg) {
    m_loyalty = cfg.res_m;
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
  }
  [[nodiscard]] auto is_loyal() const noexcept -> bool { return m_loyalty > 0; }
  void down_loyalty() { m_loyalty -= m_K; }
  void print_extra_info() const noexcept override {
    std::cout << "Its loyalty is " << m_loyalty << '\n';
  }

private:
  int m_loyalty;
  const int m_K = K;
};

class Wolf : public Warrior {
public:
  using Warrior::Warrior;

  void snatch(Warrior *obj, int city_pos, std::string_view time) {
    if (!obj)
      return;
    before_fight();
    obj->before_fight();

    if (!obj->m_weapons.empty() && m_weapons.size() < m_max_weapons) {
      int snatch_num = 0;
      auto obj_type = obj->m_weapons.front().type;

      if (obj_type == WeaponType::ARROW) {
        for (int i = static_cast<int>(obj->m_weapons.size() - 1);
             i >= 0 && m_weapons.size() < m_max_weapons; --i) {
          m_weapons.emplace_back(obj->m_weapons[i]);
          obj->m_weapons.erase(obj->m_weapons.begin() + i);
          ++snatch_num;
        }
      } else {
        while (!obj->m_weapons.empty() &&
               obj->m_weapons.front().type == obj_type &&
               m_weapons.size() < m_max_weapons) {
          m_weapons.emplace_back(obj->m_weapons.front());
          obj->m_weapons.erase(obj->m_weapons.begin());
          ++snatch_num;
        }
      }

      if (snatch_num > 0)
        std::cout << time << ' ' << m_headquarter << " wolf " << m_id
                  << " took " << snatch_num << ' '
                  << WEAPON_NAMES[static_cast<int>(obj_type)] << " from "
                  << obj->get_headquarter_name() << ' '
                  << WARRIOR_NAMES[static_cast<int>(obj->get_type())] << " "
                  << obj->get_id() << " in city " << city_pos << '\n';
    }
  }
  void print_extra_info() const noexcept override {}
};

class Headquarter {
public:
  explicit Headquarter(const std::array<int, WARRIOR_COUNT> &atk, int initial_m,
                       const std::array<int, WARRIOR_COUNT> &hp_costs, int N)
      : m_atk(atk), m_total_m(initial_m), m_costs(hp_costs), m_N(N) {}

  virtual ~Headquarter() = default;

  [[nodiscard]] virtual auto get_name() const noexcept -> std::string_view = 0;
  [[nodiscard]] virtual auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & = 0;

  void report_elements(std::string_view time) const {
    std::cout << time << " " << m_total_m << " elements in " << get_name()
              << " headquarter\n";
  }

  [[nodiscard]] auto step(std::string_view time) noexcept
      -> std::unique_ptr<Warrior> {
    if (m_stopped)
      return nullptr;

    const auto &order = get_order();
    WarriorType type = order[m_iter];
    int cost = m_costs[static_cast<int>(type)];

    if (m_total_m >= cost) {
      m_total_m -= cost;
      ++m_counts[static_cast<int>(type)];
      int id = ++m_total_count;
      int atk = m_atk[static_cast<int>(type)];

      auto warrior = create_warrior(id, type, cost, atk);
      log_production(time, type, cost);
      warrior->print_extra_info();

      m_iter = (m_iter + 1) % 5;
      return warrior;
    }

    m_stopped = true;
    return nullptr;
  }

protected:
  int m_total_m;
  int m_N;
  const std::array<int, WARRIOR_COUNT> &m_costs;
  const std::array<int, WARRIOR_COUNT> &m_atk;
  std::array<int, WARRIOR_COUNT> m_counts{0};
  int m_total_count{0};
  int m_iter{0};
  bool m_stopped{false};

private:
  void log_production(std::string_view time, WarriorType type, int cost) const {
    std::cout << time << ' ' << get_name() << ' '
              << WARRIOR_NAMES[static_cast<int>(type)] << ' ' << m_total_count
              << " born\n";
  }

  [[nodiscard]] auto create_warrior(int id, WarriorType type, int cost,
                                    const int atk) const noexcept
      -> std::unique_ptr<Warrior> {
    Config cfg = {.id = id,
                  .hp = cost,
                  .atk = atk,
                  .res_m = m_total_m,
                  .type = type,
                  .headquarter = get_name()};
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

class City {
public:
  explicit City(int i) : m_pos(i) {}

  [[nodiscard]] auto get_red() const noexcept -> Warrior * {
    return m_red_warrior.get();
  }
  [[nodiscard]] auto get_blue() const noexcept -> Warrior * {
    return m_blue_warrior.get();
  }
  [[nodiscard]] auto red_leaves() -> std::unique_ptr<Warrior> {
    return std::move(m_red_warrior);
  }
  [[nodiscard]] auto blue_leaves() -> std::unique_ptr<Warrior> {
    return std::move(m_blue_warrior);
  }

  void produce_red(std::unique_ptr<Warrior> w) { m_red_warrior = std::move(w); }
  void produce_blue(std::unique_ptr<Warrior> w) {
    m_blue_warrior = std::move(w);
  }
  void accept_incoming_red(std::unique_ptr<Warrior> w) {
    m_incoming_red = std::move(w);
  }
  void accept_incoming_blue(std::unique_ptr<Warrior> w) {
    m_incoming_blue = std::move(w);
  }

  [[nodiscard]] auto is_taken() const noexcept -> bool { return m_enemy_count >= 1; }

  void check_lion(std::string_view time, int N) {
    if (m_red_warrior && m_red_warrior->get_type() == WarriorType::LION &&
        m_pos < N + 1) {
      auto *lion = static_cast<Lion *>(m_red_warrior.get());
      if (!lion->is_loyal()) {
        std::cout << time << " red lion " << lion->get_id() << " ran away\n";
        m_red_warrior = nullptr;
      }
    }
    if (m_blue_warrior && m_blue_warrior->get_type() == WarriorType::LION &&
        m_pos > 0) {
      auto *lion = static_cast<Lion *>(m_blue_warrior.get());
      if (!lion->is_loyal()) {
        std::cout << time << " blue lion " << lion->get_id() << " ran away\n";
        m_blue_warrior = nullptr;
      }
    }
  }

  void commit_arrivals(std::string_view time, int N) {
    if (m_incoming_red) {
      m_red_warrior = std::move(m_incoming_red);
      if (m_red_warrior->get_type() == WarriorType::ICEMAN)
        static_cast<Iceman *>(m_red_warrior.get())->move_take_blood();
      else if (m_red_warrior->get_type() == WarriorType::LION)
        static_cast<Lion *>(m_red_warrior.get())->down_loyalty();

      std::cout << time << " red "
                << WARRIOR_NAMES[static_cast<int>(m_red_warrior->get_type())]
                << ' ' << m_red_warrior->get_id();
      if (m_pos == N + 1) {
        std::cout << " reached blue headquarter with "
                  << m_red_warrior->get_hp() << " elements and force "
                  << m_red_warrior->get_atk() << '\n';
        ++m_enemy_count;
        if (is_taken())
          std::cout << time << " blue headquarter was taken\n";
      } else {
        std::cout << " marched to city " << m_pos << " with "
                  << m_red_warrior->get_hp() << " elements and force "
                  << m_red_warrior->get_atk() << '\n';
      }
    }

    if (m_incoming_blue) {
      m_blue_warrior = std::move(m_incoming_blue);
      if (m_blue_warrior->get_type() == WarriorType::ICEMAN)
        static_cast<Iceman *>(m_blue_warrior.get())->move_take_blood();
      else if (m_blue_warrior->get_type() == WarriorType::LION)
        static_cast<Lion *>(m_blue_warrior.get())->down_loyalty();

      std::cout << time << " blue "
                << WARRIOR_NAMES[static_cast<int>(m_blue_warrior->get_type())]
                << ' ' << m_blue_warrior->get_id();
      if (m_pos == 0) {
        std::cout << " reached red headquarter with "
                  << m_blue_warrior->get_hp() << " elements and force "
                  << m_blue_warrior->get_atk() << '\n';
        ++m_enemy_count;
        if (is_taken())
          std::cout << time << " red headquarter was taken\n";
      } else {
        std::cout << " marched to city " << m_pos << " with "
                  << m_blue_warrior->get_hp() << " elements and force "
                  << m_blue_warrior->get_atk() << '\n';
      }
    }
  }

  void wolf_snatch(std::string_view time) {
    if (!m_red_warrior || !m_blue_warrior)
      return;
    bool red_is_wolf = (m_red_warrior->get_type() == WarriorType::WOLF);
    bool blue_is_wolf = (m_blue_warrior->get_type() == WarriorType::WOLF);

    if (red_is_wolf && !blue_is_wolf)
      static_cast<Wolf *>(m_red_warrior.get())
          ->snatch(m_blue_warrior.get(), m_pos, time);
    else if (!red_is_wolf && blue_is_wolf)
      static_cast<Wolf *>(m_blue_warrior.get())
          ->snatch(m_red_warrior.get(), m_pos, time);
  }

  void fight(std::string_view time) {
    if (!m_red_warrior || !m_blue_warrior)
      return;
    bool both_no_weapons =
        m_red_warrior->m_weapons.empty() && m_blue_warrior->m_weapons.empty();

    if (!both_no_weapons) {
      m_red_warrior->before_fight();
      m_blue_warrior->before_fight();
      m_red_warrior->reset_iter();
      m_blue_warrior->reset_iter();

      Warrior *first =
          (m_pos % 2 == 1) ? m_red_warrior.get() : m_blue_warrior.get();
      Warrior *second =
          (m_pos % 2 == 1) ? m_blue_warrior.get() : m_red_warrior.get();

      int unchanged_rounds =
          0;

      while (true) {
        int r_hp = m_red_warrior->get_hp(),
            r_ws = m_red_warrior->get_weapons_state();
        int b_hp = m_blue_warrior->get_hp(),
            b_ws = m_blue_warrior->get_weapons_state();

        first->attack(second);
        if (first->get_hp() <= 0 || second->get_hp() <= 0)
          break;

        second->attack(first);
        if (first->get_hp() <= 0 || second->get_hp() <= 0)
          break;

        if (r_hp == m_red_warrior->get_hp() &&
            r_ws == m_red_warrior->get_weapons_state() &&
            b_hp == m_blue_warrior->get_hp() &&
            b_ws == m_blue_warrior->get_weapons_state()) {
          unchanged_rounds++;
        } else {
          unchanged_rounds = 0;
        }

        if (unchanged_rounds >= 20)
          break;
      }
    }

    handle_result_and_logs(time);
  }

  void report_warrior_status(std::string_view time) const {
    if (m_red_warrior)
      m_red_warrior->report_weapons(time);
    if (m_blue_warrior)
      m_blue_warrior->report_weapons(time);
  }

private:
  int m_pos;
  int m_enemy_count{0};
  std::unique_ptr<Warrior> m_red_warrior;
  std::unique_ptr<Warrior> m_blue_warrior;
  std::unique_ptr<Warrior> m_incoming_red;
  std::unique_ptr<Warrior> m_incoming_blue;

  void print_both_died_log(std::string_view time) const noexcept {
    std::cout << time << " both red "
              << WARRIOR_NAMES[static_cast<int>(m_red_warrior->get_type())]
              << ' ' << m_red_warrior->get_id() << " and blue "
              << WARRIOR_NAMES[static_cast<int>(m_blue_warrior->get_type())]
              << ' ' << m_blue_warrior->get_id() << " died in city " << m_pos
              << '\n';
  }

  void print_alive_log(std::string_view time) const noexcept {
    std::cout << time << " both red "
              << WARRIOR_NAMES[static_cast<int>(m_red_warrior->get_type())]
              << ' ' << m_red_warrior->get_id() << " and blue "
              << WARRIOR_NAMES[static_cast<int>(m_blue_warrior->get_type())]
              << ' ' << m_blue_warrior->get_id() << " were alive in city "
              << m_pos << '\n';
  }

  void handle_result_and_logs(std::string_view time) noexcept {
    bool red_dead = (m_red_warrior->get_hp() <= 0);
    bool blue_dead = (m_blue_warrior->get_hp() <= 0);

    if (red_dead && blue_dead) {
      print_both_died_log(time);
      m_red_warrior = nullptr;
      m_blue_warrior = nullptr;
    } else if (red_dead) {
      m_red_warrior->cleanup_weapons();
      m_blue_warrior->cleanup_weapons();
      m_blue_warrior->loot(m_red_warrior.get());
      std::cout << time << " blue "
                << WARRIOR_NAMES[static_cast<int>(m_blue_warrior->get_type())]
                << ' ' << m_blue_warrior->get_id() << " killed red "
                << WARRIOR_NAMES[static_cast<int>(m_red_warrior->get_type())]
                << ' ' << m_red_warrior->get_id() << " in city " << m_pos
                << " remaining " << m_blue_warrior->get_hp() << " elements\n";
      m_red_warrior = nullptr;
      if (m_blue_warrior->get_type() == WarriorType::DRAGON)
        m_blue_warrior->yell(time, m_pos);
    } else if (blue_dead) {
      m_blue_warrior->cleanup_weapons();
      m_red_warrior->cleanup_weapons();
      m_red_warrior->loot(m_blue_warrior.get());
      std::cout << time << " red "
                << WARRIOR_NAMES[static_cast<int>(m_red_warrior->get_type())]
                << ' ' << m_red_warrior->get_id() << " killed blue "
                << WARRIOR_NAMES[static_cast<int>(m_blue_warrior->get_type())]
                << ' ' << m_blue_warrior->get_id() << " in city " << m_pos
                << " remaining " << m_red_warrior->get_hp() << " elements\n";
      m_blue_warrior = nullptr;
      if (m_red_warrior->get_type() == WarriorType::DRAGON)
        m_red_warrior->yell(time, m_pos);
    } else {
      m_red_warrior->cleanup_weapons();
      m_blue_warrior->cleanup_weapons();
      print_alive_log(time);
      if (m_red_warrior->get_type() == WarriorType::DRAGON)
        m_red_warrior->yell(time, m_pos);
      if (m_blue_warrior->get_type() == WarriorType::DRAGON)
        m_blue_warrior->yell(time, m_pos);
    }
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  if (!(std::cin >> t))
    return 0;

  for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
    int M, N, T;
    std::cin >> M >> N >> K >> T;
    std::array<int, WARRIOR_COUNT> warrior_HP;
    for (int &hp : warrior_HP)
      std::cin >> hp;
    std::array<int, WARRIOR_COUNT> warrior_ATK;
    for (int &atk : warrior_ATK)
      std::cin >> atk;

    std::cout << "Case " << caseIdx << ":\n";

    std::array<std::unique_ptr<Headquarter>, 2> bases = {
        std::make_unique<RedHeadquarter>(warrior_ATK, M, warrior_HP, N),
        std::make_unique<BlueHeadquarter>(warrior_ATK, M, warrior_HP, N)};

    std::vector<City> cities;
    cities.reserve(N + 2);
    for (int i = 0; i < N + 2; ++i)
      cities.emplace_back(i);

    int hour = 0;
    bool game_over = false;

    while (true) {
      if (hour * 60 > T || game_over)
        break;

      char m_buf[16];
      int len = std::snprintf(m_buf, sizeof(m_buf), "%03d:00", hour);
      std::string_view time_00(m_buf, len);

      cities[0].produce_red(bases[0]->step(time_00));
      cities[N + 1].produce_blue(bases[1]->step(time_00));

      if (hour * 60 + 5 > T)
        break;
      len = std::snprintf(m_buf, sizeof(m_buf), "%03d:05", hour);
      std::string_view time_05(m_buf, len);

      for (int i = 0; i < N + 2; ++i)
        cities[i].check_lion(time_05, N);

      if (hour * 60 + 10 > T)
        break;
      len = std::snprintf(m_buf, sizeof(m_buf), "%03d:10", hour);
      std::string_view time_10(m_buf, len);

      for (int i = 0; i < N + 2; ++i) {
        if (cities[i].get_red() && i < N + 1)
          cities[i + 1].accept_incoming_red(cities[i].red_leaves());
        if (cities[i].get_blue() && i > 0)
          cities[i - 1].accept_incoming_blue(cities[i].blue_leaves());
      }

      for (int i = 0; i < N + 2; ++i) {
        cities[i].commit_arrivals(time_10, N);
        if (cities[i].is_taken())
          game_over = true;
      }
      if (game_over)
        break;

      if (hour * 60 + 35 > T)
        break;
      len = std::snprintf(m_buf, sizeof(m_buf), "%03d:35", hour);
      std::string_view time_35(m_buf, len);

      for (int i = 1; i <= N; ++i)
        cities[i].wolf_snatch(time_35);

      if (hour * 60 + 40 > T)
        break;
      len = std::snprintf(m_buf, sizeof(m_buf), "%03d:40", hour);
      std::string_view time_40(m_buf, len);

      for (int i = 1; i <= N; ++i)
        cities[i].fight(time_40);

      if (hour * 60 + 50 > T)
        break;
      len = std::snprintf(m_buf, sizeof(m_buf), "%03d:50", hour);
      std::string_view time_50(m_buf, len);

      bases[0]->report_elements(time_50);
      bases[1]->report_elements(time_50);

      if (hour * 60 + 55 > T)
        break;
      len = std::snprintf(m_buf, sizeof(m_buf), "%03d:55", hour);
      std::string_view time_55(m_buf, len);

      for (int i = 0; i < N + 2; ++i)
        cities[i].report_warrior_status(time_55);

      ++hour;
    }
  }
}