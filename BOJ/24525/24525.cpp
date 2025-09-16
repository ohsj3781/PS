#include <iostream>
#include <string>
#include <utility>
#include <vector>

const std::pair<int, int> operator-(const std::pair<int, int>& lp,
                                    const std::pair<int, int>& rp) {
  return std::pair<int, int>(lp.first - rp.first, lp.second - rp.second);
}

const bool operator!=(const std::pair<int, int>& lp,
                      const std::pair<int, int>& rp) {
  return lp.first != rp.first || lp.second != rp.second;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::string str;
  str.reserve(100'000);
  std::cin >> str;

  /*std::pair.first = count_s, std::pair.second = count_k*/
  std::vector<std::pair<int, int>> cnt_skk(str.length() + 1);
  /*skk_index[i] : i= 2*cnt_s-cnt_k*/
  std::vector<int> skk_index(str.length() * 4 + 1, -1);
  skk_index[2 * str.length()] = 0;
  int ans = -1;
  for (int i = 1; i < cnt_skk.size(); ++i) {
    cnt_skk[i] = cnt_skk[i - 1];

    if (str[i - 1] == 'S') {
      cnt_skk[i].first++;
    }
    if (str[i - 1] == 'K') {
      cnt_skk[i].second++;
    }

    const int index =
        2 * cnt_skk[i].first - cnt_skk[i].second + 2 * str.length();
    if (skk_index[index] == -1) {
      skk_index[index] = i;
    } else {
      if ((cnt_skk[i] - cnt_skk[skk_index[index]]).first != 0) {
        ans = std::max(ans, i - skk_index[index]);
      }
    }
  }

  std::cout << ans;

  return 0;
}
