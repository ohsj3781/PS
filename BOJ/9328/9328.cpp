// Creator: OhSeungJae on 01/25/2024
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

// print maximum number of document that can be taken
const int solve()
{
    int h, w;
    std::cin >> h >> w;
    // '.' : empty, '*' : wall, '$' : documnet, '#' : door, 'a'~'z' : key, 'A'~'Z' : door
    std::vector<std::vector<char>> map(h + 2, std::vector<char>(w + 2, '*'));
    for (int i = 1; i <= h; ++i)
    {
        for (int j = 1; j <= w; ++j)
        {
            std::cin >> map[i][j];
        }
    }

    std::string keys;
    std::cin >> keys;

    std::vector<bool> key(26, false);
    if (keys != "0")
    {
        for (auto i = keys.begin(); i != keys.end(); ++i)
        {
            key[*i - 'a'] = true;
        }
    }

    std::queue<std::pair<int, int>> q;
    for (int i = 1; i <= h; ++i)
    {
        if (map[i][1] != '*')
        {
            q.push({i, 1});
        }
        if (map[i][w] != '*')
        {
            q.push({i, w});
        }
    }

    for (int i = 1; i <= w; ++i)
    {
        if (map[1][i] != '*')
        {
            q.push({1, i});
        }
        if (map[h][i] != '*')
        {
            q.push({h, i});
        }
    }

    std::vector<std ::queue<std::pair<int, int>>> doors(26);
    std::vector<std::pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::vector<std::vector<bool>> visited(h + 2, std::vector<bool>(w + 2, false));

    int ans = 0;
    bool need_to_check = true;
    while (need_to_check)
    {
        need_to_check = false;
        while (!q.empty())
        {
            const auto now = q.front();
            q.pop();
            if (visited[now.first][now.second])
                continue;

            if (map[now.first][now.second] >= 'A' && map[now.first][now.second] <= 'Z' && !key[map[now.first][now.second] - 'A'])
            {
                doors[map[now.first][now.second] - 'A'].push(now);
                continue;
            }
            visited[now.first][now.second] = true;
            if (map[now.first][now.second] >= 'a' && map[now.first][now.second] <= 'z')
            {
                key[map[now.first][now.second] - 'a'] = true;
                need_to_check = true;
            }
            if (map[now.first][now.second] == '$')
            {
                ans++;
            }
            for (auto i = dir.begin(); i != dir.end(); ++i)
            {
                const auto next = std::make_pair(now.first + i->first, now.second + i->second);
                if (map[next.first][next.second] == '*')
                {
                    continue;
                }
                q.push(next);
            }
        }

        if(need_to_check)
        {
            for (auto i = doors.begin(); i != doors.end(); ++i)
            {
                while (!i->empty())
                {
                    q.push(i->front());
                    i->pop();
                }
            }
        }
    }
    return ans;
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