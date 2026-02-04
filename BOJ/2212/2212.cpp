#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::vector<int> sensors(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> sensors[i];
    }
    std::sort(sensors.begin(), sensors.end());

    std::vector<int> dists;
    dists.reserve(N - 1);

    for (int i = 0; i < sensors.size() - 1; ++i) {
        const int dist = sensors[i + 1] - sensors[i];
        dists.push_back(dist);
    }
    std::sort(dists.begin(), dists.end());

    int ans = 0;
    if (dists.size() > K - 1) {
        for (int i = 0; i < dists.size() - (K - 1); ++i) {
            ans += dists[i];
        }
    }

    std::cout << ans;

    return 0;
}