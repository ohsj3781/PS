#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 9

int main() {
  char str[MAX_LEN];
  int index = 0, i = 0, len = 0, j = 0;

  for (; i < 3; ++i, ++index) {
    scanf("%s", str);
    len = strlen(str);
    for (j = 0; j < len; ++j) {
      if (str[j] < '0' || '9' < str[j]) {
        j = -1;
        break;
      }
    }
    if (j != -1) {
      index = atoi(str);
    }
  }

  if (index % 15 == 0) {
    printf("FizzBuzz");
  } else if (index % 3 == 0) {
    printf("Fizz");
  } else if (index % 5 == 0) {
    printf("Buzz");
  } else {
    printf("%d", index);
  }

  return 0;
}