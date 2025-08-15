#include <array>
#include <iostream>
#include <string>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::array<int, 10> arr = {0, 7, 4, 1, 8, 5, 2, 9, 6, 3};

  std::string str;
  str.reserve(13);
  std::cin >> str;

  int num = 0;
  int index = -1;
  int y = 0;

  for (auto i = str.begin(); i != str.end(); ++i) {
    if (*i == '*') {
      index = i - str.begin();
      continue;
    }
    if ((i - str.begin()) % 2 == 0) {
      num += *i - '0';
    } else {
      num += 3 * (*i - '0');
    }
  }
  y = 10 - num % 10;
  y = y == 10 ? 0 : y;
  index % 2 == 0 ? std::cout << y : std::cout << arr[y];
  return 0;
}