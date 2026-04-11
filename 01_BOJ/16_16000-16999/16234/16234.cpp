#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int N, L, R;
std::vector<std::pair<int, int>> MOVE = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
std::vector<std::vector<int>> matrix;
std::vector<std::vector<bool>> visited;

std::pair<int, int> operator+(const std::pair<int, int> &lp,
                              const std::pair<int, int> &rp) {
    return std::pair<int, int>(lp.first + rp.first, lp.second + rp.second);
}

const bool Moveable(const std::pair<int, int> &now,
                    const std::pair<int, int> &next) {
    if (next.first < 0 || next.first >= N || next.second < 0 ||
        next.second >= N || visited[next.first][next.second]) {
        return false;
    }

    const int num_diff = std::abs(matrix[now.first][now.second] -
                                  matrix[next.first][next.second]);

    return L <= num_diff && num_diff <= R;
}

void bfs(const std::pair<int, int> &p) {
    int cnt_people = 0;
    std::vector<std::pair<int, int>> federation;
    std::queue<std::pair<int, int>> q;

    q.push(p);
    visited[p.first][p.second] = true;

    while (!q.empty()) {
        const std::pair<int, int> now = q.front();
        q.pop();

        cnt_people += matrix[now.first][now.second];
        federation.push_back(now);

        for (int i = 0; i < MOVE.size(); ++i) {
            const std::pair<int, int> next(now + MOVE[i]);
            if (Moveable(now, next)) {
                q.push(next);
                visited[next.first][next.second] = true;
            }
        }
    }

    const int people_mean = cnt_people / federation.size();
    for (int i = 0; i < federation.size(); ++i) {
        const std::pair<int, int> &now = federation[i];
        matrix[now.first][now.second] = people_mean;
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::cin >> N >> L >> R;

    matrix.assign(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int ans = 0;
    visited.assign(N, std::vector<bool>(N, false));
    bool next_day = false;
    while (true) {
        next_day = false;
        for (int i = 0; i < N; ++i) {
            std::fill(visited[i].begin(), visited[i].end(), false);
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (visited[i][j]) {
                    continue;
                }
                const std::pair<int, int> now{i, j};
                visited[now.first][now.second] = true;

                for (int k = 0; k < MOVE.size(); ++k) {
                    const std::pair<int, int> next = (now + MOVE[k]);
                    if (Moveable(now, next)) {
                        bfs(now);
                        next_day = true;
                        break;
                    }
                }
            }
        }

        if (!next_day) {
            break;
        }
        ++ans;
    }

    std::cout << ans << "\n";

    return 0;
}