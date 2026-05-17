#include <iostream>

static constexpr int MAX_N = 200'000;

int arr[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  // freopen("input.txt", "r", stdin);

  int T;
  std::cin >> T;

  for (int tc = 1; tc <= T; ++tc) {
    int n, p;
    std::cin >> n >> p;

    for (int i = 0; i < n; ++i) {
      std::cin >> arr[i];
    }

    int ans = p + 1;
    int left_idx = 0, right_idx = 0;

    while (right_idx < n - 1) {
      const int diff =
          arr[right_idx + 1] - arr[left_idx] - right_idx - 1 + left_idx;

      if (diff <= p) {
        ++right_idx;
      } else if (left_idx < right_idx) {
        ++left_idx;
      } else {
        left_idx = ++right_idx;
      }

      ans = std::max(ans, p + right_idx - left_idx + 1);
    }

    std::cout << "#" << tc << " " << ans << "\n";
  }

  return 0;
}