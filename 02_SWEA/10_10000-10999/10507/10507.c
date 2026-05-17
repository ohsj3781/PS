#include <stdio.h>

#define MAX_N (200000)

int arr[MAX_N];

int main() {
  setbuf(stdout, NULL);

  int T;
  scanf("%d", &T);

  for (int tc = 1; tc <= T; ++tc) {
    int n, p;
    scanf("%d %d", &n, &p);

    for (int i = 0; i < n; ++i) {
      scanf("%d", &arr[i]);
    }

    int ans = p + 1;
    int left_idx = 0, right_idx = 0;

    while (right_idx < n - 1) {
      const int diff =
          arr[right_idx + 1] - arr[left_idx] - right_idx - 1 + left_idx;

      if (diff <= p) {
        ++right_idx;
      } else if (left_idx < right_idx) {
        ++left_idx;
      } else {
        left_idx = ++right_idx;
      }

      ans = ans > p + right_idx - left_idx + 1 ? ans
                                               : p + right_idx - left_idx + 1;
    }
    printf("#%d %d\n", tc, ans);
  }

  return 0;
}