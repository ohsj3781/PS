#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    int A = 2, B = 1;

    int ans = 0;
    while (500 >= A) {
        const int calc_result = A * A - B * B;
        if (calc_result < N) {
            ++A;
        } else if (calc_result > N) {
            ++B;
        } else {
            ++ans;
            ++A;
        }
    }

    std::cout << ans;

    return 0;
}