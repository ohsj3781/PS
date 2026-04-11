#include <deque>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::deque<int> profits(51);

    for (int i = 0; i < N; ++i) {
        int T, P;
        std::cin >> T >> P;

        profits[1] = std::max(profits[0], profits[1]);

        profits.pop_front();
        profits.push_back(0);

        profits[T] = std::max(profits[T], profits[0] + P);
    }

    profits[1] = std::max(profits[0], profits[1]);

    profits.pop_front();

    std::cout << profits.front();

    return 0;
}