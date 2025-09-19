#include <climits>
#include <iostream>

int N, M;
char matrix[10][10];
int dp[10][1024];

const bool ValidArrange(const int num, const int first) {
  for (int i = 0; i < M; ++i) {
    if (!(num & (1 << i))) {
      continue;
    }

    if (matrix[first][M - 1 - i] == 'x') {
      return false;
    }

    int shift = std::min(M - 1, i + 1);
    if (shift == i) {
      continue;
    }

    if ((num >> shift) & 1) {
      return false;
    }
  }
  return true;
}

const int MakeValidMask(const int now) {
  int mask = 0;
  for (int i = 0; i < M; ++i) {
    if ((now >> i) & 1) {
      for (int j = std::max(0, i - 1); j <= std::min(M - 1, i + 1); ++j) {
        if (i == j) {
          continue;
        }
        mask |= 1 << j;
      }
    }
  }
  return mask;
}

const int CountBits(int num) {
  int cnt = 0;
  while (num) {
    cnt += num & 1 ? 1 : 0;
    num >>= 1;
  }
  return cnt;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int C;
  std::cin >> C;

  for (int c = 0; c < C; ++c) {
    std::cin >> N >> M;

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        std::cin >> matrix[i][j];
      }
    }

    const int dp_max = 1 << M;
    for (int j = 0; j < dp_max; ++j) {
      if (ValidArrange(j, 0)) {
        dp[0][j] = CountBits(j);
      } else {
        dp[0][j] = INT_MIN;
      }
    }

    for (int i = 1; i < N; ++i) {
      for (int j = 0; j < dp_max; ++j) {
        dp[i][j] = INT_MIN;

        if (!ValidArrange(j, i)) {
          continue;
        }

        const int mask = MakeValidMask(j);
        for (int k = 0; k < dp_max; ++k) {
          if (dp[i - 1][k] == INT_MIN || mask & k) {
            continue;
          }

          dp[i][j] = std::max(dp[i][j], dp[i - 1][k] + CountBits(j));
        }
      }
    }

    int ans = 0;

    for (int i = 0; i < dp_max; ++i) {
      ans = std::max(ans, dp[N - 1][i]);
    }

    std::cout << ans << "\n";
  }

  return 0;
}