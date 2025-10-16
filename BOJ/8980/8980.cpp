#include <algorithm>
#include <iostream>
#include <vector>

struct Package {
    int from;
    int to;
    int boxes;

    Package() : from(0), to(0), boxes(0) {}
    Package(const int from, const int to, const int boxes)
        : from(from), to(to), boxes(boxes) {}

    const bool operator<(const Package &p) const {
        return this->to != p.to ? this->to < p.to : this->from < p.from;
    }
};

std::istream &operator>>(std::istream &is, Package &p) {
    is >> p.from >> p.to >> p.boxes;
    return is;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N, C;
    std::cin >> N >> C;

    int M;
    std::cin >> M;

    std::vector<Package> packages(M);
    for (int i = 0; i < M; ++i) {
        std::cin >> packages[i];
        packages[i].from--;
        packages[i].to--;
    }
    std::sort(packages.begin(), packages.end(), std::less<Package>());

    int ans = 0;
    std::vector<int> truck(N);
    for (int i = 0; i < packages.size(); ++i) {

        int max_truck = 0;
        for (int j = packages[i].from; j < packages[i].to; ++j) {
            max_truck = std::max(truck[j], max_truck);
        }
        const int capacity = std::min(packages[i].boxes, C - max_truck);

        for (int j = packages[i].from; j < packages[i].to; ++j) {
            truck[j] += capacity;
        }
        ans += capacity;
    }

    std::cout << ans;

    return 0;
}