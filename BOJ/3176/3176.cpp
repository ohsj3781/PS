#include <climits>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

struct LL {
    static constexpr long long SHIFT = 20;
    static constexpr long long MASK = (1 << SHIFT) - 1;
    static constexpr long long INITIALPARENT = MASK << SHIFT;
    long long value;

    LL() : value(INITIALPARENT) {}
    const LL operator=(const LL &l) {
        this->value = l.value;
        return *this;
    }

    void SetIndex(const long long index) {
        this->value |= index;
        return;
    }

    void SetMinRoute(const long long min_route) {
        this->value -= INITIALPARENT;
        this->value |= min_route << SHIFT;
        return;
    }

    void SetMaxRoute(const long long max_route) {
        this->value |= max_route << (SHIFT << 1);
        return;
    }

    const long long GetIndex() { return this->value & MASK; }

    const long long GetMinRoute() { return this->value >> SHIFT & MASK; }

    const long long GetMaxRoute() { return this->value >> (SHIFT << 1) & MASK; }
};

std::vector<std::vector<std::pair<int, int>>> routes;
/* |max route|min route |parent index| */
std::vector<std::vector<LL>> parents;
std::vector<int> level;

const bool operator<(const std::pair<int, int> &lp,
                     const std::pair<int, int> &rp) {
    return lp.second < rp.second;
}

const bool operator>(const std::pair<int, int> &lp,
                     const std::pair<int, int> &rp) {
    return lp.second > rp.second;
}

std::ostream &operator<<(std::ostream &os,
                         const std::pair<long long, long long> &p) {
    os << p.second << " " << p.first;
    return os;
}

/*level of right parent is must less than level of left parent*/
const LL MakeParents(LL ll, LL rl) {
    LL temp_l;
    temp_l.SetIndex(rl.GetIndex());
    temp_l.SetMinRoute(std::min(ll.GetMinRoute(), rl.GetMinRoute()));
    temp_l.SetMaxRoute(std::max(ll.GetMaxRoute(), rl.GetMaxRoute()));

    return temp_l;
}

void InitTree(const int now, const int parent) {

    for (int i = 1; i < parents[now].size(); ++i) {

        parents[now][i] =
            MakeParents(parents[now][i - 1],
                        parents[parents[now][i - 1].GetIndex()][i - 1]);
    }

    for (auto &route : routes[now]) {
        if (route.first ^ parent) {
            level[route.first] = level[now] + 1;
            parents[route.first].front().SetIndex(now);
            parents[route.first].front().SetMinRoute(route.second);
            parents[route.first].front().SetMaxRoute(route.second);
            InitTree(route.first, now);
        }
    }
    return;
}

/*modify Lowest Common Ancestor*/
const std::pair<long long, long long> FindAns(int left, int right) {
    if (level[left] < level[right]) {
        std::swap(left, right);
    }

    std::pair<long long, long long> ans(LONG_LONG_MIN, LONG_LONG_MAX);

    if (level[left] != level[right]) {
        for (int i = parents[left].size() - 1; i >= 0; --i) {
            if (level[parents[left][i].GetIndex()] >= level[right]) {
                ans.first = std::max(ans.first, parents[left][i].GetMaxRoute());
                ans.second =
                    std::min(ans.second, parents[left][i].GetMinRoute());
                left = parents[left][i].GetIndex();
            }
        }
    }

    if (left != right) {
        for (int i = parents[left].size() - 1; i >= 0; --i) {
            if (parents[left][i].GetIndex() != parents[right][i].GetIndex()) {
                ans.first = std::max(ans.first, parents[left][i].GetMaxRoute());
                ans.first =
                    std::max(ans.first, parents[right][i].GetMaxRoute());

                ans.second =
                    std::min(ans.second, parents[left][i].GetMinRoute());
                ans.second =
                    std::min(ans.second, parents[right][i].GetMinRoute());

                left = parents[left][i].GetIndex();
                right = parents[right][i].GetIndex();
            }
        }
    }

    if (left != right) {
        ans.first = std::max(ans.first, parents[left].front().GetMaxRoute());
        ans.first = std::max(ans.first, parents[right].front().GetMaxRoute());

        ans.second = std::min(ans.second, parents[left].front().GetMinRoute());
        ans.second = std::min(ans.second, parents[right].front().GetMinRoute());
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    routes.assign(N + 1, std::vector<std::pair<int, int>>());
    parents.assign(N + 1, std::vector<LL>(std::floor(std::log2(N)) + 1, LL()));
    level.assign(N + 1, 0);
    for (int i = 0; i < N - 1; ++i) {
        int A, B, C;
        std::cin >> A >> B >> C;

        routes[A].push_back({B, C});
        routes[B].push_back({A, C});
    }

    level[1] = 1;
    InitTree(1, 0);

    int K;
    std::cin >> K;
    for (int i = 0; i < K; ++i) {
        int D, E;
        std::cin >> D >> E;

        std::cout << FindAns(D, E) << "\n";
    }

    return 0;
}