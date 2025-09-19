#include <deque>
#include <iostream>
#include <string>
#include <utility>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, L;
  std::cin >> N >> L;
  std::deque<std::pair<int, int>> dq;

  std::string output;
  for (int i = 1; i <= N; ++i) {
    int num;
    std::cin >> num;
    while (!dq.empty() && dq.front().second < i - L + 1) {
      dq.pop_front();
    }
    if (dq.empty()) {
      output += std::to_string(num) + " ";
    } else {
      output += std::to_string(std::min(num, dq.front().first)) + " ";
    }

    while (!dq.empty() && dq.back().first >= num) {
      dq.pop_back();
    }
    dq.push_back(std::pair<int, int>(num, i));

    if (i & 1024) {
      std::cout << output;
      output.clear();
    }
  }

  std::cout << output;

  return 0;
}