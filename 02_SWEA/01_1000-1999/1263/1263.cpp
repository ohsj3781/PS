#include <algorithm>
#include <climits>
#include <iostream>

static constexpr int INF = INT_MAX >> 1;
static constexpr int MAX_N = 1000;
int matrix[MAX_N][MAX_N];
int cost_sum[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  //   freopen("input.txt", "r", stdin);

  int T;
  std::cin >> T;

  for (int tc = 1; tc <= T; ++tc) {
    int N;
    std::cin >> N;

    // init
    std::fill_n(cost_sum, N, 0);

    // get input
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        std::cin >> matrix[i][j];
      }
    }

    // calc, Floyd-Warshall
    for (int k = 0; k < N; ++k) {
      for (int i = 0; i < N; ++i) {
        if (k == i || matrix[i][k] == 0) {
          continue;
        }
        for (int j = 0; j < N; ++j) {
          if (k == j || i == j || matrix[k][j] == 0) {
            continue;
          }

          matrix[i][j] =
              matrix[i][j] == 0
                  ? matrix[i][k] + matrix[k][j]
                  : std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
        }
      }
    }

    // calc sum
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        cost_sum[i] += matrix[i][j];
        cost_sum[j] += matrix[i][j];
      }
    }

    std::cout << "#" << tc << " " << *std::min_element(cost_sum, cost_sum + N)
              << "\n";
  }

  return 0;
}