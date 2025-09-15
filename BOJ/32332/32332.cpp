#include <iostream>
#include <tuple>

std::istream& operator>>(std::istream& is,
                         std::tuple<int, int, int, double, double>& t) {
  is >> std::get<0>(t) >> std::get<1>(t) >> std::get<2>(t) >> std::get<3>(t) >>
      std::get<4>(t);
  return is;
}

std::ostream& operator<<(std::ostream& os,
                         const std::tuple<int, int, int, double, double>& t) {
  os << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) << " "
     << std::get<3>(t) << " " << std::get<4>(t);
  return os;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::tuple<int, int, int, double, double> now;
  std::tuple<int, int, int, double, double> target;

  std::cin >> now >> target;

  std::get<0>(now) = 2 * std::get<0>(now) - std::get<0>(target);
  std::get<1>(now) = 2 * std::get<1>(now) - std::get<1>(target);
  std::get<2>(now) = 2 * std::get<2>(now) - std::get<2>(target);
  std::get<3>(now) = 2 * std::get<3>(now) - std::get<3>(target);
  std::get<4>(now) = 2 * std::get<4>(now) - std::get<4>(target);

  while (std::get<2>(now) <= 0) {
    std::get<2>(now) += 30;
    --std::get<1>(now);
  }
  while (std::get<2>(now) > 30) {
    std::get<2>(now) -= 30;
    ++std::get<1>(now);
  }

  while (std::get<1>(now) <= 0) {
    std::get<1>(now) += 12;
    --std::get<0>(now);
  }
  while (std::get<1>(now) > 12) {
    std::get<1>(now) -= 12;
    ++std::get<0>(now);
  }

  std::cout.precision(3);
  std::cout << std::fixed;
  std::cout << now;

  return 0;
}