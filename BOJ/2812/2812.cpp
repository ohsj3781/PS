#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::string ans;
    ans.reserve(N);

    char buffer;
    int cnt_pop = 0;
    for (int i = 0; i < N; ++i) {

        std::cin >> buffer;

        while (cnt_pop < K && !ans.empty() && ans.back() < buffer) {
            ans.pop_back();
            ++cnt_pop;
        }
        ans.push_back(buffer);
    }

    // while (cnt_pop < K) {
    //     ans.pop_back();
    //     ++cnt_pop;
    // }

    if (cnt_pop < K) {
        ans.erase(ans.length() - (K - cnt_pop), K - cnt_pop);
    }

    std::cout << ans;

    return 0;
}