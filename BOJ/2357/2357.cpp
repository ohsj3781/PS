#include <climits>
#include <iostream>
#include <utility>
#include <vector>

std::istream& operator>>(std::istream& is, std::pair<int, int>& p) {
  is >> p.first >> p.second;
  return is;
}

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
  os << p.first << " " << p.second;
  return os;
}

class SegTree {
  int nmax;
  std::vector<int> min_tree;
  std::vector<int> max_tree;

 public:
  explicit SegTree(const std::vector<int>& v) {
    nmax = BitCeil(v.size());
    max_tree.assign(nmax << 1, 0);
    min_tree.assign(nmax << 1, 0);
    for (int i = 0; i < v.size(); ++i) {
      min_tree[i + nmax] = max_tree[i + nmax] = v[i];
    }
    for (int i = nmax - 1; i > 0; --i) {
      min_tree[i] = std::min(min_tree[i << 1], min_tree[i << 1 | 1]);
      max_tree[i] = std::max(max_tree[i << 1], max_tree[i << 1 | 1]);
    }
  }

  const std::pair<int, int> Query(std::pair<int, int> range) {
    std::pair<int, int> ans(INT_MAX, INT_MIN);
    for (range.first += nmax, range.second += nmax + 1;
         range.first < range.second; range.first >>= 1, range.second >>= 1) {
      if (range.first & 1) {
        ans.first = std::min(ans.first, min_tree[range.first]);
        ans.second = std::max(ans.second, max_tree[range.first]);
        range.first++;
      }
      if (range.second & 1) {
        --range.second;
        ans.first = std::min(ans.first, min_tree[range.second]);
        ans.second = std::max(ans.second, max_tree[range.second]);
      }
    }
    return ans;
  }

 private:
  const size_t BitCeil(size_t size) {
    size_t output_size = 1;
    while (size != 0) {
      output_size <<= 1;
      size >>= 1;
    }
    return output_size;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, M;
  std::cin >> N >> M;

  std::vector<int> v(N);
  for (auto& i : v) {
    std::cin >> i;
  }

  SegTree tree(v);

  std::pair<int, int> query;
  for (int i = 0; i < M; ++i) {
    std::cin >> query;
    --query.first;
    --query.second;
    std::cout << tree.Query(query) << "\n";
  }

  return 0;
}