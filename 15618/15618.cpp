#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parent;
std::vector<std::vector<int>> children;
std::vector<int> cnt_subtree_nodes;

// const int init_tree(const int now_node) {
//   for (auto &child : children[now_node]) {
//     if (child == parent[now_node]) {
//       continue;
//     }
//     parent[child] = now_node;
//     cnt_subtree_nodes[now_node] += init_tree(child);
//   }
//   cnt_subtree_nodes[now_node] += 1;
//   return cnt_subtree_nodes[now_node];
// }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, R, Q;
  std::cin >> N >> R >> Q;
  std::cin.ignore();

  parent.assign(N + 1, 0);
  children.assign(N + 1, std::vector<int>());
  cnt_subtree_nodes.assign(N + 1, 0);

  std::string input;
  std::stringstream buffer;

  int U, V;
  for (int i = 0; i < N - 1; ++i) {
    std::getline(std::cin, input);
    buffer << input;

    buffer >> U >> V;
    buffer.clear();

    children[U].push_back(V);
    children[V].push_back(U);
  }

  //   init_tree(R);
  std::vector<int> search_sequence(N);
  search_sequence.back() = R;

  int insert_index = search_sequence.size() - 2;
  for (int i = search_sequence.size() - 1; i >= 0; --i) {
    const int now_node = search_sequence[i];
    for (auto &child : children[now_node]) {
      if (child == parent[now_node]) {
        continue;
      }
      parent[child] = now_node;
      search_sequence[insert_index--] = child;
    }
  }

  for (int i = 0; i < search_sequence.size(); ++i) {
    const int now_node = search_sequence[i];
    cnt_subtree_nodes[now_node] += 1;
    cnt_subtree_nodes[parent[now_node]] += cnt_subtree_nodes[now_node];
  }

  int query;
  for (int i = 0; i < Q; ++i) {
    std::cin >> query;
    std::cout << cnt_subtree_nodes[query] << "\n";
  }

  return 0;
}