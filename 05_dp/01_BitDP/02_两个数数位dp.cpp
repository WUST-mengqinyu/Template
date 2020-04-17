// 二进制数位dp，求a $\in$ 1～x 和 b $\in$ 1~y，满足 $a & b > c || a ^ b < c$的对数
ll dp[maxn][2][2][2][2];
int a[maxn], b[maxn], c[maxn];


void cal(int *xt, ll x) {
    int has = 0;
    while (x) {
        xt[has++] = x % 2;
        x /= 2;
    }
}

ll dfs(int pos, int o1, int o2, int lim1, int lim2) {
    if (pos < 0) return 1;
    ll &t = dp[pos][o1][o2][lim1][lim2];
    if (t != -1) return t;
    int up1 = o1 ? a[pos] : 1;
    int up2 = o2 ? b[pos] : 1;
    ll res = 0;
    for (int i = 0; i <= up1; ++i) {
        for (int j = 0; j <= up2; ++j) {
            int t1 = i & j;
            int t2 = i ^ j;
            if (lim1 && t1 > c[pos]) continue;
            if (lim2 && t2 < c[pos]) continue;
            res += dfs(pos - 1, o1 && i == up1, o2 && j == up2, lim1 && t1 == c[pos], lim2 && t2 == c[pos]);
        }
    }
    return t = res;
}

ll solve(ll x, ll y, ll z) {
    memset(dp, -1ll, sizeof dp);
    for (int i = 0; i < 33; ++i) a[i] = b[i] = c[i] = 0;
    cal(a, x);
    cal(b, y);
    cal(c, z);
    return dfs(32, 1, 1, 1, 1);
}

int main(int argc, char *argv[]) {
    int T;
    scanf("%d", &T);
    ll x, y, z;
    for (int kase = 1; kase <= T; ++kase) {
        scanf("%lld%lld%lld", &x, &y, &z);
        ll res = solve(x, y, z);
        res -= max(0ll, y - z + 1);
        res -= max(0ll, x - z + 1);
        printf("%lld\n", x * y - res);
    }
    return 0;
}