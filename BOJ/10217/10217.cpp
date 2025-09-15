#include <algorithm>
#include <climits>
#include <iostream>
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
  const bool operator<(const Route& r) const { return this->c < r.c; }

  const bool operator>(const Route& r) const { return this->c > r.c; }
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

    std::vector<std::vector<Route>> routes(N);
    std::string input;
    std::stringstream buffer;
    for (int j = 0; j < K; ++j) {
      std::getline(std::cin, input);
      buffer << input;

      int u;
      Route temp_route;
      buffer >> u >> temp_route;
      buffer.clear();
      temp_route.v -= 1;
      routes[u - 1].push_back(temp_route);
    }

    for (auto& j : routes) {
      std::sort(j.begin(), j.end(), std::less<Route>());
    }

    std::vector<std::vector<int>> dp(N, std::vector<int>(M + 1, INF));
    dp[0][0] = 0;

    for (int i = 0; i <= M; ++i) {
      for (int j = 0; j < N; ++j) {
        if (dp[j][i] == INF) {
          continue;
        }
        for (auto& route : routes[j]) {
          const Route new_route(route.v, route.c + i, route.d + dp[j][i]);
          if (new_route.c > M) {
            break;
          }
          dp[new_route.v][new_route.c] =
              std::min(dp[new_route.v][new_route.c], new_route.d);
        }
      }
    }

    int ans = INF;
    for (auto i : dp.back()) {
      ans = std::min(ans, i);
    }

    if (ans == INF) {
      std::cout << "Poor KCM\n";
    } else {
      std::cout << ans << "\n";
    }
  }

  return 0;
}