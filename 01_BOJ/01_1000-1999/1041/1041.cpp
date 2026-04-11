#include <algorithm>
#include <iostream>
#include <numeric>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  long long N;
  std::cin >> N;

  int arr[6];
  for (int i = 0; i < 6; ++i) {
    std::cin >> arr[i];
  }

  const int corner[8] = {arr[0] + arr[1] + arr[2], arr[0] + arr[1] + arr[3],
                         arr[0] + arr[2] + arr[4], arr[0] + arr[3] + arr[4],
                         arr[1] + arr[2] + arr[5], arr[1] + arr[3] + arr[5],
                         arr[2] + arr[4] + arr[5], arr[3] + arr[4] + arr[5]};
  const int min_corner = *std::min_element(corner, corner + 8);

  const int line[12] = {arr[0] + arr[1], arr[0] + arr[2], arr[0] + arr[3],
                        arr[0] + arr[4], arr[1] + arr[2], arr[1] + arr[3],
                        arr[1] + arr[5], arr[2] + arr[4], arr[2] + arr[5],
                        arr[3] + arr[4], arr[3] + arr[5], arr[4] + arr[5]};

  const int min_line = *std::min_element(line, line + 12);

  const int min_surface = *std::min_element(arr, arr + 6);

  long long ans = 0;
  if (N == 1) {
    ans = std::accumulate(arr, arr + 6, 0) - *std::max_element(arr, arr + 6);
  } else {
    ans = 4 * min_corner + (8 * N - 12) * min_line +
          (5 * N - 6) * (N - 2) * min_surface;
  }

  std::cout << ans;

  return 0;
}