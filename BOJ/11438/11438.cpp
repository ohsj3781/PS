#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<int> sets;
std::vector<bool> visited;
std::vector<std::vector<int>> routes;
std::vector<std::vector<std::pair<int, int>>> queries;
std::vector<int> ans;

const int GetSet(const int now) {
    if (sets[now] == now) {
        return now;
    }
    return sets[now] = GetSet(sets[now]);
}

void UnionSet(const int left, const int right) {
    sets[GetSet(right)] = GetSet(left);
    return;
}

void Tarjan(const int now, const int parent) {
    sets[now] = now;

    for (int i = 0; i < routes[now].size(); ++i) {
        const int child = routes[now][i];
        if (child ^ parent) {
            Tarjan(child, now);
            UnionSet(now, child);
        }
    }

    visited[now] = true;

    for (int i = 0; i < queries[now].size(); ++i) {
        const auto &query = queries[now][i];
        if (visited[query.first]) {
            ans[query.second] = GetSet(query.first) + 1;
        }
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    sets.assign(N, -1);
    visited.assign(N, false);
    routes.assign(N, std::vector<int>());
    queries.assign(N, std::vector<std::pair<int, int>>());

    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;

        routes[a].push_back(b);
        routes[b].push_back(a);
    }

    int M;
    std::cin >> M;

    ans.assign(M, -1);

    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;
        queries[a].push_back({b, i});
        queries[b].push_back({a, i});
    }

    Tarjan(0, -1);

    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}