/*
1.费马小定理
条件:mod为素数
*/
ll inv(ll x) { return qp(x, mod - 2); }

/*
2.扩展欧几里得
条件:gcd(a,mod)==1
如果gcd(a,mod)!=1 返回-1
*/
ll inv(ll a, ll p) {
    ll g, x, y;
    g = exgcd(a, p, x, y);
    return g == 1 ? (x + p) % p : -1;
}

/*
3.公式
a/b%mod=c
->a%(b*mod)/b=c
*/

/*
4.逆元打表
p是模
p要求是奇素数
*/
ll inv[maxn];

void getinv(int n, ll p) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
}

// log逆元
ll dlog(ll g, ll b, ll p) {
    ll m = sqrt(p - 1);
    map<ll, ll> powers;
    for (long j = 0; j < m; j++) powers[qp(g, j, p)] = j;
    long gm = qp(g, -m + 2 * (p - 1), p);
    for (int i = 0; i < m; i++) {
        if (powers[b]) return i * m + powers[b];
        b = b * gm % p;
    }
    return -1;
}