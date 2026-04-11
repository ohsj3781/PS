#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;

  std::vector<int64_t> prefix_sum(N + 1);
  for (int i = 1; i < prefix_sum.size(); ++i) {
    int num;
    std::cin >> num;
    prefix_sum[i] = prefix_sum[i - 1] + num;
  }

  int bias = 0;
  for (int i = 0; i < Q; ++i) {
    int left, right;
    std::cin >> right >> left;
    if (right == 1) {
      bias -= left;
      bias %= N;
    } else if (right == 2) {
      bias += left;
      bias %= N;
    } else {
      left = (left + bias) % N;
      left = left <= 0 ? left + N : left;

      std::cin >> right;
      right = (right + bias) % N;
      right = right <= 0 ? right + N : right;

      if (left <= right) {
        std::cout << prefix_sum[right] - prefix_sum[left - 1] << "\n";
      } else {
        std::cout << prefix_sum.back() - prefix_sum[left - 1] +
                         prefix_sum[right]
                  << "\n";
      }
    }
  }
  return 0;
}