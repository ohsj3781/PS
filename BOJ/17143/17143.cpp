#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int R, C, M;

struct Pos {
  int r;
  int c;
};

std::istream& operator>>(std::istream& is, Pos& p) {
  is >> p.r >> p.c;
  return is;
}

struct Shark {
  int s;
  int d;

  const Pos move(Pos p) {
    switch (d) {
      case 1:
        p.r -= s;
        p.r %= (R - 1) << 1;
        this->d = p.r <= -R || p.r >= 0 ? this->d : 2;
        p.r = p.r <= -R ? p.r + ((R - 1) << 1) : std::abs(p.r);
        break;
      case 2:
        p.r += s;
        p.r %= (R - 1) << 1;
        this->d = p.r >= R ? 1 : this->d;
        p.r = p.r >= R ? ((R - 1) << 1) - p.r : p.r;
        break;
      case 3:
        p.c += s;
        p.c %= (C - 1) << 1;
        this->d = p.c >= C ? 4 : this->d;
        p.c = p.c >= C ? ((C - 1) << 1) - p.c : p.c;
        break;
      case 4:
        p.c -= s;
        p.c %= (C - 1) << 1;
        this->d = p.c <= -C || p.c >= 0 ? this->d : 3;
        p.c = p.c <= -C ? p.c + ((C - 1) << 1) : std::abs(p.c);
        break;
    }

    return p;
  }
};

std::istream& operator>>(std::istream& is, Shark& s) {
  is >> s.s >> s.d;
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);

  std::cin >> R >> C >> M;
  std::cin.ignore();

  std::string input;
  std::stringstream buffer;

  Shark sharks[10'000];

  std::vector<std::vector<int>> matrix(C, std::vector<int>(R, -1));
  std::vector<std::vector<int>> next_matrix(matrix);

  for (int i = 0; i < M; ++i) {
    std::getline(std::cin, input);
    buffer << input;

    int r, c, z;
    Shark s;
    buffer >> r >> c >> s >> z;
    // std::cin >> r >>c >> s >> z;
    matrix[c - 1][r - 1] = z - 1;
    sharks[z - 1] = s;
    buffer.clear();
  }

  int ans = 0;

  for (int c = 0; c < C; ++c) {
    for (int r = 0; r < R; ++r) {
      if (matrix[c][r] == -1) {
        continue;
      }
      ans += matrix[c][r] + 1;
      matrix[c][r] = -1;
      break;
    }

    for (auto& i : next_matrix) {
      std::fill(i.begin(), i.end(), -1);
    }

    for (int now_c = 0; now_c < C; ++now_c) {
      for (int now_r = 0; now_r < R; ++now_r) {
        if (matrix[now_c][now_r] == -1) {
          continue;
        }
        const Pos next_pos = sharks[matrix[now_c][now_r]].move({now_r, now_c});
        next_matrix[next_pos.c][next_pos.r] =
            std::max(next_matrix[next_pos.c][next_pos.r], matrix[now_c][now_r]);
      }
    }
    matrix = next_matrix;
  }

  std::cout << ans;

  return 0;
}