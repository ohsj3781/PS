#include <cmath>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> routes;
std::vector<std::vector<int>> parents;
std::vector<int> level;

void InitTree(const int now, const int parent) {
    for (int i = 1; i < parents[now].size(); ++i) {
        parents[now][i] = parents[parents[now][i - 1]][i - 1];
    }

    for (int i = 0; i < routes[now].size(); ++i) {
        const int child = routes[now][i];
        if (routes[now][i] ^ parent) {
            level[child] = level[now] + 1;
            parents[child][0] = now;
            InitTree(child, now);
        }
    }
    return;
}

const int LCA(int left, int right) {
    if (left == 1 || right == 1) {
        return 1;
    }

    if (level[left] < level[right]) {
        std::swap(left, right);
    }

    if (level[left] != level[right]) {
        for (int i = parents[left].size() - 1; i >= 0; --i) {
            if (level[parents[left][i]] >= level[right]) {
                left = parents[left][i];
            }
        }
    }

    int ret = left;
    if (left != right) {
        for (int i = parents[left].size() - 1; i >= 0; --i) {
            if (parents[left][i] != parents[right][i]) {
                left = parents[left][i];
                right = parents[right][i];
            }
            ret = parents[left][i];
        }
    }

    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    routes.assign(N + 1, std::vector<int>());
    parents.assign(N + 1, std::vector<int>(std::floor(std::log2(N) + 1)));
    level.assign(N + 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        routes[a].push_back(b);
        routes[b].push_back(a);
    }

    level[1] = 1;
    InitTree(1, 0);

    int M;
    std::cin >> M;

    for (int i = 0; i < M; ++i) {
        int left, right;
        std::cin >> left >> right;

        std::cout << LCA(left, right) << "\n";
    }

    return 0;
}