#include <iostream>
#include <vector>
#include <queue>

void input_matrix(std::vector<std::vector<char>> &matrix)
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

const std::string find_ans(std::vector<std::vector<char>> &matrix)
{
    int ans = 0;
    std::pair<int, int> init_pair(-1, -1);
    const std::vector<std::pair<int, int>> move = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    std::pair<int, int> pos = {-1, -1};
    for (int i = 0; i < matrix.size() && pos == init_pair; ++i)
    {
        for (int j = 0; j < matrix[i].size() && pos == init_pair; ++j)
        {
            if (matrix[i][j] == 'I')
            {
                pos.first = i;
                pos.second = j;
            }
        }
    }

    std::queue<std::pair<int, int>> q;
    q.push(pos);
    matrix[pos.first][pos.second] == 'X';

    while (!q.empty())
    {
        const std::pair<int, int> now_pos(q.front());
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            std::pair<int, int> next_pos(now_pos);
            next_pos.first += move[i].first;
            next_pos.second += move[i].second;
            if (next_pos.first < 0 || next_pos.first >= matrix.size() || next_pos.second < 0 || next_pos.second >= matrix[0].size() || matrix[next_pos.first][next_pos.second] == 'X')
            {
                continue;
            }
            q.push(next_pos);
            ans += matrix[next_pos.first][next_pos.second] == 'P' ? 1 : 0;
            matrix[next_pos.first][next_pos.second] = 'X';
        }
    }

    if (ans == 0)
    {
        return "TT";
    }
    else
    {
        return std::to_string(ans);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<char>> matrix(N, std::vector<char>(M));
    input_matrix(matrix);

    std::cout << find_ans(matrix);
    return 0;
}