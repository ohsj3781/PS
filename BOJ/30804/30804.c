#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TYEPE 9

int main() {
  int N;
  scanf("%d", &N);

  int* arr = calloc(N, sizeof(int));
  for (int i = 0; i < N; ++i) {
    scanf("%d", arr + i);
    --arr[i];
  }

  int cnt_types[MAX_TYEPE];
  memset(cnt_types, 0, sizeof(cnt_types));
  int left = 0, right = left;

  for (; right != N; ++right) {
    ++cnt_types[arr[right]];

    int sum_types = 0;
    for (int i = 0; i < MAX_TYEPE; ++i) {
      sum_types += cnt_types[i] != 0 ? 1 : 0;
    }

    if (sum_types > 2) {
      --cnt_types[arr[left]];
      ++left;
    }
  }

  free(arr);

  printf("%d", right - left);

  return 0;
}