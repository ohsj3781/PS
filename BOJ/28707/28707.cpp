#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

int N;

constexpr int MASK = 15;
constexpr int SHIFT = 4;

struct Inst {
  int l;
  int r;
  int c;

  const int Execute(long long num) const {
    // long long l_value = num / BASES[N - l] % BASE;
    long long l_value = (num >> SHIFT * (N - l)) & MASK;
    long long r_value = (num >> SHIFT * (N - r)) & MASK;
    num -= (l_value << SHIFT * (N - l)) + (r_value << SHIFT * (N - r));
    num += (l_value << SHIFT * (N - r)) + (r_value << SHIFT * (N - l));
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
    value <<= SHIFT;
    value += v[i];
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
  std::unordered_map<long long, int> m;
  std::priority_queue<std::pair<int, long long>,
                      std::vector<std::pair<int, long long>>,
                      std::greater<std::pair<int, long long>>>
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