#include <array>
#include <iostream>

int main() {
  int N;
  std::cin >> N;

  std::array<int, 6> arr;
  for (auto i = arr.begin(); i != arr.end(); ++i) {
    std::cin >> *i;
  }

  int T, P;
  std::cin >> T >> P;

  int sum_T = 0;
  for (auto i = arr.begin(); i != arr.end(); ++i) {
    sum_T += (*i + T - 1) / T;
  }

  std::cout << sum_T << '\n' << N / P << ' ' << N % P;
  return 0;
}