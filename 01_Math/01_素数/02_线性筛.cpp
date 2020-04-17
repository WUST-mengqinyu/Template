int prim[maxprime], cnt;
bool v[maxn];
void init() {
    v[0] = v[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!v[i]) prim[++cnt] = i;
        for (int j = 1; j <= cnt && i * prim[j] < maxn; j++) {
            v[i * prim[j]] = 1;
            if (!(i % prim[j])) break;
        }
    }
}

// 素数个数表
// 10 4
// 1e5 9592
// 2e5 17984
// 5e5 41538
// 1e6 78498
// 2e6 148933
// 1e7 664579
// 1e8 5761455