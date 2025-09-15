#include <stdio.h>

int main() {
  int i = 0, num = 0, index = -1;
  char str[13];
  int arr[10] = {0, 7, 4, 1, 8, 5, 2, 9, 6, 3};
  scanf("%s", str);

  for (; i < sizeof(str) / sizeof(char); ++i) {
    if (str[i] == '*') {
      index = i;
      continue;
    }
    if (i % 2 == 0) {
      num += str[i] - '0';
    } else {
      num += 3 * (str[i] - '0');
    }
  }

  num = 10 - num % 10;
  num = num == 10 ? 0 : num;
  printf("%d", index % 2 == 0 ? num : arr[num]);

  return 0;
}