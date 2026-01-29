#include <algorithm>
#include <climits>
#include <iostream>

constexpr int INF = INT_MAX >> 1;

int N;
int costs[20][20];
int dp[20][1 << 20];

const int dfs(const int person, const int visited) {
    if (person == N) {
        return 0;
    }

    if (dp[person][visited] != INF) {
        return dp[person][visited];
    }

    for (int i = 0; i < N; ++i) {
        if ((visited & (1 << i)) == 0) {
            continue;
        }

        const int last_visit = visited & ~(1 << i);
        dp[person][visited] =
            std::min(dp[person][visited],
                     dfs(person + 1, last_visit) + costs[person][i]);
    }

    return dp[person][visited];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> costs[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        std::fill_n(dp[i], 1 << N, INF);
    }
    std::cout << dfs(0, (1 << N) - 1);

    return 0;
}