#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::vector<int> v(5);
  for (auto& i : v) {
    std::cin >> i;
  }

  int ans = v[4];

  ans += v[3];
  v[0] = std::max(v[0] - v[3], 0);

  ans += v[2];
  const int left_basket = std::max(v[2] - v[1], 0);
  v[1] = std::max(v[1] - v[2], 0);
  v[0] = std::max(v[0] - 2 * left_basket, 0);

  ans += (v[1] + 1) >> 1;
  v[0] = std::max(v[0] - v[1] / 2, 0);
  v[0] = std::max(v[0] - 3 * (v[1] & 1), 0);

  ans += (v[0] + 4) / 5;

  std::cout << ans;

  return 0;
}