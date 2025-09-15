#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::string str;
  int index = 0;

  for (int i = 0; i < 3; ++i, ++index) {
    std::cin >> str;
    if (std::all_of(str.begin(), str.end(), ::isdigit) != 0) {
      index = std::stoi(str);
    }
  }

  if (index % 15 == 0) {
    std::cout << "FizzBuzz";
  } else if (index % 3 == 0) {
    std::cout << "Fizz";
  } else if (index % 5 == 0) {
    std::cout << "Buzz";
  } else {
    std::cout << index;
  }
  return 0;
}