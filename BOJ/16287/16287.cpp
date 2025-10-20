#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool weight[400'001];
int idx_0[400'001];
int idx_1[400'001];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int w, n;
    std::cin >> w >> n;

    std::vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            const int weight_sum = A[i] + A[j];
            if (!weight[weight_sum]) {
                weight[weight_sum] = true;
                idx_0[weight_sum] = i;
                idx_1[weight_sum] = j;
            }
        }
    }

    std::string ans = "NO";

    for (int i = 0; i < A.size() && ans != "YES"; ++i) {
        for (int j = 0; j < i; ++j) {
            const int target_weight = w - A[i] - A[j];
            if (target_weight < 0 || target_weight > 400'000) {
                continue;
            }
            if (weight[target_weight] && idx_0[target_weight] ^ i &&
                idx_0[target_weight] ^ j && idx_1[target_weight] ^ i &&
                idx_1[target_weight] ^ j) {
                ans = "YES";
                break;
            }
        }
    }

    std::cout << ans;

    return 0;
}