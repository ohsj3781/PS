#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, K;
  std::cin >> N >> K;

  std::array<int, 1024> cnt_strs = {
      0,
  };

  std::string str;
  str.reserve(10);
  for (int i = 0; i < N; ++i) {
    std::cin >> str;

    int converted_index = 0;
    for (int j = 0; j < str.length(); ++j) {
      const int num = str[j] - '0';
      converted_index |= 1 << num;
    }

    cnt_strs[converted_index]++;
  }

  std::array<long long, 1024> cnt_pairs = {
      0,
  };
  for (int i = 1; i < cnt_strs.size(); ++i) {
    for (int j = 1; j < i; ++j) {
      cnt_pairs[i | j] += static_cast<long long>(cnt_strs[i]) * cnt_strs[j];
    }
    cnt_pairs[i] +=
        static_cast<long long>(cnt_strs[i]) * (cnt_strs[i] - 1) >> 1;
  }

  long long ans = 0;
  for (int i = 0; i < cnt_pairs.size(); ++i) {
    std::bitset<10> b(i);
    if (b.count() != K) {
      continue;
    }
    ans += cnt_pairs[b.to_ulong()];
  }

  std::cout << ans;
  return 0;
}