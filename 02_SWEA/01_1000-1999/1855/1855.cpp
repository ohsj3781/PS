#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

static constexpr int MAX_N = 100'000;
static constexpr int MAX_ANCESTOR = 17;

int depth[MAX_N + 1];
std::vector<int> query[MAX_N + 1];
std::vector<int> children[MAX_N + 1];
bool visited[MAX_N + 1];
int sets[MAX_N + 1];

long long ans = 0;

void Init(const int N) {
  ans = 0;
  std::fill_n(depth + 1, N, 0);
  std::fill_n(sets + 1, N, 0);
  for (int i = 1; i <= N; ++i) {
    query[i].clear();
    children[i].clear();
    sets[i] = i;
    visited[i] = false;
  }

  return;
}

int GetSet(int now_n) {
  int root = now_n;
  while (sets[root] != root) {
    root = sets[root];
  }
  while (sets[now_n] != root) {
    int next = sets[now_n];
    sets[now_n] = root;
    now_n = next;
  }
  return root;
}

void UnionSet(const int child_now, const int now_node) {
  sets[GetSet(child_now)] = GetSet(now_node);
}

void TarjanLCA(const int root) {
  struct Frame {
    int node;
    int child_idx;
  };

  std::stack<Frame> stk;
  stk.push({root, 0});

  while (!stk.empty()) {
    Frame &f = stk.top();
    const int now_n = f.node;

    if (f.child_idx < children[now_n].size()) {
      const int child_n = children[now_n][f.child_idx++];
      stk.push({child_n, 0});
    } else {
      stk.pop();

      visited[now_n] = true;

      for (int i = 0; i < query[now_n].size(); ++i) {
        const int searched_n = query[now_n][i];
        if (visited[searched_n]) {
          const int LCA = GetSet(searched_n);
          ans += depth[now_n] + depth[searched_n] - 2 * depth[LCA];
        }
      }

      if (!stk.empty()) {
        UnionSet(now_n, stk.top().node);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  depth[0] = -1;

  freopen("sample_input.txt", "r", stdin);
  int T;
  std::cin >> T;

  for (int t = 1; t <= T; ++t) {
    int N;
    std::cin >> N;

    // init
    Init(N);

    // get input
    for (int i = 2; i <= N; ++i) {
      int parent;
      std::cin >> parent;

      depth[i] = depth[parent] + 1;
      children[parent].push_back(i);
    }

    for (int i = 1; i <= N; ++i) {
      std::sort(children[i].begin(), children[i].end());
    }

    // get ans

    int last_n = 0;

    // bfs
    std::queue<int> q;
    q.push(1);

    while (!q.empty()) {
      const int now_n = q.front();
      q.pop();

      if (last_n != 0) {
        query[last_n].push_back(now_n);
        query[now_n].push_back(last_n);
      }
      for (int i = 0; i < children[now_n].size(); ++i) {
        q.push(children[now_n][i]);
      }

      last_n = now_n;
    }

    TarjanLCA(1);
    std::cout << "#" << t << " " << ans << "\n";
  }

  return 0;
}