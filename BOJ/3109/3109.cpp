#include <iostream>
#include <utility>
#include <vector>

int R, C;
std::vector<std::vector<char>> matrix;

const bool DFS(const std::pair<int, int> &pos) {
    if (pos.first < 0 || pos.first >= R || pos.second >= C ||
        matrix[pos.first][pos.second] == 'x') {
        return false;
    }

    if (pos.second == C - 1 && matrix[pos.first][pos.second] == '.') {
        matrix[pos.first][pos.second] = 'x';
        return true;
    }

    for (int i = -1; i <= 1; ++i) {
        const std::pair<int, int> next_pos(pos.first + i, pos.second + 1);

        if (DFS(next_pos)) {
            matrix[pos.first][pos.second] = 'x';
            return true;
        }
    }

    matrix[pos.first][pos.second] = 'x';
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::cin >> R >> C;

    matrix.assign(R, std::vector<char>(C));
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < R; ++i) {
        if (DFS({i, 0})) {
            ++ans;
        }
    }

    std::cout << ans;

    return 0;
}
