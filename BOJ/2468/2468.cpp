#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int N;
int h;
std::vector<std::vector<int>> matrix;
std::vector<std::vector<bool>> visited;
std::vector<std::pair<int, int>> MOVE = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

std::pair<int, int> operator+(const std::pair<int, int> &lp,
                              const std::pair<int, int> &rp) {
    return std::pair<int, int>(lp.first + rp.first, lp.second + rp.second);
}

const bool Moveable(const std::pair<int, int> &now) {
    return 0 <= now.first && now.first < N && 0 <= now.second &&
           now.second < N && matrix[now.first][now.second] > h &&
           !visited[now.first][now.second];
}

void BFS(const std::pair<int, int> &p) {
    std::queue<std::pair<int, int>> q;
    q.push(p);
    visited[p.first][p.second] = true;

    while (!q.empty()) {
        const std::pair<int, int> now = q.front();
        q.pop();

        for (int i = 0; i < MOVE.size(); ++i) {
            const std::pair<int, int> next(now + MOVE[i]);
            if (Moveable(next)) {
                visited[next.first][next.second] = true;
                q.push(next);
            }
        }
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int max_h = 1, min_h = 100;

    std::cin >> N;
    matrix.assign(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> matrix[i][j];
            max_h = std::max(max_h, matrix[i][j]);
            min_h = std::min(min_h, matrix[i][j]);
        }
    }
    visited.assign(N, std::vector<bool>(N, false));

    int ans = 1;
    for (h = min_h; h < max_h; ++h) {
        int cnt_lands = 0;

        for (int i = 0; i < N; ++i) {
            std::fill(visited[i].begin(), visited[i].end(), false);
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] <= h || visited[i][j]) {
                    continue;
                }
                const std::pair<int, int> now(i, j);
                visited[now.first][now.second] = true;

                for (int k = 0; k < MOVE.size(); ++k) {
                    const std::pair<int, int> next(now + MOVE[k]);
                    if (Moveable(next)) {
                        BFS(now);
                        break;
                    }
                }
                ++cnt_lands;
            }
        }

        ans = std::max(ans, cnt_lands);
    }

    std::cout << ans;

    return 0;
}