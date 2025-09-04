#include <iostream>
#include <utility>
#include <vector>

int cnt_sets;
int max_set_size = 1;
std::vector<int> sets;
std::vector<int> sets_size;

const int GetSet(const int set) {
  if (sets[set] == set) {
    return set;
  }
  return sets[set] = GetSet(sets[set]);
}

void MergeSet(int lset, int rset) {
  lset = GetSet(lset);
  rset = GetSet(rset);
  if (lset == rset) {
    return;
  }

  if (rset < lset) {
    std::swap(rset, lset);
  }

  sets[rset] = lset;
  sets_size[lset] += sets_size[rset];

  --cnt_sets;
  max_set_size = std::max(max_set_size, sets_size[lset]);
  return;
}

std::istream& operator>>(std::istream& is, std::pair<int, int>& p) {
  is >> p.first >> p.second;
  return is;
}

const int CCW(const std::pair<int, int>& p0, const std::pair<int, int>& p1,
              const std::pair<int, int>& p2) {
  const int calc_0 =
      p0.first * p1.second + p1.first * p2.second + p2.first * p0.second;
  const int calc_1 =
      p1.first * p0.second + p2.first * p1.second + p0.first * p2.second;
  return calc_0 - calc_1 == 0 ? 0 : calc_0 - calc_1 > 0 ? 1 : -1;
}

struct Line {
  std::pair<int, int> p0;
  std::pair<int, int> p1;

  const bool Intersect(const Line& l) const {
    const int this_line =
        CCW(this->p0, this->p1, l.p0) * CCW(this->p0, this->p1, l.p1);
    const int other_line =
        CCW(l.p0, l.p1, this->p0) * CCW(l.p0, l.p1, this->p1);
    if (this_line == 0 && other_line == 0) {
      return l.p0 <= this->p1 && this->p0 <= l.p1;
    }
    return this_line <= 0 && other_line <= 0;
  }
};

std::istream& operator>>(std::istream& is, Line& l) {
  is >> l.p0 >> l.p1;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  cnt_sets = N;

  sets.assign(cnt_sets, 0);
  for (int i = 0; i < sets.size(); ++i) {
    sets[i] = i;
  }
  sets_size.assign(cnt_sets, 1);

  std::vector<Line> lines(N);
  for (int i = 0; i < lines.size(); ++i) {
    std::cin >> lines[i];

    if (lines[i].p0 > lines[i].p1) {
      std::swap(lines[i].p0, lines[i].p1);
    }
    for (int j = 0; j < i; ++j) {
      if (lines[i].Intersect(lines[j])) {
        MergeSet(i, j);
      }
    }
  }

  std::cout << cnt_sets << "\n" << max_set_size;

  return 0;
}