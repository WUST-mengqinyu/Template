#define u64 unsigned long long
#define i64 long long

const u64 BITCOUNT = sizeof(u64) * 8;

u64 count_trailing_zeroes(u64 a) {
    if (a == 0ull)
        return BITCOUNT;
    return __builtin_ctzll(a);
}
u64 disable_bit(u64 a, u64 bit) { return a & (~(1ull << bit)); }
u64 popcount(u64 a) { return __builtin_popcountll(a); }

map<u64, u64> max_clique_cache;

u64 max_clique(u64 mask, vector<u64> const &graph_matrix) { // 最大独立集传补图即可
    if (max_clique_cache.find(mask) != max_clique_cache.end())
        return max_clique_cache[mask];
    u64 a = count_trailing_zeroes(mask);
    if (a == BITCOUNT) return 0;
    u64 res1 = max_clique(disable_bit(mask, a), graph_matrix);
    u64 res2 = max_clique(mask & disable_bit(graph_matrix[a], a), graph_matrix) | (1ull << a);
    u64 res = popcount(res1) > popcount(res2) ? res1 : res2;
    max_clique_cache[mask] = res;
    return res;
}

int main() {
    vector<u64> M;
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        M.clear();
        M.resize(n);
        max_clique_cache.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x; scanf("%d", &x);
                if (x == 1) M[i] |= 1ll << j;
            }
        }
        printf("%d\n", popcount(max_clique((1ll << n) - 1, M)));
    }
}