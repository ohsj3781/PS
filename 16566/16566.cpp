#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> indexes;

const int GetIndex(const int index) {
  return indexes[index] == index ? index
                                 : indexes[index] = GetIndex(indexes[index]);
}

void MergeIndex(const int l_index, const int r_index) {
  if (r_index < indexes.size()) {
    indexes[GetIndex(l_index)] = GetIndex(r_index);
  }
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, M, K;
  std::cin >> N >> M >> K;

  std::vector<bool> valid_num(N + 1);
  int num;
  for (int i = 0; i < M; ++i) {
    std::cin >> num;
    valid_num[num] = true;
  }

  std::vector<int> v;
  v.reserve(M);
  for (int i = 0; i < valid_num.size() && v.size() < M; ++i) {
    if (valid_num[i]) {
      v.push_back(i);
    }
  }

  indexes.assign(v.size(), 0);
  for (int i = 0; i < indexes.size(); ++i) {
    indexes[i] = i;
  }

  int query;
  for (int i = 0; i < K; ++i) {
    std::cin >> query;

    const int index =
        GetIndex(std::upper_bound(v.begin(), v.end(), query) - v.begin());
    std::cout << v[index] << "\n";
    MergeIndex(index, index + 1);
  }

  return 0;
}