#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int a, b;
  std::cin >> a >> b;

  long long ans = 0;

  if (b > 2) {
    a = a < 3 ? 3 : a;

    a = (a + 1) >> 1;
    b >>= 1;

    ans = static_cast<long long>(b - a + 1) * (a + b);
  }

  std::cout << ans;

  return 0;
}