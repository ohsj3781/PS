#include <climits>
#include <iostream>
#include <vector>

constexpr int INF = INT_MAX;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<int> nums(N);
  std::vector<int> scores(1'000'001, INF);

  for (auto &num : nums) {
    std::cin >> num;
    scores[num] = 0;
  }

  for (auto num : nums) {
    for (int i = 2 * num; i <= 1'000'000; i += num) {
      if (scores[i] != INF) {
        scores[num]++;
        scores[i]--;
      }
    }
  }

  for (auto num : nums) {
    std::cout << scores[num] << ' ';
  }

  return 0;
}