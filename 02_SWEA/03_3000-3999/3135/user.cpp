static constexpr int ALPHA_SIZE = 26;
static constexpr char C_OFFSET = 'a';
static constexpr int POOL_SIZE = 100'000'1;

struct Node {
  int cnt_;
  int ch_[ALPHA_SIZE];

  void Init() {
    cnt_ = 0;
    for (int &c : ch_) {
      c = -1;
    }
    return;
  }
};

static Node pool[POOL_SIZE];
static int pool_top;

void init(void) {
  pool_top = 0;
  pool[pool_top++].Init();

  return;
}

void insert(int buffer_size, char *buf) {
  int now = 0;

  for (int i = 0; i < buffer_size; ++i) {
    const int c = buf[i] - C_OFFSET;

    if (pool[now].ch_[c] == -1) {
      pool[pool_top].Init();
      pool[now].ch_[c] = pool_top++;
    }

    now = pool[now].ch_[c];
    ++pool[now].cnt_;
  }

  return;
}

int query(int buffer_size, char *buf) {
  int now = 0;
  for (int i = 0; i < buffer_size; ++i) {
    int c = buf[i] - C_OFFSET;
    if (pool[now].ch_[c] == -1) {
      return 0;
    }

    now = pool[now].ch_[c];
  }

  return pool[now].cnt_;
}