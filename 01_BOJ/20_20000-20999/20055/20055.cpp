#include <deque>
#include <iostream>

struct Node {
  int durability;
  bool robot;
  Node() : durability(0), robot(false) {}
  Node(const int durability, const bool robot = false)
      : durability(durability), robot(robot) {}
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, K;
  std::cin >> N >> K;

  std::deque<Node> belt(2 * N);
  for (int i = 0; i < belt.size(); ++i) {
    std::cin >> belt[i].durability;
  }

  int ans = 0;
  int cnt_zero_durability = 0;

  do {
    belt.push_front(belt.back());
    belt.pop_back();

    belt[N - 1].robot = false;
    for (int i = N - 1; i > 0; --i) {
      if (!belt[i].robot && belt[i].durability > 0 && belt[i - 1].robot) {
        belt[i].robot = true;
        belt[i - 1].robot = false;
        if (--belt[i].durability == 0) {
          ++cnt_zero_durability;
        }
      }
    }

    belt[N - 1].robot = false;

    if (!belt.front().robot && belt.front().durability > 0) {
      belt.front().robot = true;
      if (--belt.front().durability == 0) {
        ++cnt_zero_durability;
      }
    }

    ++ans;
  } while (cnt_zero_durability < K);

  std::cout << ans;

  return 0;
}