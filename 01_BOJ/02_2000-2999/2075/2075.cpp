#include <iostream>
#include <queue>
#include <vector>

struct Data {
  int num;
  int row;
  int col;
  const bool operator<(const Data& d) const { return this->num < d.num; }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<std::vector<int>> matrix(N, std::vector<int>(N));
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      std::cin >> matrix[i][j];
    }
  }

  std::priority_queue<Data> pq;
  for (int i = 0; i < matrix.back().size(); ++i) {
    pq.push({matrix.back()[i], N - 1, i});
  }

  for (int i = 0; i < N - 1; ++i) {
    const Data now(pq.top());
    pq.pop();

    pq.push({matrix[now.row - 1][now.col], now.row - 1, now.col});
  }

  std::cout << pq.top().num;

  return 0;
}