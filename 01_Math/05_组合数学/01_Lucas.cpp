const int maxn = 1e6 + 10;

ll fac[maxn], inv[maxn], facinv[maxn];

void init() {
    fac[0] = inv[0] = facinv[0] = 1;
    fac[1] = inv[1] = facinv[1] = 1;
    for (int i = 2; i < maxn; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - mod / i * inv[mod % i] % mod;
        facinv[i] = facinv[i - 1] * inv[i] % mod;
    }
}

ll C(int n, int k) {
    if (k > n || k < 0) return 0;
    return fac[n] * facinv[k] % mod * facinv[n - k] % mod;
}

ll lucas(ll n, ll m) {
    ll res = 1;
    while (n && m) {
        res = res * C(n % mod, m % mod) % mod;
        n /= mod;
        m /= mod;
    }
    return res;
}