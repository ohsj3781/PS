#include <iostream>
#include <vector>
#include <climits>

const int INF = INT_MAX;
int N;
const int start_city = 0;

void input_W(std::vector<std::vector<int>> &W)
{
    for (auto i = W.begin(); i != W.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
        {
            std::cin >> *j;
        }
    }
    return;
}

const int dfs(std::vector<std::vector<int>> &W, std::vector<std::vector<int>> &dp, const int now_city, const int visit_city)
{
    if (dp[now_city][visit_city] != INF)
    {
        return dp[now_city][visit_city];
    }

    int shortest_route = INF;
    if (visit_city == (1 << now_city))
    {
        return W[start_city][now_city] != 0 ? W[start_city][now_city] : -1;
    }

    for (int i = 0; i < N; ++i)
    {
        if (i == start_city || W[i][now_city] == 0 || (visit_city & (1 << i)) == 0)
        {
            continue;
        }
        const int calc_route = dfs(W, dp, i, visit_city ^ (1 << now_city));
        if (calc_route == -1)
        {
            continue;
        }
        shortest_route = std::min(shortest_route, calc_route + W[i][now_city]);
    }

    return dp[now_city][visit_city] = shortest_route == INF ? -1 : shortest_route;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::cin >> N;

    std::vector<std::vector<int>> W(N, std::vector<int>(N));
    input_W(W);

    std::vector<std::vector<int>> dp(N, std::vector(1 << N, INF));
    dp[start_city][0] = 0;

    std::cout << dfs(W, dp, start_city, (1 << N) - 1);

    return 0;
}