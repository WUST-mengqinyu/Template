// ---
// $0 \leq m \leq n \leq 1000$
// ---
const int maxn = 1010;
ll C[maxn][maxn];
void init() {
    C[0][0] = 1;
    for (int i = 1; i < maxn; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
}

// ---
// $0 \leq m \leq n \leq 10^5$, 模$p$为素数
// ---
const int maxn = 100010;
ll f[maxn];
ll inv[maxn]; // 阶乘的逆元
void CalFact() {
    f[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = (f[i - 1] * i) % p;
    inv[maxn - 1] = qp(f[maxn - 1], p - 2);
    for (int i = maxn - 2; ~i; i--) inv[i] = inv[i + 1] * (i + 1) % p;
}
ll C(int n, int m) { return f[n] * inv[m] % p * inv[n - m] % p; }