#include <algorithm>
#include <iostream>
#include <utility>

static constexpr int MAX_N = 500'000;
static std::pair<int, int> a[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i;
    }

    std::sort(a, a + n);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, a[i].second - i);
    }

    std::cout << ans + 1;

    return 0;
}