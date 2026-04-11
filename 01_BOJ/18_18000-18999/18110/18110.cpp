#include <iostream>
#include <vector>
#include <cmath>

static const int MAX_DIFF = 30;

const int calc_avg(const std::vector<int> &v, const int n)
{
    if (n == 0)
    {
        return 0;
    }

    const int cutted_numbers = static_cast<const int>(std::round(0.15 * n));
    const int lower_bound=cutted_numbers+1;
    const int upper_bound=n-cutted_numbers;
    int sum=0;
    int number_sum=0;
    for(int i=1;i<v.size();++i){
        
        if(v[i-1]<lower_bound&&v[i]>=lower_bound){
            sum+=i*(v[i]-lower_bound+1);
        }
        else if(v[i-1]<upper_bound&&v[i]>=upper_bound){
            sum+=i*(upper_bound-v[i-1]);
        }
        else if(v[i]>=lower_bound&&v[i]<=upper_bound){
            sum+=i*(v[i]-v[i-1]);
        }
    }
    return std::round(static_cast<double>(sum) / (upper_bound-lower_bound+1));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> v(MAX_DIFF + 1);

    int input;
    for (int i = n; i > 0; --i)
    {
        std::cin >> input;
        v[input]++;
    }
    for(int i=1;i<v.size();++i){
        v[i]+=v[i-1];
    }

    std::cout << calc_avg(v, n);

    return 0;
}