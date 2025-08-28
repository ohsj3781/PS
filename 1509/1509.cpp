#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::string s;
  s.reserve(2500);
  std::cin >> s;

  std::vector<std::vector<bool>> is_palindrom(
      s.length(), std::vector<bool>(s.length(), false));
  for (int i = 0; i < 2 * s.length() - 1; ++i) {
    int left = i >> 1, right = (i + 1) >> 1;
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
      is_palindrom[left--][right++] = true;
    }
  }

  std::vector<int> dp(s.length());
  for (int right = 0; right < dp.size(); ++right) {
    if (is_palindrom[0][right]) {
      dp[right] = 1;
      continue;
    }
    dp[right] = right + 1;
    for (int left = right; left >= 1; --left) {
      if (is_palindrom[left][right]) {
        dp[right] = std::min(dp[right], dp[left - 1] + 1);
      }
    }
  }

  std::cout << dp.back();

  return 0;
}