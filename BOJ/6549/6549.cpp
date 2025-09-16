#include <iostream>
#include <stack>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  while (true) {
    int n;
    std::cin >> n;
    if (n == 0) {
      break;
    }

    std::vector<int> heights(n);
    for (int i = 0; i < heights.size(); ++i) {
      std::cin >> heights[i];
    }

    std::vector<std::pair<int, int>> range(n);
    for (int i = 0; i < range.size(); ++i) {
      range[i] = {i, i};
    }

    long long ans = 0;
    for (int i = 0; i < range.size(); ++i) {
      if (heights[i] == 0) {
        continue;
      }

      while (range[i].first - 1 >= 0 &&
             heights[i] <= heights[range[i].first - 1]) {
        range[i].first = range[range[i].first - 1].first;
      }
    }

    for (int i = range.size() - 1; i >= 0; --i) {
      while (range[i].second + 1 < heights.size() &&
             heights[i] <= heights[range[i].second + 1]) {
        range[i].second = range[range[i].second + 1].second;
      }

      ans = std::max(
          ans, static_cast<long long>(range[i].second - range[i].first + 1) *
                   heights[i]);
    }

    std::cout << ans << "\n";
  }

  return 0;
}