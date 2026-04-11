#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const std::pair<int, int> operator+(const std::pair<int, int> &lp,
                                    const std::pair<int, int> &rp) {
    return {lp.first + rp.first, lp.second + rp.second};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<bool>> visited;
    std::vector<std::pair<int, int>> MOVE = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    while (true) {
        int w, h;
        std::cin >> w >> h;
        if (w == 0 && h == 0) {
            break;
        }

        matrix.assign(h, std::vector<int>(w));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                std::cin >> matrix[i][j];
            }
        }

        int ans = 0;
        visited.assign(h, std::vector<bool>(w, false));

        std::queue<std::pair<int, int>> q;

        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == 0 || visited[i][j]) {
                    continue;
                }
                q.push({i, j});
                visited[i][j] = true;

                while (!q.empty()) {
                    const std::pair<int, int> now(q.front());
                    q.pop();
                    for (int k = 0; k < MOVE.size(); ++k) {
                        const std::pair<int, int> next = now + MOVE[k];
                        if (next.first < 0 || next.first >= matrix.size() ||
                            next.second < 0 ||
                            next.second >= matrix[i].size() ||
                            matrix[next.first][next.second] == 0 ||
                            visited[next.first][next.second]) {
                            continue;
                        }
                        q.push(next);
                        visited[next.first][next.second] = true;
                    }
                }
                ++ans;
            }
        }
        std::cout << ans << "\n";
    }

    return 0;
}