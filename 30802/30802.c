#include <stdio.h>

int main() {
  int N, T, P, sum_T = 0;
  int arr[6];
  scanf("%d", &N);

  for (int i = 0; i < 6; ++i) {
    scanf("%d", arr + i);
  }

  scanf("%d %d", &T, &P);

  for (int i = 0; i < 6; ++i) {
    sum_T += (arr[i] + T - 1) / T;
  }

  printf("%d\n%d %d", sum_T, N / P, N % P);
  return 0;
}