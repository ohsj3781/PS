#include <iostream>
#include <stack>
#include <utility>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  long long ans = 0;
  std::stack<std::pair<int, int>> stk;

  int person, cnt_same_height_people;
  for (int i = 0; i < N; ++i) {
    cnt_same_height_people = 1;
    std::cin >> person;

    while (!stk.empty() && stk.top().first <= person) {
      ans += stk.top().second;
      if (stk.top().first == person) {
        cnt_same_height_people = stk.top().second + 1;
      }
      stk.pop();
    }

    if (!stk.empty()) {
      ans++;
    }
    stk.push({person, cnt_same_height_people});
  }
  std::cout << ans;

  return 0;
}