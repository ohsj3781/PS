#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int T, R;
    std::cin >> T;
    std::string str;
    while (T--)
    {
        std::cin >> R >> str;
        for (auto i = str.begin(); i != str.end(); ++i)
        {
            for (int j = R; j != 0; --j)
            {
                putchar(*i);
            }
        }
        putchar('\n');
    }
}