#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int n;
  std::cin >> n;
  std::cin.ignore();

  std::vector<int> a(n);
  std::vector<int> b(n);
  std::vector<int> c(n);
  std::vector<int> d(n);

  std::string input;
  std::stringstream buf;

  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, input);
    buf << input;

    buf >> a[i] >> b[i] >> c[i] >> d[i];
    buf.clear();
  }

  std::sort(a.begin(), a.end(), std::less<int>());
  std::sort(b.begin(), b.end(), std::less<int>());
  std::sort(c.begin(), c.end(), std::greater<int>());
  std::sort(d.begin(), d.end(), std::greater<int>());

  std::vector<int> left(a.size() * b.size());
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      left[i * b.size() + j] = a[i] + b[j];
    }
  }

  std::sort(left.begin(), left.end(), std::less<int>());

  std::vector<int> right(c.size() * d.size());
  for (int i = 0; i < c.size(); ++i) {
    for (int j = 0; j < d.size(); ++j) {
      right[i * d.size() + j] = c[i] + d[j];
    }
  }

  std::sort(right.begin(), right.end(), std::greater<int>());

  long long ans = 0;
  auto l = left.begin();
  auto r = right.begin();
  long long cnt_l = 1;
  long long cnt_r = 1;

  while (l != left.end() && r != right.end()) {
    if (*l + *r < 0) {
      ++l;

    } else if (*l + *r > 0) {
      ++r;
    } else {
      cnt_l = 1;
      cnt_r = 1;
      ++l;
      while (l != left.end() && *l == *(l - 1)) {
        ++cnt_l;
        ++l;
      }
      ++r;
      while (r != right.end() && *r == *(r - 1)) {
        ++cnt_r;
        ++r;
      }
      ans += cnt_l * cnt_r;
    }
  }

  std::cout << ans;

  return 0;
}