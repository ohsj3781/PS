#include <cmath>
#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  long long n;
  std::cin >> n;

  long long ans = 1;

  if ((n & 1) == 0) {
    n >>= 1;

    while ((n & 1) == 0) {
      n >>= 1;
      ans *= 2;
    }
  }

  for (long long i = 3; i * i <= n; i += 2) {
    if (n % i != 0) {
      continue;
    }

    n /= i;
    ans *= i - 1;

    while (n % i == 0) {
      n /= i;
      ans *= i;
    }
  }

  if (n != 1) {
    ans *= n - 1;
  }

  std::cout << ans;

  return 0;
}