#include <iostream>
#include <vector>
#include <algorithm>

struct point
{
    int value;
    int input_order;
};

const bool compare_point(const point &lp, const point &rp)
{

    return lp.value == rp.value ? lp.input_order < rp.input_order : lp.value < rp.value;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr), std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<point> v(N);

    int num;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> num;
        v[i] = {num, i};
    }

    std::sort(v.begin(), v.end(), compare_point);

    std::vector<int> output(N);

    int idx = 1;
    while (idx < output.size())
    {
        while (v[idx].value == v[idx - 1].value)
        {
            output[v[idx].input_order] = output[v[idx - 1].input_order];
            ++idx;
        }
        if (idx >= N)
        {
            break;
        }
        output[v[idx].input_order] = output[v[idx - 1].input_order] + 1;
        ++idx;
    }

    for (auto i = output.begin(); i != output.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    return 0;
}
