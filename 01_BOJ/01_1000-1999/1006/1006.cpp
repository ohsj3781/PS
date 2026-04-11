#include <climits>
#include <iostream>

constexpr int MAX_N = 10000;
constexpr int INF = INT_MAX >> 1;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int T;
  std::cin >> T;

  int sections[2][MAX_N];
  int dp[3][MAX_N + 1];

  for (int test_case = 0; test_case < T; ++test_case) {
    int N, W;
    std::cin >> N >> W;

    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < N; ++j) {
        std::cin >> sections[i][j];
      }
    }

    int ans = INF;
    for (int i = 0; i < 4; ++i) {
      bool invalid = true;
      int value_saver[2];
      switch (i) {
        case 0:
          invalid = false;
          break;
        case 1:
          if (N >= 2 && sections[0][0] + sections[0][N - 1] <= W) {
            invalid = false;
            value_saver[0] = sections[0][0];
            value_saver[1] = sections[0][N - 1];
            sections[0][0] = sections[0][N - 1] = INF;
          }
          break;

        case 2:
          if (N >= 2 && sections[1][0] + sections[1][N - 1] <= W) {
            invalid = false;
            value_saver[0] = sections[1][0];
            value_saver[1] = sections[1][N - 1];
            sections[1][0] = sections[1][N - 1] = INF;
          }
          break;

        case 3:
          if (N >= 2 && sections[0][0] + sections[0][N - 1] <= W &&
              sections[1][0] + sections[1][N - 1] <= W) {
            invalid = false;
            sections[0][0] = sections[0][N - 1] = sections[1][0] =
                sections[1][N - 1] = INF;
          }

          break;
      }

      if (invalid) {
        continue;
      }

      dp[0][0] = dp[1][0] = dp[2][0] = 0;

      for (int j = 1; j < N + 1; ++j) {
        dp[0][j] = dp[1][j] = (j << 1) - 1;
        dp[2][j] = j << 1;

        dp[2][j] =
            std::min(dp[2][j], sections[0][j - 1] + sections[1][j - 1] <= W
                                   ? dp[2][j - 1] + 1
                                   : dp[2][j - 1] + 2);

        dp[0][j] = std::min(dp[0][j], dp[2][j - 1] + 1);
        if (j > 1 && sections[0][j - 1] + sections[0][j - 2] <= W) {
          dp[0][j] = std::min(dp[0][j], dp[1][j - 1] + 1);
        }

        dp[1][j] = std::min(dp[1][j], dp[2][j - 1] + 1);
        if (j > 1 && sections[1][j - 1] + sections[1][j - 2] <= W) {
          dp[1][j] = std::min(dp[1][j], dp[0][j - 1] + 1);
        }

        dp[2][j] = std::min(dp[2][j], dp[0][j] + 1);
        dp[2][j] = std::min(dp[2][j], dp[1][j] + 1);

        if (j > 1 && sections[0][j - 1] + sections[0][j - 2] <= W &&
            sections[1][j - 1] + sections[1][j - 2] <= W) {
          dp[2][j] = std::min(dp[2][j], dp[2][j - 2] + 2);
        }
      }

      switch (i) {
        case 0:
          ans = std::min(ans, dp[2][N]);
          break;
        case 1:
          ans = std::min(ans, dp[2][N] - 1);
          sections[0][0] = value_saver[0];
          sections[0][N - 1] = value_saver[1];
          break;
        case 2:
          ans = std::min(ans, dp[2][N] - 1);
          sections[1][0] = value_saver[0];
          sections[1][N - 1] = value_saver[1];
          break;
        case 3:
          ans = std::min(ans, dp[2][N] - 2);
          break;
      }
    }

    std::cout << ans << "\n";
  }
  return 0;
}