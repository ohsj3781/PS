#include <iostream>
#include <string>

const int ALL=(1<<20)-1;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr),std::cout.tie(nullptr);

    unsigned int set_S=0;

    int M;
    std::cin>>M;

    unsigned int x;
    std::string user_input;
    while(M--){
        std::cin>>user_input;

        if(user_input=="all"){ 
            set_S=ALL;
        }
        else if(user_input=="empty"){
            set_S=0;
        }
        else{
            std::cin>>x;
            x-=1;
            if(user_input=="add"){
                set_S|=(1<<x);
            }
            else if(user_input=="remove"){
                set_S&=(ALL^(1<<x));
            }
            else if(user_input=="check"){
                std::cout<< ((set_S>>x) & 1) ? 1 : 0<<'\n';
            }
            else{
                set_S^=(1<<x);
            }
            //user_input==toggle
        }
    }
}