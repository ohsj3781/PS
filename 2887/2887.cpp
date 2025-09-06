#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> sets;

const int GetSet(const int set) {
  if (sets[set] == set) {
    return set;
  }
  return sets[set] = GetSet(sets[set]);
}

void MergeSet(const int lset, const int rset) {
  sets[lset] = rset;
  return;
}

struct Info {
  int pos;
  int index;
  const bool operator<(const Info& i) const { return this->pos < i.pos; }
  const bool operator>(const Info& i) const { return this->pos > i.pos; }
};

struct Edge {
  int value;
  int set0;
  int set1;

  const bool operator<(const Edge& e) const { return this->value < e.value; }
  const bool operator>(const Edge& e) const { return this->value > e.value; }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  sets.assign(N, 0);

  std::vector<Info> x_info(N);
  std::vector<Info> y_info(N);
  std::vector<Info> z_info(N);

  for (int i = 0; i < N; ++i) {
    std::cin >> x_info[i].pos >> y_info[i].pos >> z_info[i].pos;

    sets[i] = x_info[i].index = y_info[i].index = z_info[i].index = i;
  }

  std::sort(x_info.begin(), x_info.end(), std::less<Info>());
  std::sort(y_info.begin(), y_info.end(), std::less<Info>());
  std::sort(z_info.begin(), z_info.end(), std::less<Info>());

  std::vector<Edge> edges;
  edges.reserve(3 * N);
  for (int i = 1; i < N; ++i) {
    edges.push_back({x_info[i].pos - x_info[i - 1].pos, x_info[i].index,
                     x_info[i - 1].index});
    edges.push_back({y_info[i].pos - y_info[i - 1].pos, y_info[i].index,
                     y_info[i - 1].index});
    edges.push_back({z_info[i].pos - z_info[i - 1].pos, z_info[i].index,
                     z_info[i - 1].index});
  }
  std::sort(edges.begin(), edges.end(), std::less<Edge>());

  int cnt_tunnel = 0;
  long long ans = 0;

  for (int i = 0; i < edges.size() && cnt_tunnel < N - 1; ++i) {
    const int lset = GetSet(edges[i].set0);
    const int rset = GetSet(edges[i].set1);

    if (lset == rset) {
      continue;
    }

    ans += edges[i].value;
    MergeSet(lset, rset);
    ++cnt_tunnel;
  }

  std::cout << ans;

  return 0;
}