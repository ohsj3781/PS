#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

std::vector<std::pair<long long, long long>> points;

std::istream &operator>>(std::istream &is, std::pair<long long, long long> &p) {
    is >> p.first >> p.second;
    return is;
}

const int ccw(const std::pair<long long, long long> &p0,
              const std::pair<long long, long long> &p1,
              const std::pair<long long, long long> &p2) {
    const long long calc = p0.first * p1.second + p1.first * p2.second +
                           p2.first * p0.second - p1.first * p0.second -
                           p2.first * p1.second - p0.first * p2.second;
    return calc == 0 ? 0 : calc > 0 ? 1 : -1;
}

const long long dist(const std::pair<long long, long long> &lp,
                     const std::pair<long long, long long> &rp) {
    return (lp.first - rp.first) * (lp.first - rp.first) +
           (lp.second - rp.second) * (lp.second - rp.second);
}

bool compare(const std::pair<long long, long long> &lp,
             const std::pair<long long, long long> &rp) {
    const int ccw_result = ccw(points.front(), lp, rp);

    return ccw_result == 0 ? dist(points.front(), lp) < dist(points.front(), rp)
                           : ccw_result > 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    points.assign(N, {0, 0});
    for (int i = 0; i < points.size(); ++i) {
        std::cin >> points[i];
    }

    std::sort(points.begin(), points.end());
    std::sort(points.begin() + 1, points.end(), compare);

    std::vector<std::pair<long long, long long>> ans;
    ans.push_back(points[0]);
    ans.push_back(points[1]);
    for (int i = 2; i < points.size(); ++i) {
        while (ans.size() >= 2 &&
               ccw(points[i], ans[ans.size() - 2], ans[ans.size() - 1]) <= 0) {
            ans.pop_back();
        }

        ans.push_back(points[i]);
    }

    std::cout << ans.size();

    return 0;
}