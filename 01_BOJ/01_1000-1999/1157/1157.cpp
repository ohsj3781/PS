#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    const int START = 'A';
    const int END = 'Z';    
    std::string str;
    std::cin >> str;
    
    std::vector<int> cnt(END - START + 1);
    for (auto i = str.begin(); i != str.end(); ++i)
    {
        cnt[std::toupper(*i) - START]++;
    }

    int max_idx = 0;
    bool overlap = false;
    for (int i = 1; i < cnt.size(); ++i)
    {
        overlap = cnt[max_idx] == cnt[i] ? true : cnt[max_idx] < cnt[i] ? false : overlap;
        max_idx = cnt[max_idx]<cnt[i] ? i : max_idx;                    
    }

    const char ans = max_idx + START;

    std::cout << (overlap ? '?' : ans);
    return 0;
}