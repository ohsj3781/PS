#include <climits>
#include <iostream>
#include <utility>
#include <vector>

constexpr int INF = INT_MAX >> 1;

std::istream& operator>>(std::istream& is, std::pair<int, int>& p) {
  is >> p.first >> p.second;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int C, N;
  std::cin >> C >> N;

  int added_max_people = 0;
  std::vector<std::pair<int, int>> cites(N);

  for (auto i = cites.begin(); i != cites.end(); ++i) {
    std::cin >> *i;
    added_max_people = std::max(added_max_people, i->second);
  }

  std::vector<int> cost(C + added_max_people, INF);
  cost.front() = 0;
  for (int i = 0; i < cost.size(); ++i) {
    for (auto j = cites.begin(); j != cites.end(); ++j) {
      if (i - j->second < 0 || cost[i - j->second] == INF) {
        continue;
      }

      cost[i] = std::min(cost[i], cost[i - j->second] + j->first);
    }
  }

  int ans = INF;
  for (auto i = cost.begin() + C; i != cost.end(); ++i) {
    ans = std::min(ans, *i);
  }
  std::cout << ans << '\n';

  return 0;
}