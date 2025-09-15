#include <iostream>
#include <vector>
#include <climits>

static const int MAX_HEIGHT = 256;
static const int INF = INT_MAX;

void init_ground_height(const int N, const int M, std::vector<int> &ground_height)
{
    int n;
    for (int i = N * M; i > 0; --i)
    {
        std::cin >> n;
        ++ground_height[n];
    }
    return;
}

void solution(const std::vector<int> &ground_height, const int B)
{
    int sol_time = INF;
    int ground_level = -1;
    for (int i = 0; i <= MAX_HEIGHT; ++i)
    {
        int temp_B=B;
        int time = 0;
        for (int j = ground_height.size() - 1; j >= 0; --j)
        {
            const int the_number_of_blocks=std::abs(j-i)*ground_height[j];
            temp_B += j>=i ? the_number_of_blocks : -the_number_of_blocks;
            time += j >= i ? 2 * the_number_of_blocks : the_number_of_blocks;
        }
        if (temp_B>=0 && time <= sol_time)
        {
            sol_time = time;
            ground_level = i;
        }
    }

    std::cout << sol_time<<' '<<ground_level;
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N, M, B;
    std::cin >> N >> M >> B;

    std::vector<int> ground_height(MAX_HEIGHT + 1);
    init_ground_height(N, M, ground_height);

    solution(ground_height, B);

    return 0;
}