#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> v(N);
    for(int i = 0; i < v.size(); ++i){
        std::cin >> v[i];
    }

    std::vector<std::vector<int>> matrix(N, std::vector<int>(N,0));
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = i + 1; j <matrix[i].size(); ++j){
            matrix[i][j] = v[i] * v[j] - v[i] -v[j];
        }
    }

    int ans = 0;
    for(int i = 0; i < v.size(); ++i){
        ans += v[i];
    }

    std::pair<int,int> pos(0,1);
    while(true){
        for(int i = 0; i < matrix.size(); ++i){
            for(int j = i + 1; j <matrix[i].size(); ++j){
                if(matrix[pos.first][pos.second] < matrix[i][j]){
                    pos.first = i;
                    pos.second = j;
                }
            }
        }

        if(matrix[pos.first][pos.second] <= 0){
            break;
        }

        ans += matrix[pos.first][pos.second];

        for(int i = 0; i < v.size(); ++i){
            matrix[pos.first][i] = matrix[pos.second][i] =
            matrix[i][pos.first] = matrix[i][pos.second] = 0;
        }
    }

    std::cout << ans;

    return 0;
    
}