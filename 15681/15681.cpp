#include <iostream>
#include <vector>

std::vector<int> routes[100'001];
int dp[100'001];

const int Initdp(const int node) {
  dp[node] = 1;
  for (auto &route : routes[node]) {
    if (dp[route] != 0) {
      continue;
    }
    dp[node] += Initdp(route);
  }
  return dp[node];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, R, Q;
  std::cin >> N >> R >> Q;

  std::fill_n(dp, N + 1, 0);

  int U, V;
  for (int i = 0; i < N - 1; ++i) {
    std::cin >> U >> V;
    routes[U].push_back(V);
    routes[V].push_back(U);
  }

  Initdp(R);

  int query;
  for (int i = 0; i < Q; ++i) {
    std::cin >> query;
    std::cout << dp[query] << "\n";
  }

  return 0;
}