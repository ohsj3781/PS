#include <iostream>
#include <queue>
#include <vector>

std::vector<int> sets;
std::vector<std::vector<int>> routes;

const int GetSet(const int set) {
    if (sets[set] == set) {
        return set;
    }
    return sets[set] = GetSet(sets[set]);
}

void MergeSet(int now_set, int next_set) {
    sets[GetSet(next_set)] = GetSet(now_set);
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    routes.assign(N, std::vector<int>());
    sets.assign(N, 0);
    for (int i = 0; i < N; ++i) {
        sets[i] = i;
    }

    for (int i = 0; i < M; ++i) {
        int node_0, node_1;
        std::cin >> node_0 >> node_1;
        --node_0;
        --node_1;

        routes[node_0].push_back(node_1);
        routes[node_1].push_back(node_0);
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (GetSet(i) != i) {
            continue;
        }

        std::queue<int> q;
        q.push(i);

        while (!q.empty()) {
            const int now = q.front();
            q.pop();

            for (int j = 0; j < routes[now].size(); ++j) {
                const int next = routes[now][j];
                if (GetSet(next) == GetSet(now)) {
                    continue;
                }

                MergeSet(now, next);
                q.push(next);
            }
        }

        ++ans;
    }

    std::cout << ans;

    return 0;
}