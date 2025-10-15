#include <iostream>
#include <queue>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::vector<int> usages(K);
    std::vector<std::queue<int>> item_usages_seq(K + 1);

    for (int i = 0; i < K; ++i) {
        std::cin >> usages[i];
        item_usages_seq[usages[i]].push(i);
    }

    int ans = 0;
    std::set<int> multitab;

    for (int i = 0; i < K; ++i) {
        if (multitab.find(usages[i]) != multitab.end()) {
            item_usages_seq[usages[i]].pop();
            continue;
        }
        if (multitab.size() < N) {
            multitab.insert(usages[i]);
            item_usages_seq[usages[i]].pop();
            continue;
        }
        auto selected_iter = multitab.begin();
        for (auto iter = multitab.begin(); iter != multitab.end(); ++iter) {
            if (item_usages_seq[*iter].empty()) {
                selected_iter = iter;
                break;
            }
            if (item_usages_seq[*selected_iter].front() <
                item_usages_seq[*iter].front()) {
                selected_iter = iter;
            }
        }
        multitab.erase(selected_iter);
        multitab.insert(usages[i]);
        ++ans;
        item_usages_seq[usages[i]].pop();
    }

    std::cout << ans;

    return 0;
}