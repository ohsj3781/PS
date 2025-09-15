#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> A(N),B(N);
    for(auto i=A.begin(); i!=A.end(); i++)
        std::cin >> *i;

    for(auto i=B.begin(); i!=B.end(); i++)
        std::cin >> *i;

    std::sort(A.begin(), A.end());

    std::sort(B.begin(), B.end(), std::greater<int>());

    int sum = 0;
    for(int i = 0; i < N; i++)
        sum += A[i] * B[i];

    std::cout<<sum;

}