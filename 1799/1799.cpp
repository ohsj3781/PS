#include <iostream>
#include <utility>
#include <vector>
int n;
std::vector<bool> diagonal_1;
std::vector<bool> diagonal_2;
std::vector<std::vector<std::pair<int, int>>> positions(2);

const int ConvertToDiagonal1(const int i, const int j) { return i + j; }

const int ConvertToDiagonal2(const int i, const int j) { return n - 1 - i + j; }

const int FindMaximumBishop(
    std::vector<std::pair<int, int>>::iterator iter,
    const std::vector<std::pair<int, int>>::const_iterator& iter_end,
    const int cnt_bishop = 0) {
  if (iter_end == iter) {
    return cnt_bishop;
  }

  int ans = 0;

  if (diagonal_1[iter->first] && diagonal_2[iter->second]) {
    diagonal_1[iter->first] = diagonal_2[iter->second] = false;
    ans = FindMaximumBishop(iter + 1, iter_end, cnt_bishop + 1);
    diagonal_1[iter->first] = diagonal_2[iter->second] = true;
  }

  return std::max(ans, FindMaximumBishop(iter + 1, iter_end, cnt_bishop));
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> n;

  int input;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> input;

      if (input) {
        positions[(i + j) & 1].push_back(std::pair<int, int>(
            ConvertToDiagonal1(i, j), ConvertToDiagonal2(i, j)));
      }
    }
  }

  diagonal_1.assign(2 * n - 1, true);
  diagonal_2.assign(2 * n - 1, true);

  std::cout << FindMaximumBishop(positions.front().begin(),
                                 positions.front().end()) +
                   FindMaximumBishop(positions.back().begin(),
                                     positions.back().end());

  return 0;
}