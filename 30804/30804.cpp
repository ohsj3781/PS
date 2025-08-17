#include <iostream>
#include <vector>

constexpr int MAX_TYPE = 9;

void operator-=(std::vector<int>& lv, const std::vector<int>& rv) {
  for (int i = 0; i < lv.size(); ++i) {
    lv[i] -= rv[i];
  }
  return;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
  for (auto i = v.begin(); i != v.end(); ++i) {
    os << *i << ' ';
  }
  return os;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<std::vector<int>> t(N + 1, std::vector<int>(MAX_TYPE));

  int type;
  for (auto i = t.begin() + 1; i != t.end(); ++i) {
    std::cin >> type;
    *i = *(i - 1);
    ++(*i)[type - 1];

    // std::cout << *i << '\n';
  }

  int low = 1, high = N, mid, ans = 0;

  bool valid_len = false;
  while (low <= high) {
    mid = (low + high) >> 1;

    for (auto i = t.begin() + mid; i != t.end(); ++i) {
      std::vector<int> type_cnt = *i;
      type_cnt -= *(i - mid);

      //   std::cout << "type_cnt:\n" << type_cnt << '\n';

      int cnt_types = 0;
      for (auto i = type_cnt.begin(); i != type_cnt.end(); ++i) {
        cnt_types += *i != 0 ? 1 : 0;
      }
      valid_len = cnt_types <= 2 ? true : false;
      if (valid_len) {
        break;
      }
    }
    // std::cout << "mid : " << mid << " valid_len : " << valid_len << '\n';
    if (valid_len) {
      low = mid + 1;
      ans = mid > ans ? mid : ans;
    } else {
      high = mid - 1;
    }
  }

  std::cout << ans;

  return 0;
}