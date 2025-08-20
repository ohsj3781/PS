#include <iostream>
#include <map>
#include <utility>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int n;
  std::cin >> n;
  std::map<int, std::vector<int>> map_a;
  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    map_a[temp].push_back(i);
  }

  int m;
  std::cin >> m;
  std::map<int, std::vector<int>> map_b;
  for (int i = 0; i < m; ++i) {
    int temp;
    std::cin >> temp;
    map_b[temp].push_back(i);
  }

  std::vector<int> ans;
  std::vector<std::pair<int, int>> ans_pos;

  for (auto i = map_a.rbegin(); i != map_a.rend(); ++i) {
    if (map_b.find(i->first) == map_b.end()) {
      continue;
    }
    auto iter_a = i->second.begin();
    auto iter_b = map_b[i->first].begin();
    while (iter_a != i->second.end() && iter_b != map_b[i->first].end()) {
      if (ans_pos.empty() ||
          (ans_pos.back().first < *iter_a && ans_pos.back().second < *iter_b)) {
        ans.push_back(i->first);
        ans_pos.push_back({*iter_a, *iter_b});
      }
      if (ans_pos.back().first >= *iter_a) {
        ++iter_a;
      }
      if (ans_pos.back().second >= *iter_b) {
        ++iter_b;
      }
    }
  }

  std::cout << ans.size() << '\n';
  if (!ans.empty()) {
    for (auto i = ans.begin(); i != ans.end(); ++i) {
      std::cout << *i << ' ';
    }
  }

  return 0;
}