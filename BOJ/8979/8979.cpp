#include <algorithm>
#include <iostream>
#include <vector>

struct Country {
  int n;
  int g;
  int s;
  int b;

  const bool operator>(const Country& c) const {
    return this->g != c.g   ? this->g > c.g
           : this->s != c.s ? this->s > c.s
                            : this->b > c.b;
  }

  const bool operator!=(const Country& c) const {
    return this->g != c.g || this->s != c.s || this->b != c.b;
  }
};

std::istream& operator>>(std::istream& is, Country& c) {
  is >> c.n >> c.g >> c.s >> c.b;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N, K;
  std::cin >> N >> K;

  std::vector<Country> countries(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> countries[i];
  }

  std::sort(countries.begin(), countries.end(), std::greater<Country>());

  int ranking = 1;
  if (countries.front().n != K) {
    for (int i = 1; i < countries.size(); ++i) {
      if (countries[i - 1] != countries[i]) {
        ranking = i + 1;
      }

      if (countries[i].n == K) {
        break;
      }
    }
  }

  std::cout << ranking;

  return 0;
}