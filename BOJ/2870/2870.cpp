#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const bool compare(const std::string& ls, const std::string& rs) {
  return ls.length() == rs.length() ? ls < rs : ls.length() < rs.length();
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<std::string> ans;

  std::string input;
  for (int i = 0; i < N; ++i) {
    std::cin >> input;
    auto left = input.begin();
    auto right = input.begin();
    while (right != input.end()) {
      if (std::isdigit(*right)) {
        left = right;
        while (right != input.end() && std::isdigit(*right)) {
          ++right;
        }
        while (right - left > 1 && *left == '0') {
          ++left;
        }
        ans.push_back(input.substr(left - input.begin(), right - left));
      } else {
        ++right;
      }
    }
  }

  std::sort(ans.begin(), ans.end(), compare);

  for (auto& str : ans) {
    std::cout << str << '\n';
  }

  return 0;
}