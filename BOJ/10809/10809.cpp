// Creator: OhSeungJae on 05/04/2024
#include <iostream>
#include <vector>
#include <string>


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;

    std::vector<int> v(26, -1);

    for(int i = 0; i < str.length(); i++){
        if(v[str[i] - 'a'] == -1){
            v[str[i] - 'a'] = i;
        }
    }

    for(auto i=v.begin(); i!=v.end(); i++){
        std::cout << *i << ' ';
    }  
    return 0;
}