#include <iostream>
#include <string>
#include <vector>

constexpr long long DIVIDER = 1'000'003;
using Matrix = std::vector<std::vector<long long>>;

Matrix multiplier;

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  Matrix temp_m(lhs.size(), std::vector<long long>(rhs.front().size()));

  for (int i = 0; i < temp_m.size(); ++i) {
    for (int j = 0; j < temp_m[i].size(); ++j) {
      for (int k = 0; k < rhs.size(); ++k) {
        temp_m[i][j] += lhs[i][k] * rhs[k][j];
      }
      temp_m[i][j] %= DIVIDER;
    }
  }

  return temp_m;
}

Matrix& operator*=(Matrix& lhs, const Matrix& rhs) { return lhs = lhs * rhs; }

Matrix Mul(const int T) {
  if (T == 1) {
    return multiplier;
  }
  Matrix mul = Mul(T >> 1);

  mul *= mul;
  if (T & 1) {
    mul *= multiplier;
  }

  return mul;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, S, E, T;
  std::cin >> N >> S >> E >> T;

  multiplier.assign(5 * N, std::vector<long long>(5 * N));

  for (int i = 0; i < N; ++i) {
    std::string str;
    std::cin >> str;
    for (int j = 0; j < N; ++j) {
      int num = str[j] - '0';
      if (num == 0) {
        continue;
      }
      multiplier[5 * i][5 * j + num - 1] = 1;
      for (int k = 1; k < num; ++k) {
        multiplier[5 * j + k][5 * j + k - 1] = 1;
      }
    }
  }

  Matrix ans(1, std::vector<long long>(5 * N));
  ans.front()[5 * (S - 1)] = 1;

  ans *= Mul(T);

  std::cout << ans.front()[5 * (E - 1)];

  return 0;
}