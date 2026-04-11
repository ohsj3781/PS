#include <array>
#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::array<long long, 10> cnt_num = {
      0,
  };

  for (long long divider = 10; divider / 10 <= N; divider *= 10) {
    const long long quotient = (N + 1) / divider;
    const long long remainder = (N + 1) % divider;

    for (int i = 0; i < cnt_num.size(); ++i) {
      if (i == 0) {
        if (quotient == 0) {
          continue;
        }

        cnt_num[i] += (quotient - 1) * (divider / 10);

        if (remainder / (divider / 10) > i) {
          cnt_num[i] += (divider / 10);
        } else if (remainder / (divider / 10) == i) {
          cnt_num[i] += remainder % (divider / 10);
        }

      } else {
        cnt_num[i] += quotient * (divider / 10);

        if (remainder / (divider / 10) > i) {
          cnt_num[i] += (divider / 10);
        } else if (remainder / (divider / 10) == i) {
          cnt_num[i] += remainder % (divider / 10);
        }
      }
    }
  }

  for (int i = 0; i < cnt_num.size(); ++i) {
    std::cout << cnt_num[i] << " ";
  }

  return 0;
}