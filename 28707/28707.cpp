#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

int N;
constexpr int BASE = 10;
constexpr int BASES[BASE] = {1,           10,           100,       1'000,
                             10'000,      100'000,      1'000'000, 10'000'000,
                             100'000'000, 1'000'000'000};
struct Inst {
  int l;
  int r;
  int c;

  const int Execute(int num) const {
    int l_value = num / BASES[N - l] % BASE;
    int r_value = num / BASES[N - r] % BASE;
    num -= l_value * BASES[N - l] + r_value * BASES[N - r];
    num += l_value * BASES[N - r] + r_value * BASES[N - l];
    return num;
  }
};

std::istream& operator>>(std::istream& is, Inst& i) {
  is >> i.l >> i.r >> i.c;
  return is;
}

const int VectorToInt(const std::vector<int>& v) {
  int value = 0;
  for (int i = 0; i < v.size(); ++i) {
    value += v[i] * BASES[N - i - 1];
  }
  return value;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> N;

  std::vector<int> v(N);
  for (auto& i : v) {
    std::cin >> i;
    --i;
  }

  int M;
  std::cin >> M;

  std::vector<Inst> insts(M);
  for (auto& inst : insts) {
    std::cin >> inst;
  }

  // m.first = vector, m.second = cost
  std::unordered_map<int, int> m;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  pq.push({0, VectorToInt(v)});
  m[VectorToInt(v)] = 0;

  std::vector<int> idle_v(v);
  std::sort(idle_v.begin(), idle_v.end(), std::less<int>());
  const int idle_value = VectorToInt(idle_v);

  while (!pq.empty() && pq.top().second != idle_value) {
    const auto now(pq.top());
    pq.pop();

    if (m[now.second] < now.first) {
      continue;
    }
    --m[now.second];

    for (const auto& inst : insts) {
      const std::pair<int, int> temp = {now.first + inst.c,
                                        inst.Execute(now.second)};

      auto iter = m.find(temp.second);

      if (iter == m.end() || iter->second > temp.first) {
        pq.push(temp);
        m[temp.second] = temp.first;
      }
    }
  }

  std::cout << (pq.empty() ? -1 : pq.top().first);

  return 0;
}