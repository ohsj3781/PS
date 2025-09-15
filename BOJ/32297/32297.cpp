#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::string str;
  str.reserve(N);
  std::cin >> str;

  bool found = str.find("gori") != std::string::npos;

  std::cout << (found ? "YES" : "NO");

  return 0;
}