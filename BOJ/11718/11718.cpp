// Creator : Seung Jae Oh 02/02/2024

#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::string str;
    while (true)
    {
        std::getline(std::cin, str);
        if (str.empty())
            break;
        std::cout << str << '\n';
    }

    return 0;
}