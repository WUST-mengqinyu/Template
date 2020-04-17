bool f[maxlen];
bool sieve[maxn];

// maxn 至少为 sqrt(R)，预处理
void init() {
    for (int i = 2; i < maxn; i++) sieve[i] = true;
    for (int i = 2; i * i < maxn; i++) {
        if (sieve[i]) {
            for (int j = i * 2; j < maxn; j += i) {
                sieve[j] = false;
            }
        }
    }
}
// 计算 [L,R] 素性，f[i] 为 1 表示 i+L 为素数
void cal(ll L, ll R) {
    int len = R - L + 1;
    for (int i = 0; i < len; i++) f[i] = true;
    if (1 - L >= 0) f[1 - L] = false;
    for (ll i = 2; i * i < R; i++) {
        if (sieve[i]) {
            for (ll j = max(1ll * 2, (L - 1 + i) / i) * i; j <= R; j += i) f[j - L] = false;
        }
    }
}