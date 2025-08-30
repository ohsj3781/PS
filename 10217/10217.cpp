#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

constexpr int INF = INT_MAX >> 1;

struct Route {
  int v;
  int c;
  int d;
  Route() : v(0), c(0), d(0) {}
  Route(const int v, const int c, const int d) : v(v), c(c), d(d) {}
  Route(const Route& r) : v(r.v), c(r.c), d(r.d) {}
  Route operator=(const Route& r) {
    this->v = r.v;
    this->c = r.c;
    this->d = r.d;
    return *this;
  }
  const bool operator<(const Route& r) const {
    return this->d != r.d   ? this->d < r.d
           : this->c != r.c ? this->c < r.c
                            : this->v > r.v;
  }

  const bool operator>(const Route& r) const {
    return this->d != r.d   ? this->d > r.d
           : this->c != r.c ? this->c > r.c
                            : this->v < r.v;
  }
};

std::istream& operator>>(std::istream& is, Route& r) {
  is >> r.v >> r.c >> r.d;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
  os << r.v << " " << r.c << " " << r.d;
  return os;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int T;
  std::cin >> T;

  for (int i = 0; i < T; ++i) {
    int N, M, K;
    std::cin >> N >> M >> K;
    std::cin.ignore();

    std::vector<std::vector<Route>> routes(N + 1);
    std::string input;
    std::stringstream buffer;
    for (int j = 0; j < K; ++j) {
      std::getline(std::cin, input);
      buffer << input;

      int u;
      Route temp_route;
      buffer >> u >> temp_route;
      buffer.clear();

      routes[u].push_back(temp_route);
    }

    for (auto& j : routes) {
      std::sort(j.begin(), j.end(), std::less<Route>());
    }

    std::vector<std::map<int, int>> dp(N + 1);
    std::priority_queue<Route, std::vector<Route>, std::greater<Route>> pq;
    pq.push(Route(1, 0, 0));

    while (!pq.empty() && pq.top().v != N) {
      Route now_r(pq.top());
      //   std::cout << "now_r : " << now_r << "\n";
      pq.pop();

      for (auto& j : routes[now_r.v]) {
        Route new_r(j.v, now_r.c + j.c, now_r.d + j.d);
        if (new_r.c > M || dp[new_r.v][new_r.c] <= new_r.d) {
          continue;
        }
        pq.push(new_r);
        for (int k = new_r.c; k < dp[now_r.v].size(); ++k) {
          if (dp[new_r.v][k] < new_r.d) {
            break;
          }
          dp[new_r.v][k] = new_r.d;
        }
      }
    }

    if (pq.empty()) {
      std::cout << "Poor KCM\n";
    } else {
      std::cout << pq.top().d << "\n";
    }
  }

  return 0;
}