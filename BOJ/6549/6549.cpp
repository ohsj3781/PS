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

    long long ans = 0;

    // first is height, second is left index
    std::stack<std::pair<int, int>> stk;
    for (int i = 0; i < n; ++i) {
      int height;
      std::cin >> height;
      std::pair<int, int> temp(height, i);

      while (!stk.empty() && stk.top().first > temp.first) {
        ans = std::max(ans, static_cast<long long>(i - stk.top().second) *
                                stk.top().first);
        temp.second = stk.top().second;
        stk.pop();
      }
      if (!stk.empty() && stk.top().first == temp.first) {
        continue;
      }
      stk.push(temp);
    }

    while (!stk.empty()) {
      ans = std::max(
          ans, static_cast<long long>(n - stk.top().second) * stk.top().first);
      stk.pop();
    }

    std::cout << ans << "\n";
  }

  return 0;
}