#include <algorithm>
#include <array>
#include <climits>
#include <iostream>

struct SegTree {
  private:
    static constexpr int INF = INT_MAX;
    int nmax;
    int tree[262'144];

  public:
    void Init(const int N) {
        nmax = BitCeil(N);
        std::fill_n(tree, nmax << 1, INF);

        for (int i = 0; i < N; ++i) {
            std::cin >> tree[i + nmax];
        }

        for (int i = nmax - 1; i > 0; --i) {
            tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
        }
        return;
    }

    const int Query(int left, int right) {
        int left_value = INF;
        int right_value = INF;
        for (left += nmax, right += nmax + 1; left < right;
             left >>= 1, right >>= 1) {
            if (left & 1) {
                left_value = std::min(left_value, tree[left++]);
            }
            if (right & 1) {
                right_value = std::min(right_value, tree[--right]);
            }
        }

        return std::min(left_value, right_value);
    }

  private:
    const int BitCeil(int size) {
        int output_size = 1;
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

    SegTree tree;
    tree.Init(N);

    for (int i = 0; i < M; ++i) {
        int left, right;
        std::cin >> left >> right;
        std::cout << tree.Query(left - 1, right - 1) << "\n";
    }

    return 0;
}