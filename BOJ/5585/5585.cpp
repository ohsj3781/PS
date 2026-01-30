#include <iostream>


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    N = 1000 - N;

    int ans = 0;
    ans += N / 500;
    N %= 500;

    ans += N / 100;
    N %= 100;

    ans += N / 50;
    N %= 50;

    ans += N /10;
    N %= 10;

    ans += N / 5;
    N %= 5;

    ans += N;

    std::cout << ans;

    return 0;
}