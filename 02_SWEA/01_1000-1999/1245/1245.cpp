#include <algorithm>
#include <iomanip>
#include <iostream>

int N;
static constexpr int MAX_N = 10;

struct Object {
  double x;
  double w;

  const double GetF(const double x) const {
    double f = w / ((this->x - x) * (this->x - x));
    return this->x > x ? f : -f;
  }

  bool operator<(const Object &o) const { return this->x < o.x; }
};

Object arr[MAX_N];

const double GetAns(const double lx, const double rx) {
  double left = lx;
  double right = rx;
  double mid;
  while (right > left + 1e-12) {
    mid = left + (right - left) / 2.0;

    double f = 0.0;
    for (int i = 0; i < N; ++i) {
      f += arr[i].GetF(mid);
    }

    if (f < 0.0) {
      left = mid;
    } else {
      right = mid;
    }
  }

  return mid;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cout << std::fixed << std::setprecision(10);

  // freopen("input.txt", "r", stdin);

  int t;
  std::cin >> t;
  for (int tc = 1; tc <= t; ++tc) {
    std::cin >> N;

    // GetInput
    for (int i = 0; i < N; ++i) {
      std::cin >> arr[i].x;
    }
    for (int i = 0; i < N; ++i) {
      std::cin >> arr[i].w;
    }
    // std::sort(arr, arr + N, std::less<Object>());

    // Get Ans
    std::cout << "#" << tc;
    for (int i = 0; i < N - 1; ++i) {
      std::cout << " " << GetAns(arr[i].x, arr[i + 1].x);
    }

    std::cout << "\n";
  }

  return 0;
}