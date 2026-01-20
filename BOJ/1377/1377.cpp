#include <algorithm>
#include <iostream>
#include <vector>

static constexpr int MAX_VALUE = 1'000'000;
static constexpr int nmax = 1'048'576;

struct SegTree {
    std::vector<int> data;
    SegTree() : data(nmax << 1, 0) {}

    void Insert(const int num) {
        int index = num + nmax;
        while (index > 0) {
            data[index]++;
            index >>= 1;
        }

        return;
    }

    // return the number of bigger than number in segment tree [left + 1, right)
    const int Query(const int num) {
        int left = num + 1;
        int left_sum = 0;
        int right = MAX_VALUE + 1;
        int right_sum = 0;

        for (left += nmax, right += nmax; left < right;
             left >>= 1, right >>= 1) {
            if (left & 1) {
                left_sum += data[left++];
            }
            if (right & 1) {
                right_sum += data[--right];
            }
        }

        return left_sum + right_sum + 1;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    int ans = 0;

    SegTree tree;
    int num;
    for (int i = 0; i < n; ++i) {
        std::cin >> num;
        ans = std::max(ans, tree.Query(num));
        tree.Insert(num);
    }

    std::cout << ans;

    return 0;
}