#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::vector<std::string> v(12);
  for (auto& str : v) {
    str.reserve(4);
    std::cin >> str;
  }

  std::vector<std::tuple<int, int, int>> ans;

  for (int i = 0; i < v.size(); ++i) {
    for (int j = i + 1; j < v.size(); ++j) {
      for (int k = j + 1; k < v.size(); ++k) {
        bool valid = true;
        for (int l = 0; l < 4 && valid; ++l) {
          valid =
              (v[i][l] == v[j][l] && v[i][l] == v[k][l]) ||
              (v[i][l] != v[j][l] && v[i][l] != v[k][l] && v[j][l] != v[k][l]);
        }
        if (valid) {
          ans.push_back(std::make_tuple<int, int, int>(i + 1, j + 1, k + 1));
        }
      }
    }
  }

  if (ans.empty()) {
    std::cout << "no sets";
  } else {
    for (auto& i : ans) {
      std::cout << std::get<0>(i) << ' ' << std::get<1>(i) << ' '
                << std::get<2>(i) << '\n';
    }
  }
}