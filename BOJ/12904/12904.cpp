#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::string S, T;
    S.reserve(999);
    std::cin >> S;
    T.reserve(1000);
    std::cin >> T;

    while (T.length() > S.length()) {
        if (T.back() == 'A') {
            T.pop_back();
        } else {
            T.pop_back();
            std::reverse(T.begin(), T.end());
        }
    }

    int ans = T == S ? 1 : 0;
    std::cout << ans;

    return 0;
}