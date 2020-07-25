int mn[maxn], prim[maxprime];
int tot = 0;
void init() {
    for (int i = 2; i < maxn; ++i) {
        if (!mn[i]) prim[++tot] = i, mn[i] = i;
        for (int j = 1; j <= tot && i * prim[j] < maxn; ++j) {
            mn[i * prim[j]] = prim[j];
            if (!(i % prim[j])) break;
        }
    }
}

// 素数个数表
// 10 4
// 1e5 9592 (1e4)
// 2e5 17984 (2e4)
// 5e5 41538 (5e4)
// 1e6 78498 (8e4)
// 2e6 148933 (1.5e5)
// 1e7 664579 (7e5)
// 3e7 1857859 (2e6)
// 1e8 5761455 (6e6)