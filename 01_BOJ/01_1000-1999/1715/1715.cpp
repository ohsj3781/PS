#include <iostream>
#include <queue>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<int> v(N);
  for (auto &i : v) {
    std::cin >> i;
  }

  std::priority_queue pq(v.begin(), v.end(), std::greater<int>());

  int ans = 0;
  while (pq.size() >= 2) {
    const int n1 = pq.top();
    pq.pop();

    const int n2 = pq.top();
    pq.pop();

    const int sum = n1 + n2;
    ans += sum;
    pq.push(sum);
  }

  std::cout << ans;

  return 0;
}