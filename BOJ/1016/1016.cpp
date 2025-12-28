#include <iostream>
#include <vector>

std::vector<long long> prime_nums;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    long long min, max;
    std::cin >> min >> max;
    
    std::vector<bool> valid_num(max - min + 1, true);

    long long index = min % 4;
    if(index > 0){
        index = 4 - index;
    }

    for(long long i = index; i < valid_num.size(); i += 4){
        valid_num[i] = false;
    }

    for(long long i = 3; i * i <= max; i+=2){
        const long long square_num = i * i;
        index = min % (square_num);
        if(index > 0){
            index = square_num - index;
        }

        for(long long j = index; j < valid_num.size(); j += square_num){
            valid_num[j] = false;
        }
    }

    int cnt = 0;
    for(int i = 0; i < valid_num.size(); ++i){
        cnt += valid_num[i] ? 1 : 0;
    }

    std::cout << cnt;

    return 0;
}