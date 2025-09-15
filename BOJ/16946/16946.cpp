#include <iostream>
#include <string>
#include <vector>

int N, M;
std::vector<std::vector<char>> matrix;
std::vector<int> sets;
std::vector<int> cnt;

const int First[4] = {1, 0, -1, 0};
const int Second[4] = {0, 1, 0, -1};

const int GetSets(const int set) {
  if (sets[set] == set) {
    return set;
  }
  return sets[set] = GetSets(sets[set]);
}

void MergeSet(const int lset, const int rset) {
  sets[lset] = rset;
  cnt[rset] += cnt[lset];
  return;
}

void SearchMatrix(const int first, const int second) {
  for (int i = 0; i < 4; ++i) {
    const int next_first = first + First[i];
    const int next_second = second + Second[i];
    if (next_first < 0 || N <= next_first || next_second < 0 ||
        M <= next_second || matrix[next_first][next_second] == '1' ||
        GetSets(first * M + second) == GetSets(next_first * M + next_second)) {
      continue;
    }
    MergeSet(GetSets(first * M + second),
             GetSets(next_first * M + next_second));
    SearchMatrix(next_first, next_second);
  }

  return;
}

const bool SearchedSet(const int set, const std::vector<int>& searched_sets) {
  bool searched = false;
  for (int searched_set : searched_sets) {
    if (GetSets(set) == GetSets(searched_set)) {
      searched = true;
      break;
    }
  }
  return searched;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> N >> M;

  matrix.assign(N, std::vector<char>(M, 0));
  sets.assign(N * M, 0);
  for (int i = 0; i < sets.size(); ++i) {
    sets[i] = i;
  }
  cnt.assign(N * M, 1);

  std::string input;
  input.reserve(M);
  for (int i = 0; i < N; ++i) {
    std::cin >> input;
    for (int j = 0; j < M; ++j) {
      matrix[i][j] = input[j];
    }
  }

  for (int first = 0; first < N; ++first) {
    std::string output;
    output.reserve(M + 1);
    for (int second = 0; second < M; ++second) {
      int ans = 0;
      if (matrix[first][second] != '0') {
        ans = 1;
        std::vector<int> searched_sets;
        searched_sets.reserve(3);

        for (int i = 0; i < 4; ++i) {
          const int next_first = first + First[i];
          const int next_second = second + Second[i];

          if (next_first < 0 || N <= next_first || next_second < 0 ||
              M <= next_second || matrix[next_first][next_second] == '1' ||
              SearchedSet(next_first * M + next_second, searched_sets)) {
            continue;
          }
          SearchMatrix(next_first, next_second);

          ans += cnt[GetSets(next_first * M + next_second)];
          searched_sets.push_back(GetSets(next_first * M + next_second));
        }
      }
      output += ans % 10 + '0';
    }
    output += "\n";
    std::cout << output;
  }

  return 0;
}