#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>

const int calc_type(const std::string &mbti)
{
    int type = 0;
    for (auto i = mbti.begin(); i != mbti.end(); ++i)
    {
        type <<= 1;
        type += (*i == 'E' || *i == 'S' || *i == 'T' || *i == 'J') ? 1 : 0;
    }
    return type;
}

const int count_bit_of_one(int num)
{
    int cnt_one = 0;
    do
    {
        cnt_one += num & 1;
        num >>= 1;
    } while (num > 0);
    return cnt_one;
}

const int find_ans(const std::vector<int> &mbti_type)
{
    static const int INF = INT_MAX;
    int ans = INF;
    for (auto i = mbti_type.begin(); i != mbti_type.end(); ++i)
    {
        if (*i >= 3)
        {
            return 0;
        }
    }

    for (int i = 0; i < mbti_type.size(); ++i)
    {
        if (mbti_type[i] == 0)
        {
            continue;
        }
        for (int j = i + 1; j < mbti_type.size(); ++j)
        {
            if (mbti_type[j] == 0)
            {
                continue;
            }
            for (int k = j + 1; k < mbti_type.size(); ++k)
            {
                if (mbti_type[k] == 0)
                {
                    continue;
                }
                ans = std::min(ans, count_bit_of_one(i ^ j) + count_bit_of_one(i ^ k) + count_bit_of_one(j ^ k));
            }
        }
    }

    for (int i = 0; i < mbti_type.size(); ++i)
    {
        if (mbti_type[i] != 2)
        {
            continue;
        }
        for (int j = 0; j < mbti_type.size(); ++j)
        {
            if (i == j || mbti_type[j] == 0)
            {
                continue;
            }
            ans = std::min(ans, 2 * count_bit_of_one(i ^ j));
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
        int N;
        std::cin >> N;
        std::vector<int> mbti_type(16);
        std::string mbti;
        for (int j = 0; j < N; ++j)
        {
            std::cin >> mbti;
            mbti_type[calc_type(mbti)]++;
        }
        std::cout << find_ans(mbti_type) << '\n';
    }

    return 0;
}