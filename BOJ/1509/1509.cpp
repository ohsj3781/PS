#include <iostream>
#include <string>
#include <vector>

const size_t ConvertToIndex(const int left, const int right) {
  return left + (right * (right + 1) >> 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::string s;
  s.reserve(2500);
  std::cin >> s;

  std::vector<bool> is_palindrom((s.length() + 1) * s.length() >> 1, false);
  for (int i = 0; i < 2 * s.length() - 1; ++i) {
    int left = i >> 1, right = (i + 1) >> 1;
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
      is_palindrom[ConvertToIndex(left--, right++)] = true;
    }
  }

  std::vector<int> dp(s.length());
  for (int right = 0; right < dp.size(); ++right) {
    if (is_palindrom[ConvertToIndex(0, right)]) {
      dp[right] = 1;
      continue;
    }
    dp[right] = right + 1;
    for (int left = right; left >= 1; --left) {
      if (is_palindrom[ConvertToIndex(left, right)]) {
        dp[right] = std::min(dp[right], dp[left - 1] + 1);
      }
    }
  }

  std::cout << dp.back();

  return 0;
}