#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

constexpr int INF = INT_MAX >> 1;

std::vector<std::vector<std::pair<int, int>>> routes;
std::vector<int> costs;
std::vector<int> visited;

std::istream &operator>>(std::istream &is, std::pair<int, int> &p) {
    is >> p.first >> p.second;
    return is;
}

struct Compare {
    const bool operator()(const std::pair<int, int> &lp,
                          const std::pair<int, int> &rp) {
        return lp.second != rp.second ? lp.second > rp.second
                                      : lp.first > rp.first;
    }
};

void DeleteFastestRoute(const int S, const int D, const int N) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        Compare>
        pq;

    costs[S] = 0;
    pq.push({S, 0});

    std::vector<std::vector<int>> last_nodes(N);

    while (!pq.empty() && pq.top().first != D) {
        const std::pair<int, int> now_r = pq.top();
        pq.pop();

        if (visited[now_r.first]) {
            continue;
        }

        visited[now_r.first] = true;

        for (int i = 0; i < routes[now_r.first].size(); ++i) {
            const std::pair<int, int> next_r = routes[now_r.first][i];

            if (costs[next_r.first] > now_r.second + next_r.second) {

                costs[next_r.first] = now_r.second + next_r.second;
                last_nodes[next_r.first].clear();
                last_nodes[next_r.first].push_back(now_r.first);

                pq.push({next_r.first, now_r.second + next_r.second});
            } else if (costs[next_r.first] == now_r.second + next_r.second) {
                last_nodes[next_r.first].push_back(now_r.first);
            }
        }
    }

    std::fill(visited.begin(), visited.end(), false);
    std::queue<int> q;
    q.push(D);

    while (!q.empty()) {
        int now_node = q.front();
        q.pop();
        if (visited[now_node]) {
            continue;
        }
        visited[now_node] = true;

        for (int i = 0; i < last_nodes[now_node].size(); ++i) {
            const int last_node = last_nodes[now_node][i];
            q.push(last_node);

            for (int j = 0; j < routes[last_node].size(); ++j) {
                if (routes[last_node][j].first == now_node) {
                    std::swap(routes[last_node][j], routes[last_node].back());
                    routes[last_node].pop_back();
                    break;
                }
            }
        }
    }

    return;
}

const int GetAnsRoute(const int S, const int D, const int N) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        Compare>
        pq;
    std::fill(costs.begin(), costs.end(), INF);
    std::fill(visited.begin(), visited.end(), false);
    costs[S] = 0;
    pq.push({S, 0});

    while (!pq.empty() && pq.top().first != D) {
        const std::pair<int, int> now_r = pq.top();
        pq.pop();

        if (visited[now_r.first]) {
            continue;
        }

        visited[now_r.first] = true;

        for (int i = 0; i < routes[now_r.first].size(); ++i) {
            const std::pair<int, int> next_r = routes[now_r.first][i];

            if (costs[next_r.first] > now_r.second + next_r.second) {
                costs[next_r.first] = now_r.second + next_r.second;

                pq.push({next_r.first, now_r.second + next_r.second});
            }
        }
    }

    return (pq.empty() ? -1 : pq.top().second);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    while (true) {
        int N, M;
        std::cin >> N >> M;
        if (N == 0 && M == 0) {
            break;
        }
        routes.assign(N, std::vector<std::pair<int, int>>());
        costs.assign(N, INF);
        visited.assign(N, false);

        int S, D;
        std::cin >> S >> D;

        for (int i = 0; i < M; ++i) {
            int U, V, P;
            std::cin >> U >> V >> P;
            routes[U].push_back({V, P});
        }

        DeleteFastestRoute(S, D, N);

        std::cout << GetAnsRoute(S, D, N) << "\n";
    }
    return 0;
}