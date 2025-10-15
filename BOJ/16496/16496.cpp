#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Compare {
    const bool operator()(const std::string &ls, const std::string &rs) {
        const std::string lr = ls + rs;
        const std::string rl = rs + ls;

        return lr == rs ? true : ls > rs;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;
    std::cin.clear();

    std::vector<std::string> inputs(N);
    for (int i = 0; i < inputs.size(); ++i) {
        std::cin >> inputs[i];
    }

    std::sort(inputs.begin(), inputs.end(), Compare());

    if (inputs.front() == "0") {
        std::cout << 0;
    } else {
        for (int i = 0; i < inputs.size(); ++i) {
            std::cout << inputs[i];
        }
    }

    return 0;
}