#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct pos
{
    int x;
    int y;
    pos() : x(0), y(0) {}
    pos(const int x, const int y) : x(x), y(y) {}
    pos(const pos &p) : x(p.x), y(p.y) {}
    const pos operator=(const pos &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
};

void init_matrix(std::vector<std::vector<int>> &matrix)
{
    for (auto i = matrix.begin(); i != matrix.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
        {
            std::cin >> *j;
        }
    }
    return;
}

const bool out_of_range(const pos &p, const int n, const int m)
{
    return p.x < 0 || p.x >= m || p.y < 0 || p.y >= n;
}

const pos find_target(const std::vector<std::vector<int>> &matrix)
{
    pos temp;
    for (auto i = matrix.begin(); i != matrix.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
        {
            if (*j == 2)
            {
                temp.y = i - matrix.begin();
                temp.x = j - i->begin();
                return temp;
            }
        }
    }
}

void init_dp(const std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &dp, const int n, const int m)
{
    static const int INF = INT_MAX;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            dp[i][j] = matrix[i][j] == 1 ? INF : 0;
        }
    }
}

void solve(const std::vector<std::vector<int>> &matrix, const int n, const int m)
{
     static const int INF = INT_MAX;
    static const std::vector<int> X = {0, -1, 0, 1};
    static const std::vector<int> Y = {-1, 0, 1, 0};
    std::vector<std::vector<int>> dp(n, std::vector<int>(m));
    init_dp(matrix, dp,n,m);

    std::queue<pos> q;
    q.push(find_target(matrix));

    while (!q.empty())
    {
        const pos now_pos = q.front();
        q.pop();
        for (int i = 0; i < X.size(); ++i)
        {
            pos temp_pos(now_pos);
            temp_pos.x += X[i];
            temp_pos.y += Y[i];
            if (out_of_range(temp_pos, n, m) || matrix[temp_pos.y][temp_pos.x] == 0 || dp[temp_pos.y][temp_pos.x] <= dp[now_pos.y][now_pos.x] + 1)
            {
                continue;
            }
            dp[temp_pos.y][temp_pos.x] = dp[now_pos.y][now_pos.x] + 1;
            q.push(temp_pos);
        }
    }

    for (auto i = dp.begin(); i != dp.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
        {
            std::cout << (*j==INF ? -1 :*j) << ' ';
        }
        std::cout << '\n';
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr), std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    init_matrix(matrix);

    solve(matrix, n, m);

    return 0;
}