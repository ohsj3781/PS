#include <algorithm>
#include <climits>
#include <iostream>

static constexpr int NONE = INT_MIN;
static constexpr size_t DP_SIZE = 1'000'000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    int dp[1'000'000];
    std::fill_n(dp, DP_SIZE, NONE);
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int input;
        std::cin >> input;

        auto ptr = std::lower_bound(dp, dp + ans, input);

        if (ptr == dp + ans) {
            dp[ans++] = input;
        } else {
            *ptr = input;
        }
    }

    std::cout << ans;

    return 0;
}