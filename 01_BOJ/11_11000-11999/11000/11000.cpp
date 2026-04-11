#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::istream &operator>>(std::istream &is, std::pair<int, int> &p) {
    is >> p.first >> p.second;
    return is;
}

const bool operator<(const std::pair<int, int> &lp,
                     const std::pair<int, int> &rp) {
    return lp.second != rp.second ? lp.second < rp.second : lp.first < rp.first;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> v(N);
    for (int i = 0; i < v.size(); ++i) {
        std::cin >> v[i];
    }
    std::sort(v.begin(), v.end());

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for (int i = 0; i < v.size(); ++i) {

        if (!pq.empty() && pq.top() <= v[i].first) {
            pq.pop();
        }
        pq.push(v[i].second);
    }

    std::cout << pq.size();

    return 0;
}