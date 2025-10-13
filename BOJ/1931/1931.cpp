#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct Compare {
    const bool operator()(const std::pair<int, int> &lp,
                          const std::pair<int, int> &rp) {
        return lp.second != rp.second ? lp.second < rp.second
                                      : lp.first < rp.first;
    }
};

std::istream &operator>>(std::istream &is, std::pair<int, int> &p) {
    is >> p.first >> p.second;
    return is;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> meetings(N);
    for (int i = 0; i < meetings.size(); ++i) {
        std::cin >> meetings[i];
    }
    std::sort(meetings.begin(), meetings.end(), Compare());

    int ans = 0;
    std::pair<int, int> now_meeting = {-1, -1};

    for (int i = 0; i < meetings.size(); ++i) {
        if (now_meeting.second <= meetings[i].first) {
            ++ans;
            now_meeting = meetings[i];
        }
    }
    std::cout << ans;

    return 0;
}