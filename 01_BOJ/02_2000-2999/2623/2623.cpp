#include <iostream>
#include <vector>
#include <string>
#include <queue>

void inputassistantPD(std::vector<std::vector<int>> &assistantPD)
{
    for (auto i = assistantPD.begin(); i != assistantPD.end(); i++)
    {
        int num;
        std::cin >> num;
        for (int j = 0; j < num; j++)
        {
            int temp;
            std::cin >> temp;
            (*i).push_back(temp);
        }
    }
}

// make a sequence of artist that satisfy assistantPD's sequence if it is possible return the sequence else return "0"
// artist's number is 1~N
const std::string find_ans(const std::vector<std::vector<int>> &assistantPD, const int N)
{
    std::string ans;
    std::vector<int> artist_list_before_this_artist(N + 1);
    std::vector<std::vector<int>> artist_list_after_this_artist(N + 1);
    for (auto i = assistantPD.begin(); i != assistantPD.end(); ++i)
    {
        for (auto j = i->begin() + 1; j != i->end(); ++j)
        {
            artist_list_before_this_artist[*j]++;
        }
        for (auto j = i->begin(); j != i->end() - 1; ++j)
        {
            artist_list_after_this_artist[*j].push_back(*(j + 1));
        }
    }

    std::queue<int> q;
    for (int i = 1; i <= N; ++i)
    {
        if (artist_list_before_this_artist[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        const int now_artist = q.front();
        q.pop();

        ans += std::to_string(now_artist) + "\n";
        for (auto i = artist_list_after_this_artist[now_artist].begin(); i != artist_list_after_this_artist[now_artist].end(); ++i)
        {
            artist_list_before_this_artist[*i]--;
            if (artist_list_before_this_artist[*i] == 0)
            {
                q.push(*i);
            }
        }
    }

    for (int i = 1; i <= N; ++i)
    {
        if (!artist_list_before_this_artist[i] == 0)
        {
            return "0";
        }
    }

    return ans; // if it is impossible return "0"
}

int main()
{

    int N, M;
    std::cin >> N >> M;
    // save sequence of assistantPD's artist
    std::vector<std::vector<int>> assistantPD(M);

    inputassistantPD(assistantPD);

    std::cout << find_ans(assistantPD, N);

    return 0;
}