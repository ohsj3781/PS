#include <iostream>
static constexpr int MAX = 100'000;

int N, M;
int sets[MAX + 1];
int rank[MAX + 1];
long long weights[MAX + 1]; // weights[x] = value[x] - value[parent[x]]

int GetSet(int x) {
  if (sets[x] == x) {
    return x;
  }

  int root = GetSet(sets[x]);
  weights[x] += weights[sets[x]]; // 경로 압축 시 offset 누적
  sets[x] = root;
  return root;
}

// rset is merged to lset
void MergeSet(const int lset, const int rset) {
  sets[GetSet(rset)] = GetSet(lset);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // freopen("sample_input.txt", "r", stdin);

  int T;
  std::cin >> T;

  for (int tc = 1; tc <= T; ++tc) {
    std::cin >> N >> M;

    // Init
    for (int i = 1; i <= N; ++i) {
      sets[i] = i;
      rank[i] = 0;
      weights[i] = 0;
    }

    std::cout << "#" << tc;

    char c;
    int a, b;
    long long w;
    for (int i = 0; i < M; ++i) {
      std::cin >> c >> a >> b;

      if (c == '!') {
        std::cin >> w;

        const int root_a =
            GetSet(a); // 이후 weights[a] = value[a] - value[root_a]
        const int root_b =
            GetSet(b); // 이후 weights[b] = value[b] - value[root_b]

        if (root_a == root_b) {
          continue;
        }

        // value[b] - value[a] = w 조건을 만족시키는 루트 offset 설정
        if (rank[root_a] < rank[root_b]) {
          // root_a를 root_b 아래로 붙임
          // weights[root_a] = value[root_a] - value[root_b]
          //             = (value[a] - weights[a]) - (value[b] - weights[b])
          //             = -(value[b] - value[a]) + weights[b] - weights[a]
          //             = -w + weights[b] - weights[a]

          // sets[root_a] = root_b;
          MergeSet(root_b, root_a);
          weights[root_a] = weights[b] - weights[a] - w;
        } else if (rank[root_a] > rank[root_b]) {
          // root_b를 root_a 아래로 붙임
          // weights[root_b] = value[root_b] - value[root_a]
          //             = (value[b] - weights[b]) - (value[a] - weights[a])
          //             = (value[b] - value[a]) + weights[a] - weights[b]
          //             = w + weights[a] - weights[b]

          // sets[root_b] = root_a;
          MergeSet(root_a, root_b);
          weights[root_b] = w + weights[a] - weights[b];
        } else {
          // sets[root_b] = root_a;
          MergeSet(root_a, root_b);
          weights[root_b] = w + weights[a] - weights[b];
          ++rank[root_a];
        }

      } else {
        const int root_a = GetSet(a);
        const int root_b = GetSet(b);

        if (root_a != root_b) {
          std::cout << " UNKNOWN";
        } else {
          // weights[a] = value[a] - value[root]
          // weights[b] = value[b] - value[root]
          // value[b] - value[a] = weights[b] - weights[a]
          std::cout << " " << weights[b] - weights[a];
        }
      }
    }

    std::cout << "\n";
  }

  return 0;
}