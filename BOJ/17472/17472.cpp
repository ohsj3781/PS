#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

static constexpr int INF = INT_MAX;
static constexpr int ISLAND_INDEX_BIAS = 2;
static std::vector<std::pair<int, int>> DIR = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int N, M;
std::vector<std::vector<int>> matrix;
std::vector<std::vector<int>> dists;

std::vector<int> sets;

void InitSets(const int N) {
    sets.assign(N, 0);
    for (int i = 0; i < sets.size(); ++i) {
        sets[i] = i;
    }
    return;
}

const int GetSet(const int set) {
    if (sets[set] == set) {
        return set;
    }
    return sets[set] = GetSet(sets[set]);
}

const bool MergeSet(const int lset, const int rset) {
    if (GetSet(lset) == GetSet(rset)) {
        return false;
    }

    sets[GetSet(rset)] = GetSet(lset);
    return true;
}

std::pair<int, int> operator+(const std::pair<int, int> &lp,
                              const std::pair<int, int> &rp) {
    return {lp.first + rp.first, lp.second + rp.second};
}

const bool IsOutOfRange(const std::pair<int, int> &p) {
    return p.first < 0 || p.first >= N || p.second < 0 || p.second >= M;
}

struct package {
    int island0;
    int island1;
    int dist;
    package(const int island0, const int island1, const int dist)
        : island0(island0), island1(island1), dist(dist) {}

    const bool operator<(const package &p) const { return this->dist < p.dist; }
    const bool operator>(const package &p) const { return this->dist > p.dist; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::cin >> N >> M;
    matrix.assign(N, std::vector<int>(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    // indexing each islands
    int cnt_islands = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (matrix[i][j] != 1) {
                continue;
            }

            const int island_index = cnt_islands++ + ISLAND_INDEX_BIAS;
            std::queue<std::pair<int, int>> q;
            q.push({i, j});

            matrix[i][j] = island_index;
            while (!q.empty()) {
                const std::pair<int, int> now_pos = q.front();
                q.pop();

                for (int k = 0; k < DIR.size(); ++k) {
                    const std::pair<int, int> next_pos = now_pos + DIR[k];
                    if (IsOutOfRange(next_pos) ||
                        matrix[next_pos.first][next_pos.second] != 1) {
                        continue;
                    }

                    q.push(next_pos);
                    matrix[next_pos.first][next_pos.second] = island_index;
                }
            }
        }
    }

    // find minimum distances between each islandes
    std::vector<std::vector<int>> dists(cnt_islands,
                                        std::vector<int>(cnt_islands, INF));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (matrix[i][j] == 0) {
                continue;
            }

            const int island0_idx = matrix[i][j] - ISLAND_INDEX_BIAS;

            for (int k = 0; k < DIR.size(); ++k) {
                int dist = 0;

                std::pair<int, int> last_pos(i, j);
                std::pair<int, int> now_pos = last_pos + DIR[k];

                while (!IsOutOfRange(now_pos)) {
                    if (matrix[now_pos.first][now_pos.second] == 0) {
                        ++dist;
                    }
                    if (dist > 0 &&
                        matrix[now_pos.first][now_pos.second] != 0) {
                        last_pos = now_pos;
                        break;
                    }
                    last_pos = now_pos;
                    now_pos = now_pos + DIR[k];
                }

                const int island1_idx =
                    matrix[last_pos.first][last_pos.second] - ISLAND_INDEX_BIAS;

                if (dist >= 2 && matrix[last_pos.first][last_pos.second] != 0 &&
                    island0_idx != island1_idx) {

                    dists[island0_idx][island1_idx] =
                        dists[island1_idx][island0_idx] =
                            std::min(dists[island0_idx][island1_idx], dist);
                }
            }
        }
    }

    // get ans
    int ans = 0;
    std::vector<bool> island_connected(cnt_islands, false);
    std::priority_queue<package, std::vector<package>, std::greater<package>>
        pq;
    for (int i = 0; i < cnt_islands; ++i) {
        for (int j = i + 1; j < cnt_islands; ++j) {
            if (dists[i][j] == INF) {
                continue;
            }

            pq.push(package(i, j, dists[i][j]));
        }
    }

    InitSets(cnt_islands);
    for (int i = 0; i < cnt_islands - 1; ++i) {
        while (!pq.empty() && !MergeSet(pq.top().island0, pq.top().island1)) {
            pq.pop();
        }

        if (pq.empty()) {
            ans = -1;
            break;
        }

        ans += pq.top().dist;
        pq.pop();
    }

    std::cout << ans;

    return 0;
}