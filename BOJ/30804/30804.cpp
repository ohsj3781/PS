#include <iostream>

constexpr int MAX_TYPE = 9;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  int* arr = new int[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> arr[i];
    --arr[i];
  }

  int cnt_types[MAX_TYPE];
  std::fill(cnt_types, cnt_types + MAX_TYPE, 0);
  int left = 0, right = left;

  for (; right != N; ++right) {
    ++cnt_types[arr[right]];

    int sum_types = 0;
    for (int i = 0; i < MAX_TYPE; ++i) {
      sum_types += cnt_types[i] != 0 ? 1 : 0;
    }

    if (sum_types > 2) {
      --cnt_types[arr[left]];
      ++left;
    }
  }

  delete[] arr;

  std::cout << right - left;

  return 0;
}