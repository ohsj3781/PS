#include <iostream>
#include <vector>

constexpr long long BASE = 1'000'000'007;

constexpr int N = 8;

const std::vector<std::vector<long long>> MatrixMul(
    const std::vector<std::vector<long long>>& lm,
    const std::vector<std::vector<long long>>& rm) {
  std::vector<std::vector<long long>> return_matrix(
      lm.size(), std::vector<long long>(rm.front().size()));
  for (int i = 0; i < return_matrix.size(); ++i) {
    for (int j = 0; j < return_matrix[i].size(); ++j) {
      for (int k = 0; k < rm.size(); ++k) {
        return_matrix[i][j] += lm[i][k] * rm[k][j];
        return_matrix[i][j] %= BASE;
      }
    }
  }

  return return_matrix;
}

const std::vector<std::vector<long long>> GetMultiplierMatrix(const int cnt) {
  static const std::vector<std::vector<long long>> BASE_MATRIX{
      {0, 1, 0, 1, 0, 0, 0, 0}, {1, 0, 1, 1, 0, 0, 0, 0},
      {0, 1, 0, 1, 1, 1, 0, 0}, {1, 1, 1, 0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0, 1, 1, 0}, {0, 0, 1, 1, 1, 0, 0, 1},
      {0, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 1, 0}};
  if (cnt == 1) {
    return BASE_MATRIX;
  }

  std::vector<std::vector<long long>> matrix = GetMultiplierMatrix(cnt >> 1);

  matrix = MatrixMul(matrix, matrix);
  if (cnt & 1) {
    matrix = MatrixMul(matrix, BASE_MATRIX);
  }
  return matrix;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int D;
  std::cin >> D;

  std::vector<std::vector<long long>> ans(1, std::vector<long long>(N));
  ans.front().front() = 1;

  ans = MatrixMul(ans, GetMultiplierMatrix(D));

  std::cout << ans.front().front();

  return 0;
}