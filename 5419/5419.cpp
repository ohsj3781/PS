#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

struct Island {
  int x;
  int y;
};

struct FirstCompare {
  const bool operator()(const Island& li, const Island& ri) {
    return li.y != ri.y ? li.y < ri.y : li.x > ri.x;
  }
};

struct SecondCompare {
  const bool operator()(const Island& li, const Island& ri) {
    return li.x != ri.x ? li.x < ri.x : li.y > ri.y;
  }
};

struct SegTree {
 private:
  int nmax;
  std::array<int, 262'144> tree;

 public:
  void Init(const int N) {
    nmax = BitCeil(N);
    std::fill_n(tree.begin(), nmax << 1, 0);
    return;
  }

  void Insert(const int num) {
    for (int i = (num + nmax); i > 0; i >>= 1) {
      tree[i]++;
    }
    tree[0]++;
    return;
  }

  const int Query(int right) {
    int left = 0;
    int left_value = 0;
    int right_value = 0;
    for (left += nmax, right += nmax + 1; left < right;
         left >>= 1, right >>= 1) {
      if (left & 1) {
        left_value += tree[left++];
      }
      if (right & 1) {
        right_value += tree[--right];
      }
    }
    return left_value + right_value;
  }

 private:
  const int BitCeil(int size) {
    int output_size = 1;
    while (size != 0) {
      output_size <<= 1;
      size >>= 1;
    }
    return output_size;
  }
};

std::istream& operator>>(std::istream& is, Island& i) {
  is >> i.x >> i.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Island& i) {
  os << i.x << " " << i.y;
  return os;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  int T;
  std::cin >> T;

  std::array<Island, 75000> islands;
  SegTree tree;

  for (int test_case = 0; test_case < T; ++test_case) {
    int N;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
      std::cin >> islands[i];
    }

    std::sort(islands.begin(), islands.begin() + N, FirstCompare());
    for (int i = 0; i < N; ++i) {
      islands[i].y = i;
    }
    std::sort(islands.begin(), islands.begin() + N, SecondCompare());

    long long ans = 0;
    tree.Init(N);
    for (int i = 0; i < N; ++i) {
      ans += i - tree.Query(islands[i].y);
      tree.Insert(islands[i].y);
    }

    std::cout << ans << "\n";
  }

  return 0;
}