#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    int C;
    for (int i = 0; i < T; ++i) {
        std::cin >> C;

        const int quater = C / 25;
        C %= 25;

        const int dime = C / 10;
        C %= 10;

        const int nickel = C / 5;
        C %= 5;

        std::cout << quater << " " << dime << " " << nickel << " " << C << "\n";
    }

    return 0;
}