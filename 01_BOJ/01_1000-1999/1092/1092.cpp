#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> cranes(N, 0);
    for (int i = 0; i < cranes.size(); ++i) {
        std::cin >> cranes[i];
    }
    std::sort(cranes.begin(), cranes.end());

    int M;
    std::cin >> M;

    std::vector<int> boxes(M);
    for (int i = 0; i < boxes.size(); ++i) {
        std::cin >> boxes[i];
    }
    std::sort(boxes.begin(), boxes.end(), std::greater<int>());

    int ans = -1;
    if (boxes.front() <= cranes.back()) {
        std::vector<int> cnt_cranes_time(N);
        for (int i = 0; i < boxes.size(); ++i) {
            const int cnt_cranes_time_bias =
                std::lower_bound(cranes.begin(), cranes.end(), boxes[i]) -
                cranes.begin();

            auto cnt_cranes_time_iter =
                std::min_element(cnt_cranes_time.begin() + cnt_cranes_time_bias,
                                 cnt_cranes_time.end());
            (*cnt_cranes_time_iter)++;
        }
        ans = *std::max_element(cnt_cranes_time.begin(), cnt_cranes_time.end());
    }

    std::cout << ans;

    return 0;
}