#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> wires;
struct Compare {
  const bool operator()(const int l, const int r) {
    return wires[l].second < wires[r].second;
  }
};

std::istream& operator>>(std::istream& is, std::pair<int, int>& p) {
  is >> p.first >> p.second;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  wires.assign(N, std::pair<int, int>());
  for (auto& wire : wires) {
    std::cin >> wire;
  }

  std::sort(wires.begin(), wires.end(), std::less<std::pair<int, int>>());

  std::vector<int> last_wire_index(N, -1);
  std::vector<int> dp;
  dp.reserve(N);

  dp.push_back(0);
  for (int i = 1; i < wires.size(); ++i) {
    if (wires[i].second > wires[dp.back()].second) {
      last_wire_index[i] = dp.back();
      dp.push_back(i);
    } else {
      auto iter = std::lower_bound(dp.begin(), dp.end(), i, Compare());
      *iter = i;
      last_wire_index[i] = iter == dp.begin() ? -1 : *(iter - 1);
    }
  }

  std::vector<int> longest_seq(dp.size());
  int wire_index = dp.back();
  for (int i = longest_seq.size() - 1; i >= 0; --i) {
    longest_seq[i] = wire_index;
    wire_index = last_wire_index[wire_index];
  }

  std::cout << N - longest_seq.size() << "\n";

  int seq_index = 0;
  for (int i = 0; i < wires.size(); ++i) {
    if (longest_seq[seq_index] == i) {
      ++seq_index;
      continue;
    }
    std::cout << wires[i].first << "\n";
  }
  return 0;
}