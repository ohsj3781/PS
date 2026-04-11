#include <iostream>
#include <string>
#include <vector>

std::vector<int> ans;
std::vector<int> faliure;

void SetFailure(const std::string &P) {
    const int P_length = P.length();
    faliure.assign(P_length, 0);

    faliure[0] = 0;
    int i = 1;
    int j = 0;

    while (i < P_length) {
        if (P[i] == P[j]) {
            faliure[i++] = ++j;
        } else if (j > 0) {
            j = faliure[j - 1];
        } else {
            faliure[j] = 0;
            ++i;
        }
    }

    return;
}

void KMP(const std::string &T, const std::string &P) {
    SetFailure(P);

    const int T_length = T.length();
    const int P_length = P.length();

    int i = 0, j = 0;
    while (i < T_length) {
        if (T[i] == P[j]) {
            if (j == P_length - 1) {
                ans.push_back(i - j + 1);
                ++i;
                j = faliure[j];
            } else {
                ++i, ++j;
            }
        } else {
            if (j > 0) {
                j = faliure[j - 1];
            } else {
                ++i;
            }
        }
    }

    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::string T, P;
    T.reserve(1'000'000);
    P.reserve(1'000'000);
    std::getline(std::cin, T);
    std::getline(std::cin, P);

    KMP(T, P);

    std::string output;
    output += std::to_string(ans.size()) + "\n";
    for (int i = 0; i < ans.size(); ++i) {
        output += std::to_string(ans[i]) + " ";
    }

    std::cout << output;

    return 0;
}