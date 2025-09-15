#include <iostream>
#include <vector>
static const int MAX = 10;
static const long long BASE = 1000000000;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    // dp[i][j][k][l], j 는 저장 된 숫자의 첫번째 자리, k는 해당 숫자의 자리수를 구성하는 숫자중의 최댓값, l는 해당 숫자의 자리수를 구성하는 숫자중 최솟값
    std::vector<std::vector<std::vector<std::vector<int>>>> dp(N + 1, std::vector<std::vector<std::vector<int>>>(MAX, std::vector<std::vector<int>>(MAX, std::vector<int>(MAX))));
    for (int i = 0; i < MAX; ++i)
    {
        dp[1][i][i][i] = 1;
    }

    for (int i = 2; i <= N; ++i)
    {
        for (int j = 0; j < MAX; ++j)
        {
            for (int k = 0; k < MAX; ++k)
            {
                if (k < j)
                {
                    continue;
                }
                for (int l = 0; l <= k; ++l)
                {
                    if (j < l)
                    {
                        continue;
                    }
                    if (j - 1 >= l)
                    {
                        dp[i][j][k][l] += dp[i - 1][j - 1][k][l];
                        dp[i][j][k][l] %= BASE;
                        if (j == k && j - 1 >= l)
                        {
                            dp[i][j][k][l] += dp[i - 1][j - 1][k - 1][l];
                            dp[i][j][k][l] %= BASE;
                        }
                    }

                    if (j + 1 <= k)
                    {
                        dp[i][j][k][l] += dp[i - 1][j + 1][k][l];
                        dp[i][j][k][l] %= BASE;
                        if (j == l && j + 1 <= k)
                        {
                            dp[i][j][k][l] += dp[i - 1][j + 1][k][l + 1];
                            dp[i][j][k][l] %= BASE;
                        }
                    }
                }
            }
        }
    }

    int ans=0;
    for(int i=1;i<MAX;++i){
        ans+=dp[N][i][MAX-1][0];
        ans%=BASE;
    }

    std::cout<<ans;

    return 0;
}