#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

std::vector<int> sets;

struct Compare {
  const bool operator()(const std::tuple<int, int, int>& lt,
                        const std::tuple<int, int, int>& rt) {
    return std::get<2>(lt) < std::get<2>(rt);
  }
};

std::istream& operator>>(std::istream& is, std::tuple<int, int, int>& t) {
  is >> std::get<0>(t) >> std::get<1>(t) >> std::get<2>(t);
  return is;
}

const int GetSet(const int set) {
  if (sets[set] == set) {
    return set;
  }
  return sets[set] = GetSet(sets[set]);
}

void MergeSets(int lset, int rset) {
  lset = GetSet(lset);
  rset = GetSet(rset);

  if (lset <= rset) {
    sets[rset] = lset;
  } else {
    sets[lset] = rset;
  }
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, M;
  std::cin >> N >> M;

  int number_of_sets = N;
  sets.resize(N + 1);
  for (int i = 1; i < sets.size(); ++i) {
    sets[i] = i;
  }

  std::vector<std::tuple<int, int, int>> routes(M);
  for (auto& route : routes) {
    std::cin >> route;
  }
  std::sort(routes.begin(), routes.end(), Compare());

  int ans = 0;
  auto iter = routes.begin();
  for (auto iter = routes.begin(); iter != routes.end() && number_of_sets > 2;
       ++iter) {
    const int set_a = GetSet(std::get<0>(*iter));
    const int set_b = GetSet(std::get<1>(*iter));
    if (set_a == set_b) {
      continue;
    }
    MergeSets(set_a, set_b);
    ans += std::get<2>(*iter);
    --number_of_sets;
  }

  std::cout << ans;

  return 0;
}