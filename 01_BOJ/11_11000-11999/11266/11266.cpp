#include <climits>
#include <iostream>
#include <vector>

constexpr int INF = INT_MAX >> 1;

int cnt_ans = 0;
int visit_seq;
std::vector<int> visit;
std::vector<std::vector<int>> edges;
std::vector<bool> is_cut_vertex;

const int DFS(const int now, const bool root) {
    int ret = visit[now] = visit_seq++;

    int child = 0;
    for (int i = 0; i < edges[now].size(); ++i) {
        const int next = edges[now][i];
        if (visit[next] == -1) {
            ++child;
            const int subtree = DFS(next, false);
            if (!is_cut_vertex[now] && !root && subtree >= visit[now]) {
                is_cut_vertex[now] = true;
                ++cnt_ans;
            }
            ret = std::min(ret, subtree);
        } else {
            ret = std::min(ret, visit[next]);
        }
    }
    if (!is_cut_vertex[now] && root && child > 1) {
        is_cut_vertex[now] = true;
        ++cnt_ans;
    }
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int V, E;
    std::cin >> V >> E;

    visit.assign(V, -1);
    edges.assign(V, std::vector<int>());
    is_cut_vertex.assign(V, false);

    for (int i = 0; i < E; ++i) {
        int n0, n1;
        std::cin >> n0 >> n1;
        --n0, --n1;

        edges[n0].push_back(n1);
        edges[n1].push_back(n0);
    }

    for (int i = 0; i < V; ++i) {
        if (visit[i] != -1) {
            continue;
        }
        visit_seq = 0;
        DFS(i, true);
    }

    std::cout << cnt_ans << "\n";
    for (int i = 0; i < V; ++i) {
        if (is_cut_vertex[i]) {
            std::cout << i + 1 << " ";
        }
    }

    return 0;
}