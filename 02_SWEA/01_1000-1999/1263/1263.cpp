#include <bitset>
#include <climits>
#include <iostream>
#include <sstream>

static constexpr int INF = INT_MAX;
static constexpr int MAX_N = 1000;

int N;
std::bitset<MAX_N> edges[MAX_N];

int calc_cc(int src) {
  static std::bitset<MAX_N> visited, cur, next;
  visited.reset();
  cur.reset();
  next.reset();

  visited.set(src); // src는 거리 0, 시작부터 방문 처리
  cur.set(src);     // 현재 탐색할 노드 집합 (현재 depth의 레이어)

  int cc_sum = 0, depth = 0;
  while (cur.any()) {
    ++depth;
    next.reset();

    for (int i = 0; i < N; ++i) {
      if (cur[i]) {
        next |= edges[i];
      }
    }

    next &= ~visited;
    cc_sum += next.count() * depth;
    visited |= next;
    cur = next;
  }

  return cc_sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // freopen("input.txt", "r", stdin);

  int T;
  std::cin >> T;
  std::cin.ignore();

  std::string str;
  std::stringstream buffer;

  for (int tc = 1; tc <= T; ++tc) {
    std::getline(std::cin, str);
    buffer.clear();
    buffer << str;

    buffer >> N;

    // init
    for (int i = 0; i < N; ++i) {
      edges[i].reset();
    }

    int input;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        buffer >> input;
        if (input)
          edges[i].set(j);
      }
    }

    int ans = INF;
    for (int i = 0; i < N; ++i)
      ans = std::min(ans, calc_cc(i));

    std::cout << "#" << tc << " " << ans << "\n";
  }

  return 0;
}