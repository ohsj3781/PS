#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> routes;
std::vector<int> sets;
std::vector<int> merged_set_size;
std::vector<int> origin_merged_set_size;

void InitSet() {
    for (int i = 0; i < sets.size(); ++i) {
        sets[i] = i;
    }
    std::fill(merged_set_size.begin(), merged_set_size.end(), 1);
    return;
}

const int GetSet(const int set) {
    if (set == sets[set]) {
        return set;
    }
    return sets[set] = GetSet(sets[set]);
}

void MergeSet(int lset, int rset) {
    lset = GetSet(lset);
    rset = GetSet(rset);

    if (lset > rset) {
        std::swap(lset, rset);
    }

    sets[rset] = lset;
    merged_set_size[lset] += merged_set_size[rset];
    merged_set_size[rset] = 0;

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int V, E;
    std::cin >> V >> E;

    routes.assign(V, std::vector<int>());
    for (int i = 0; i < E; ++i) {
        int A, B;
        std::cin >> A >> B;
        --A, --B;

        routes[A].push_back(B);
        routes[B].push_back(A);
    }

    sets.assign(V, 0);
    merged_set_size.assign(V, 1);
    InitSet();

    origin_merged_set_size.assign(V, 0);

    for (int i = 0; i < V; ++i) {
        if (GetSet(i) != i) {
            continue;
        }
        std::queue<int> q;
        q.push(i);
        while (!q.empty()) {
            const int now = q.front();
            q.pop();
            for (int j = 0; j < routes[now].size(); ++j) {
                if (GetSet(now) ^ GetSet(routes[now][j])) {
                    MergeSet(now, routes[now][j]);
                    q.push(routes[now][j]);
                }
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        origin_merged_set_size[i] = merged_set_size[GetSet(i)];
    }

    std::vector<int> ans;

    for (int i = 0; i < V; ++i) {
        if (routes[i].empty()) {
            continue;
        }
        InitSet();
        std::queue<int> q;
        q.push(routes[i].front());

        while (!q.empty()) {
            const int now = q.front();
            q.pop();
            for (int j = 0; j < routes[now].size(); ++j) {
                if (routes[now][j] ^ i &&
                    GetSet(now) ^ GetSet(routes[now][j])) {
                    MergeSet(now, routes[now][j]);
                    q.push(routes[now][j]);
                }
            }
        }

        if (origin_merged_set_size[i] - 1 !=
            merged_set_size[GetSet(routes[i].front())]) {
            ans.push_back(i + 1);
        }
    }

    std::cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << " ";
    }

    return 0;
}