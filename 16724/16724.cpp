#include <iostream>
#include <string>
#include <utility>
#include <vector>

int N, M;

int cnt_sets;
std::vector<int> sets;

const int ConvertToSet(const std::pair<int, int>& p) {
  return p.first * M + p.second;
}

const int GetSet(const int set_index) {
  if (sets[set_index] == set_index) {
    return set_index;
  }

  return sets[set_index] = GetSet(sets[set_index]);
}

void MergeSet(int lset, int rset) {
  lset = GetSet(lset);
  rset = GetSet(rset);

  if (lset != rset) {
    sets[lset] = rset;
    cnt_sets--;
  }

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> N >> M;

  cnt_sets = N * M;
  sets.assign(N * M, 0);
  for (int i = 0; i < sets.size(); ++i) {
    sets[i] = i;
  }

  std::string input;
  for (int i = 0; i < N; ++i) {
    std::cin >> input;
    for (int j = 0; j < M; ++j) {
      const std::pair<int, int> now_pos(i, j);
      std::pair<int, int> next_pos(now_pos);
      if (input[j] == 'U') {
        next_pos.first--;
      } else if (input[j] == 'D') {
        next_pos.first++;
      } else if (input[j] == 'L') {
        next_pos.second--;
      } else {
        next_pos.second++;
      }

      MergeSet(ConvertToSet(now_pos), ConvertToSet(next_pos));
    }
  }

  std::cout << cnt_sets;

  return 0;
}