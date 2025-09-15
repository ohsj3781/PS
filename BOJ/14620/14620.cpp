#include <climits>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

constexpr int INF = INT_MAX;

int N;
std::vector<std::vector<int>> m;
const int calc_cost(const std::pair<int, int>& p) {
  static const std::vector<std::pair<int, int>> BIAS = {
      {0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  int cost = 0;

  for (auto& i : BIAS) {
    const std::pair<int, int> now_p = {p.first + i.first, p.second + i.second};
    if (now_p.first < 0 || now_p.first >= N || now_p.second < 0 ||
        now_p.second >= N) {
      cost = -1;
      break;
    }
    cost += m[now_p.first][now_p.second];
  }

  return cost;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> N;

  m.assign(N, std::vector<int>(N));

  for (auto& i : m) {
    for (auto& j : i) {
      std::cin >> j;
    }
  }

  int ans = INF;

  for (int i = 0; i < N * N; ++i) {
    const std::pair<int, int> p1 = {i / N, i % N};
    const int c1 = calc_cost(p1);
    if (c1 == -1) {
      continue;
    }
    for (int j = i + 1; j < N * N; ++j) {
      const std::pair<int, int> p2 = {j / N, j % N};
      if (std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second) <=
          2) {
        continue;
      }
      const int c2 = calc_cost(p2);
      if (c2 == -1) {
        continue;
      }
      for (int k = j + 1; k < N * N; ++k) {
        const std::pair<int, int> p3 = {k / N, k % N};
        if (std::abs(p1.first - p3.first) + std::abs(p1.second - p3.second) <=
                2 ||
            std::abs(p2.first - p3.first) + std::abs(p2.second - p3.second) <=
                2) {
          continue;
        }
        const int c3 = calc_cost(p3);
        if (c3 == -1) {
          continue;
        }
        ans = std::min(ans, c1 + c2 + c3);
      }
    }
  }

  std::cout << ans;

  return 0;
}