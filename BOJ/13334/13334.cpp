#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::istream& operator>>(std::istream& is, std::pair<int, int>& p) {
  is >> p.first >> p.second;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> people(n);
  for (int i = 0; i < people.size(); ++i) {
    std::cin >> people[i];
    if (people[i].first < people[i].second) {
      std::swap(people[i].first, people[i].second);
    }
  }

  std::sort(people.begin(), people.end(), std::less<std::pair<int, int>>());

  int d;
  std::cin >> d;

  int ans = 0;
  if (!people.empty()) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for (int i = 0; i < people.size(); ++i) {
      if (people[i].first - people[i].second > d) {
        continue;
      }
      pq.push(people[i].second);

      while (!pq.empty() && people[i].first - pq.top() > d) {
        pq.pop();
      }

      ans = std::max(ans, static_cast<int>(pq.size()));
    }
  }

  std::cout << ans;

  return 0;
}