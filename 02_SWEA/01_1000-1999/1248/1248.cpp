#include <iostream>
#include <vector>

static constexpr int MAX_VERTICES = 10'000;
static constexpr int MAX_ANCESTORS = 14;
std::vector<int> children[MAX_VERTICES + 1];
// ancestors[i][j] = vertex i'th 2^j'th ancestors,
// if ancestors[i][j] == -1, ancestors[i][j] doesn't exist
int ancestors[MAX_VERTICES + 1][MAX_ANCESTORS];
int subtree_size[MAX_VERTICES + 1];
int depth[MAX_VERTICES + 1];

// return the number of subtree vertices
const int DFS(const int now_v, const int parent_v) {
  // set depth
  depth[now_v] = depth[parent_v] + 1;

  // set ancestors
  ancestors[now_v][0] = parent_v;
  for (int i = 1; i < MAX_ANCESTORS; ++i) {
    ancestors[now_v][i] = ancestors[ancestors[now_v][i - 1]][i - 1];
  }

  // set subtree_size and search
  subtree_size[now_v] = 1;
  for (int i = 0; i < children[now_v].size(); ++i) {
    subtree_size[now_v] += DFS(children[now_v][i], now_v);
  }

  return subtree_size[now_v];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int T;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    int V, E, v0, v1;
    std::cin >> V >> E >> v0 >> v1;

    // init
    for (int i = 1; i <= V; ++i) {
      children[i].clear();
      std::fill_n(ancestors[i], MAX_ANCESTORS, 0);
    }
    std::fill_n(subtree_size, MAX_VERTICES + 1, 0);
    std::fill_n(depth, MAX_VERTICES + 1, -1);

    // get edge info
    for (int i = 0; i < E; ++i) {
      int parent, child;
      std::cin >> parent >> child;

      children[parent].push_back(child);
    }

    // DFS
    DFS(1, 0);

    // get ans
    if (depth[v0] < depth[v1]) {
      for (int i = MAX_ANCESTORS - 1; i >= 0; --i) {
        if (depth[v0] <= depth[ancestors[v1][i]]) {
          v1 = ancestors[v1][i];
        }
      }
    } else if (depth[v0] > depth[v1]) {
      for (int i = MAX_ANCESTORS - 1; i >= 0; --i) {
        if (depth[ancestors[v0][i]] >= depth[v1]) {
          v0 = ancestors[v0][i];
        }
      }
    }

    for (int i = MAX_ANCESTORS - 1; i >= 0; --i) {
      if (ancestors[v0][i] != 0 && ancestors[v1][i] != 0 &&
          ancestors[v0][i] != ancestors[v1][i]) {
        v0 = ancestors[v0][i];
        v1 = ancestors[v1][i];
      }
    }

    int ans_node, ans_size;

    if (v0 == v1) {
      ans_node = v0;
      ans_size = subtree_size[v0];
    } else {
      ans_node = ancestors[v0][0];
      ans_size = subtree_size[ancestors[v0][0]];
    }

    std::cout << "#" << t << " " << ans_node << " " << ans_size << "\n";
  }

  return 0;
}