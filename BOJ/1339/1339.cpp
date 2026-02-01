#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int weights[26];
    std::fill_n(weights, 26, 0);

    int N;
    std::cin >> N;

    std::string input;
    for (int i = 0; i < N; ++i) {
        std::cin >> input;

        int weight = 1;
        for (int j = input.length() - 1; j >= 0; --j) {
            weights[input[j] - 'A'] += weight;
            weight *= 10;
        }
    }

    std::sort(weights, weights + 26, std::greater<int>());

    int ans = 0;
    for (int i = 9; i > 0; --i) {
        if (weights[9 - i] == 0) {
            break;
        }

        ans += i * weights[9 - i];
    }

    std::cout << ans;

    return 0;
}