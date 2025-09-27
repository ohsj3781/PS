#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::vector<int> level;
std::vector<int> dist;
std::vector<std::vector<int>> parents;
std::vector<std::vector<std::pair<int, int>>> children;

void Init(const int now, const int parent) {
  parents[now][0] = parent;
  for (int i = 1; i < parents[now].size(); ++i) {
    parents[now][i] = parents[parents[now][i - 1]][i - 1];
  }

  for (int i = 0; i < children[now].size(); ++i) {
    std::pair<int, int>& child = children[now][i];
    if (child.first ^ parent) {
      level[child.first] = level[now] + 1;
      dist[child.first] = dist[now] + child.second;
      Init(child.first, now);
    }
  }

  return;
}

const int LCA(int left, int right) {
  if (left == 1 || right == 1) {
    return 1;
  }

  if (level[left] < level[right]) {
    std::swap(left, right);
  }

  if (level[left] != level[right]) {
    for (int i = parents[left].size() - 1; i >= 0; --i) {
      if (level[parents[left][i]] >= level[right]) {
        left = parents[left][i];
      }
    }
  }

  int ret = left;
  if (left != right) {
    for (int i = std::floor(std::log2(level[left])); i >= 0; --i) {
      if (parents[left][i] != parents[right][i]) {
        left = parents[left][i];
        right = parents[right][i];
      }

      ret = parents[left][i];
    }
  }

  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  level.assign(N + 1, 0);
  dist.assign(N + 1, 0);
  parents.assign(N + 1, std::vector<int>(std::floor(std::log2(N)) + 1, 0));
  children.assign(N + 1, std::vector<std::pair<int, int>>());

  for (int i = 0; i < N - 1; ++i) {
    int n0, n1, cost;
    std::cin >> n0 >> n1 >> cost;

    children[n0].push_back({n1, cost});
    children[n1].push_back({n0, cost});
  }

  Init(1, 0);

  int M;

  std::cin >> M;

  for (int i = 0; i < M; ++i) {
    int n0, n1;
    std::cin >> n0 >> n1;

    const int lca = LCA(n0, n1);

    std::cout << dist[n0] + dist[n1] - 2 * dist[lca] << "\n";
  }

  return 0;
}