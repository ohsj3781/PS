#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

int N;
std::vector<int> sets;

const int GetSet(const int set) {
  if (set == sets[set]) {
    return set;
  }
  return sets[set] = GetSet(sets[set]);
}

void MergeSet(int lset, int rset) {
  lset = GetSet(lset);
  rset = GetSet(rset);
  if (lset == rset) {
    return;
  }
  if (rset > lset) {
    std::swap(lset, rset);
  }
  sets[rset] = lset;
}

struct Inst {
  int l;
  int r;
  int c;
  int set;

  const bool operator<(const Inst& i) const { return this->c < i.c; }
};

std::istream& operator>>(std::istream& is, Inst& i) {
  is >> i.l >> i.r >> i.c;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> N;
  sets.assign(N, 0);
  for (int i = 0; i < sets.size(); ++i) {
    sets[i] = i;
  }

  std::vector<int> v(N);
  for (auto& i : v) {
    std::cin >> i;
  }

  int M;
  std::cin >> M;

  std::vector<Inst> insts(M);
  for (auto& inst : insts) {
    std::cin >> inst;
    --inst.l;
    --inst.r;
    MergeSet(inst.l, inst.r);
  }
  for (auto& inst : insts) {
    inst.set = GetSet(inst.l);
  }

  std::vector<std::vector<int>> sorted_sets;
  for (int i = 0; i < sets.size(); ++i) {
    int set = GetSet(i);
    bool inserted = false;
    for (auto& sorted_set : sorted_sets) {
      if (GetSet(i) == GetSet(sorted_set.front())) {
        sorted_set.push_back(i);
        inserted = true;
        break;
      }
    }
    if (!inserted) {
      sorted_sets.push_back({i});
    }
  }
  for (auto& sorted_set : sorted_sets) {
    std::sort(sorted_set.begin(), sorted_set.end(), std::less<int>());
  }

  std::vector<std::vector<int>> sorted_value_sets(sorted_sets);
  for (int i = 0; i < sorted_value_sets.size(); ++i) {
    for (int j = 0; j < sorted_value_sets[i].size(); ++j) {
      sorted_value_sets[i][j] = v[sorted_sets[i][j]];
    }
    std::sort(sorted_value_sets[i].begin(), sorted_value_sets[i].end(),
              std::less<int>());
  }

  // valid test
  std::vector<int> test_v(v);
  for (int i = 0; i < sorted_sets.size(); ++i) {
    for (int j = 0; j < sorted_sets[i].size(); ++j) {
      test_v[sorted_sets[i][j]] = sorted_value_sets[i][j];
    }
  }
  int ans = -1;
  bool valid = true;
  for (int i = 1; i < test_v.size(); ++i) {
    if (test_v[i - 1] > test_v[i]) {
      valid = false;
      break;
    }
  }

  if (valid) {
    ans = 0;
    std::vector<std::vector<Inst>> sorted_insts(sorted_sets.size(),
                                                std::vector<Inst>());
    for (int i = 0; i < sorted_insts.size(); ++i) {
      for (auto& inst : insts) {
        if (GetSet(sorted_sets[i].front()) == GetSet(inst.set)) {
          for (int j = 0; j < sorted_insts[i].size(); ++j) {
            if (inst.l == sorted_sets[i][j]) {
              inst.l = j;
            }
            if (inst.r == sorted_sets[i][j]) {
              inst.r = j;
            }
          }
          sorted_insts[i].push_back(inst);
        }
      }
      std::sort(sorted_insts[i].begin(), sorted_insts[i].end(),
                std::less<Inst>());
    }

    std::map<std::vector<int>, int> searched;
    std::priority_queue<std::pair<int, std::vector<int>>,
                        std::vector<std::pair<int, std::vector<int>>>,
                        std::greater<std::pair<int, std::vector<int>>>>
        pq;

    for (int i = 0; i < sorted_sets.size(); ++i) {
      searched.clear();
      std::vector<int> partial_v(sorted_value_sets[i]);
      for (int j = 0; j < sorted_sets[i].size(); ++j) {
        partial_v[j] = v[sorted_sets[i][j]];
      }

      pq.push({0, partial_v});

      while (!pq.empty() && pq.top().second != sorted_value_sets[i]) {
        auto now(pq.top());
        pq.pop();

        if (searched[now.second] < now.first) {
          continue;
        }
        searched[now.second]--;

        for (const auto& sorted_inst : sorted_insts[i]) {
          std::swap(now.second[sorted_inst.l], now.second[sorted_inst.r]);

          auto iter = searched.find(now.second);
          if (iter == searched.end() ||
              iter->second > now.first + sorted_inst.c) {
            pq.push({now.first + sorted_inst.c, now.second});
            searched[now.second] = now.first + sorted_inst.c;
          }
          std::swap(now.second[sorted_inst.l], now.second[sorted_inst.r]);
        }
      }

      ans += pq.top().first;
      std::priority_queue<std::pair<int, std::vector<int>>,
                          std::vector<std::pair<int, std::vector<int>>>,
                          std::greater<std::pair<int, std::vector<int>>>>
          temp_pq;
      pq.swap(temp_pq);
    }
  }

  std::cout << ans;
  return 0;
}