#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
int n;
std::vector<bool> diagonal_1;
std::vector<bool> diagonal_2;
std::vector<std::vector<std::pair<int, int>>> positions(2);

const int ConvertToDiagonal1(const int i, const int j) { return i + j; }

const int ConvertToDiagonal2(const int i, const int j) { return n - 1 - i + j; }

const int FindMaximumBishop0(std::vector<std::pair<int, int>>::iterator iter) {
  static int ans = 0;
  static int cnt_bishop = 0;
  if (positions.front().end() == iter) {
    return ans = std::max(ans, cnt_bishop);
  }

  if (diagonal_1[iter->first] && diagonal_2[iter->second]) {
    ++cnt_bishop;
    diagonal_1[iter->first] = false;
    diagonal_2[iter->second] = false;

    FindMaximumBishop0(iter + 1);

    --cnt_bishop;
    diagonal_1[iter->first] = true;
    diagonal_2[iter->second] = true;
  }

  FindMaximumBishop0(iter + 1);

  return ans;
}

const int FindMaximumBishop1(std::vector<std::pair<int, int>>::iterator iter) {
  static int ans = 0;
  static int cnt_bishop = 0;
  if (positions.back().end() == iter) {
    ans = std::max(ans, cnt_bishop);
    return ans;
  }

  if (diagonal_1[iter->first] && diagonal_2[iter->second]) {
    ++cnt_bishop;
    diagonal_1[iter->first] = diagonal_2[iter->second] = false;

    FindMaximumBishop1(iter + 1);

    --cnt_bishop;
    diagonal_1[iter->first] = diagonal_2[iter->second] = true;
  }

  FindMaximumBishop1(iter + 1);

  return ans;
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

  std::cout << FindMaximumBishop0(positions.front().begin()) +
                   FindMaximumBishop1(positions.back().begin());

  return 0;
}