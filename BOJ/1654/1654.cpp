#include <iostream>
#include <vector>
#include <algorithm>

const int cnt_cutted_wires(const std::vector<int>& wires,const int cutted_length){
    int cnt=0;
    for(auto i=wires.begin();i!=wires.end();++i){
        cnt+=*i/cutted_length;
    }
    return cnt;
}

const int calc_maximum_wire_length(const std::vector<int>& wires,const int N){
    long long begin=1;
    long long end=*std::max_element(wires.begin(),wires.end());
    long long mid;
    long long ans=1;
    while(begin<=end){
        mid=(begin+end)/2;
        const int cutted_wires=cnt_cutted_wires(wires,mid);
        if(cutted_wires<N){
            end=mid-1;
        }
        else{
            begin=mid+1;
            ans=std::max(ans,mid);
        }
    }
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr),std::cout.tie(nullptr);
    
    int K,N;
    std::cin>>K>>N;

    std::vector<int> wires (K);
    for(auto i=wires.begin();i!=wires.end();++i){
        std::cin>>*i;
    }

    std::cout<<calc_maximum_wire_length(wires,N);

    return 0;
}