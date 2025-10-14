#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> weights(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> weights[i];
    }
    std::sort(weights.begin(), weights.end(), std::less<int>());

    int max_makable_num = 0;
    int ans = 0;

    for (int i = 0; i < N; ++i) {
        if (max_makable_num + 1 < weights[i]) {
            ans = max_makable_num + 1;
            break;
        } else {
            max_makable_num += weights[i];
            ans = max_makable_num + 1;
        }
    }

    std::cout << ans;

    return 0;
}