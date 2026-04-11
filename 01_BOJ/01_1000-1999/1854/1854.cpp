#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const bool operator<(const std::pair<int, int>& lp,
                     const std::pair<int, int>& rp) {
  return lp.first < rp.first;
}

const bool operator>(const std::pair<int, int>& lp,
                     const std::pair<int, int>& rp) {
  return lp.first > rp.first;
}

std::istream& operator>>(std::istream& is, std::pair<int, int>& p) {
  is >> p.second >> p.first;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<std::pair<int, int>>> routes(n);
  for (int i = 0; i < m; ++i) {
    int start_city;
    std::pair<int, int> r;
    std::cin >> start_city >> r;
    --start_city;
    --r.second;
    routes[start_city].push_back(r);
  }

  for (int i = 0; i < routes.size(); ++i) {
    std::sort(routes[i].begin(), routes[i].end(),
              std::less<std::pair<int, int>>());
  }

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  pq.push(std::pair<int, int>(0, 0));

  std::vector<std::priority_queue<int, std::vector<int>, std::less<int>>> dist(
      n);
  dist[0].push(0);

  while (!pq.empty()) {
    const std::pair<int, int> now_r(pq.top());
    pq.pop();

    if (dist[now_r.second].top() < now_r.first) {
      continue;
    }

    for (int i = 0; i < routes[now_r.second].size(); ++i) {
      const std::pair<int, int> next_r(
          now_r.first + routes[now_r.second][i].first,
          routes[now_r.second][i].second);

      if (dist[next_r.second].size() < k) {
        dist[next_r.second].push(next_r.first);
        pq.push(next_r);
      } else if (dist[next_r.second].size() == k &&
                 dist[next_r.second].top() > next_r.first) {
        dist[next_r.second].pop();
        dist[next_r.second].push(next_r.first);
        pq.push(next_r);
      }
    }
  }

  for (int i = 0; i < dist.size(); ++i) {
    if (dist[i].size() == k) {
      std::cout << dist[i].top() << "\n";
    } else {
      std::cout << "-1\n";
    }
  }

  return 0;
}