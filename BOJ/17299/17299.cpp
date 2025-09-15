#include <iostream>
#include <vector>
#include <stack>

static const int MAX = 1'000'000;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr), std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> v(N);
    std::vector<int> cnt(MAX + 1, 0);
    for (int i = 0; i < v.size(); ++i)
    {
        int num;
        std::cin >> num;
        v[i] = num;
        cnt[num]++;
    }

    std::vector<int> ans(N, -1);
    std::stack<int> s;

    for (int i = v.size() - 1; i >= 0; --i)
    {
        while (!s.empty() && cnt[v[i]] >= cnt[s.top()])
            s.pop();

        if (!s.empty())
            ans[i] = s.top();
        s.push(v[i]);
    }

    for (auto i = ans.begin(); i != ans.end(); ++i)
    {
        std::cout << *i << ' ';
    }

    return 0;
}