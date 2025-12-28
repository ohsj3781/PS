#include <iostream>
#include <vector>
#include <utility>

int N, M;
std::vector<std::vector<int>> matrix;

std::pair<int, int> operator+ (const std::pair<int, int>&lp, const std::pair<int, int>&rp){
    return {lp.first + rp.first, lp.second + rp.second};
}

struct Dice{
    
    std::pair<int, int> pos;
    int temp_faces[6];
    int faces[6];

    static constexpr std::pair<int, int> move[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    
    Dice(const std::pair<int, int>& pos): pos(pos){
        for(int i = 0; i < 6; ++i){
            faces[i] = 0;
        }
    }

    const int Move(const int dir){
        const std::pair<int, int> temp_pos = pos + move[dir];
        
        // Move out of range
        if(temp_pos.first < 0 || N <= temp_pos.first || temp_pos.second < 0 || M <= temp_pos.second){
            return -1;
        }

        pos = temp_pos;

        for(int i = 0; i < 6; ++i){
            temp_faces[i] = faces[i];
        }

        switch(dir){
            case 0:
                faces[0] = temp_faces[4];
                faces[2] = temp_faces[0];
                faces[4] = temp_faces[5];
                faces[5] = temp_faces[2];
            break;

            case 1:
                faces[0] = temp_faces[2];
                faces[2] = temp_faces[5];
                faces[4] = temp_faces[0];
                faces[5] = temp_faces[4];
            break;

            case 2:
                faces[0] = temp_faces[1];
                faces[1] = temp_faces[5];
                faces[3] = temp_faces[0];
                faces[5] = temp_faces[3];
            break;

            case 3:
                faces[0] = temp_faces[3];
                faces[1] = temp_faces[0];
                faces[3] = temp_faces[5];
                faces[5] = temp_faces[1];
            break;
        }

        //roll dice
        if(matrix[pos.first][pos.second] == 0){
            matrix[pos.first][pos.second] = faces[5];
        }
        else{
            faces[5] = matrix[pos.first][pos.second];
            matrix[pos.first][pos.second] = 0;
        }

        return faces[0];
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int x, y, K;
    std::cin >> N >> M >> x >> y >> K;

    matrix.assign(N, std::vector<int>());
    for(int i = 0; i < matrix.size(); ++i){
        matrix[i].assign(M,0);
        for(int j = 0; j < matrix[i].size(); ++j){
            std::cin >> matrix[i][j];
        }
    }

    Dice d({x, y});

    for(int i = 0; i < K; ++i){
        int dir;
        std::cin >> dir;

        const int output = d.Move(dir - 1);
        if(output == -1){
            continue;
        }
        
        std::cout << output << "\n";
    }

    return 0;
}