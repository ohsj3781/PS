#include <iostream>
#include <queue>
#include <vector>

static constexpr int MAX_V = 1'000;
int num_predecessor[MAX_V + 1];
std::vector<int> successors[MAX_V + 1];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  //   freopen("sample_input.txt", "r", stdin);

  for (int tc = 1; tc <= 10; ++tc) {
    int V, E;
    std::cin >> V >> E;

    // Init
    std::fill_n(num_predecessor + 1, V, 0);
    for (int i = 1; i <= V; ++i) {
      successors[i].clear();
    }

    for (int i = 0; i < E; ++i) {
      int predecessor, succesor;
      std::cin >> predecessor >> succesor;

      ++num_predecessor[succesor];
      successors[predecessor].push_back(succesor);
    }

    std::queue<int> q;
    for (int i = 1; i <= V; ++i) {
      if (num_predecessor[i] == 0) {
        q.push(i);
      }
    }

    std::cout << "#" << tc;

    while (!q.empty()) {
      const int now_v = q.front();
      q.pop();

      std::cout << " " << now_v;

      for (int i = 0; i < successors[now_v].size(); ++i) {
        if (--num_predecessor[successors[now_v][i]] == 0) {
          q.push(successors[now_v][i]);
        }
      }
    }

    std::cout << "\n";
  }

  return 0;
}