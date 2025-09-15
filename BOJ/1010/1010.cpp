// Creator: OhSeungJae on 01/28/2024

#include <iostream>
#include <vector>

// There is a N site in west and M site in east make bridege between them and bridege can't cross each other
// Calculate the number of possible bridge

const int dp(const int M, const int N, std::vector<std::vector<int>> &combination)
{
    if (combination[M][N] != -1)
    {
        return combination[M][N];
    }

    if (M == N || N == 0)
    {
        return combination[M][N] = 1;
    }
    return combination[M][N] = dp(M - 1, N - 1, combination) + dp(M - 1, N, combination);
}

const int solve()
{
    int N, M;
    std::cin >> N >> M;

    int ans = 0;

    int min_num = std::min(N, M);
    int max_num = std::max(N, M);

    std::vector<std::vector<int>> combination(max_num+1,std::vector<int>(min_num+1,-1));

    return dp(max_num,min_num,combination);
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i)
    {
        std::cout << solve() << '\n';
    }
    return 0;
}