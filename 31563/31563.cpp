#include <iostream>
#include <vector>
class SegTree {
  int nmax;
  std::vector<long long> tree;

 public:
  explicit SegTree(const std::vector<int>& v) {
    nmax = BitCeil(v.size());
    tree.assign(nmax << 1, 0);

    for (int i = 0; i < v.size(); ++i) {
      tree[i + nmax] = v[i];
    }
    for (int i = nmax - 1; i > 0; --i) {
      tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
  }

  const long long Query(int left, int right) {
    long long left_value = 0;
    long long right_value = 0;
    for (left += nmax, right += nmax + 1; left < right;
         left >>= 1, right >>= 1) {
      if (left & 1) {
        left_value += tree[left++];
      }
      if (right & 1) {
        right_value += tree[--right];
      }
    }
    return left_value + right_value;
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

  int N, Q;
  std::cin >> N >> Q;

  std::vector<int> v(N);
  for (auto& i : v) {
    std::cin >> i;
  }

  int bias = 0;
  SegTree seg_tree(v);

  for (int i = 0; i < Q; ++i) {
    int left, right;
    std::cin >> right >> left;
    if (right == 1) {
      bias -= left;
      bias %= N;
    } else if (right == 2) {
      bias += left;
      bias %= N;
    } else  // right ==3
    {
      left += bias - 1;
      while (left < 0) {
        left += N;
      }
      while (left >= N) {
        left -= N;
      }

      std::cin >> right;
      right += bias - 1;
      while (right < 0) {
        right += N;
      }
      while (right >= N) {
        right -= N;
      }

      if (left <= right) {
        std::cout << seg_tree.Query(left, right) << '\n';
      } else {
        std::cout << seg_tree.Query(left, N - 1) + seg_tree.Query(0, right)
                  << '\n';
      }
    }
  }

  return 0;
}