#include <iostream>
#include <vector>

std::vector<int> empty_gates;

const int GetEmptyGate(const int gate) {
  if (empty_gates[gate] == gate) {
    return gate;
  }
  return empty_gates[gate] = GetEmptyGate(empty_gates[gate]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int G, P;
  std::cin >> G >> P;

  empty_gates.assign(G + 1, 0);
  for (int i = 0; i < empty_gates.size(); ++i) {
    empty_gates[i] = i;
  }

  int ans = P;
  int gate;
  for (int i = 0; i < P; ++i) {
    std::cin >> gate;
    const int empty_gate = GetEmptyGate(gate);
    if (empty_gate == 0) {
      ans = i;
      break;
    }
    empty_gates[empty_gate] = GetEmptyGate(empty_gate - 1);
  }

  std::cout << ans;

  return 0;
}