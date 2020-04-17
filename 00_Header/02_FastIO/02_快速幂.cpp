// 精确快速乘
ll mul(ll a, ll b, ll mod) {
    a %= mod; b %= mod;
    ll res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a);
            if (res >= mod) res -= mod;
        }
        a = (a + a);
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return res;
}

// O(1)快速乘
ll mul(ll a, ll b, ll M) { return (a * b - (ll)((long double)a * b / M) * M + M) % M; }

//int128
ll ans = ((__int128) a * b) % p;

// 10进制快速幂，直接读入%s,c 预处理字符串len
char c[1000005];
int len;
ll qp(ll a) {
    len --;
    a %= mod;
    ll s = a;
    ll res = 1;
    while (len >= 0) {
        ll cur = s;
        for (int i = 1; i <= c[len] - '0'; ++i) {
            res = res * s % mod;
        }
        for (int i = 1; i < 10; ++i) {
            cur = cur * s % mod;
        }
        s = cur;
        len --;
    }
    return res;
}