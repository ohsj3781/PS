#include <iostream>


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int A,B,C;
    std::cin>> A>>B>>C;

    std::cout<<A+B-C<<'\n';

    int temp_b=B;
    int base=1;

    while(temp_b){
        temp_b/=10;
        base*=10;
    }

    std::cout<<A*base+B-C;
}