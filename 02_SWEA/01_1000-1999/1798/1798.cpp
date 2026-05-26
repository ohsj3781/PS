#include <bitset>
#include <iostream>
#include <vector>

static constexpr int MAX_N = 35;
static constexpr int MAX_M = 5;
static constexpr int MAX_TIME = 540;

static int times[MAX_N][MAX_N];

struct Point {
    int idx_;
    int time_;
    int s_;
};
static Point points[MAX_N];
static int hotels[MAX_N];
static int airport;
static int N, M, points_n, hotels_n;

static int ans;
static std::vector<int> ans_route;

static void DFS(const int now_idx, const int m, const int left_time,
                const int s, const std::bitset<MAX_N> &visitied,
                std::vector<int> &route) {

    if (m == M && left_time >= times[now_idx][airport] && s > ans) {
        ans = s;

        route.push_back(airport + 1);
        ans_route = route;
        route.pop_back();
    }

    bool visitible_points = false;

    for (int i = 0; i < points_n; ++i) {
        if (visitied[i]) {
            continue;
        }

        const int next_idx = points[i].idx_;
        const int calc_time = times[now_idx][next_idx] + points[i].time_;

        if (calc_time > left_time) {
            continue;
        }

        route.push_back(next_idx + 1);
        DFS(next_idx, m, left_time - calc_time, s + points[i].s_,
            visitied | std::bitset<MAX_N>(1 << i), route);
        route.pop_back();

        visitible_points = true;
    }

    if (!visitible_points && m < M) {
        for (int i = 0; i < hotels_n; ++i) {
            const int next_idx = hotels[i];

            if (times[now_idx][next_idx] > left_time) {
                continue;
            }

            route.push_back(next_idx + 1);
            DFS(next_idx, m + 1, MAX_TIME, s, visitied, route);
            route.pop_back();
        }
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    ans_route.reserve(MAX_N);

    // freopen("input.txt", "r", stdin);

    int T;
    std::cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        // Init
        points_n = 0;
        hotels_n = 0;
        airport = -1;
        ans = 0;
        ans_route.clear();

        std::cin >> N >> M;

        // Input
        for (int i = 0; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                int time;
                std::cin >> time;

                times[i][j] = times[j][i] = time;
            }
        }

        for (int i = 0; i < N; ++i) {
            char type;
            std::cin >> type;

            if (type == 'P') {
                int time, s;
                std::cin >> time >> s;

                points[points_n].idx_ = i;
                points[points_n].time_ = time;
                points[points_n].s_ = s;
                ++points_n;
            } else if (type == 'H') {
                hotels[hotels_n++] = i;
            } else {
                airport = i;
            }
        }

        // get ans
        std::vector<int> v;
        DFS(airport, 1, MAX_TIME, 0, 0, v);

        std::cout << "#" << tc << " " << ans;
        for (int i = 0; i < ans_route.size(); ++i) {
            std::cout << " " << ans_route[i];
        }
        std::cout << "\n";
    }

    return 0;
}