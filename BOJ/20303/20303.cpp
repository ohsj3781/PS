#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

constexpr int INF = INT_MIN;

int N, M, K;
std::vector<int> candies;
std::vector<int> sets;
std::vector<int> cnt_children;

const int Getset(const int set) {
  if (set == sets[set]) {
    return set;
  }
  return sets[set] = Getset(sets[set]);
}

void MergeSet(int lset, int rset) {
  lset = Getset(lset);
  rset = Getset(rset);

  if (lset != rset) {
    sets[rset] = lset;
    candies[lset] += candies[rset];
    cnt_children[lset] += cnt_children[rset];
  }

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> N >> M >> K;

  candies.assign(N, 0);
  sets.assign(N, 0);
  for (int i = 0; i < N; ++i) {
    sets[i] = i;
  }
  cnt_children.assign(N, 1);

  for (auto& candy : candies) {
    std::cin >> candy;
  }

  int left_child, right_child;
  for (int i = 0; i < M; ++i) {
    std::cin >> left_child >> right_child;
    MergeSet(left_child - 1, right_child - 1);
  }

  std::vector<int> dp(K, INF);
  dp.front() = 0;

  for (int i = 0; i < sets.size(); ++i) {
    if (i != Getset(i)) {
      continue;
    }

    for (int cnt_people = K - 1 - cnt_children[i]; cnt_people >= 0;
         --cnt_people) {
      if (dp[cnt_people] == INF) {
        continue;
      }

      dp[cnt_people + cnt_children[i]] = std::max(
          dp[cnt_people + cnt_children[i]], dp[cnt_people] + candies[i]);
    }
  }

  std::cout << *std::max_element(dp.begin(), dp.end());

  return 0;
}