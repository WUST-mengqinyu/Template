const int maxn = 1e7+50;

int prim[maxn], vis[maxn];
int tot, phi[maxn];
struct node {
    ll res;
    bool v;
};

node qpow(ll A, ll B, ll C) {
    ll re = 1;
    bool flag = true;
    while (B) {
        if (B & 1) {
            if ((re *= A) >= C) flag = 0;
            re = re % C;
        }
        B = B >> 1;
        if (B) {
            if (A >= C) flag = 0;
            A %= C;
            if ((A *= A) >= C) flag = 0;
            A %= C;
        }
    }
    return node{re, flag};
}

void init(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prim[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot && prim[j] * i <= n; j++) {
            vis[i * prim[j]] = 1;
            if (i % prim[j] == 0) {
                phi[i * prim[j]] = phi[i] * prim[j];
                break;
            } else phi[i * prim[j]] = phi[i] * (prim[j] - 1);
        }

    }
}


inline ll Euler(ll x) {
    if (x < maxn) return phi[x];
    return 0;
}

node f(ll a, ll k, ll p) {
    if (p == 1) return node{0, 0};
    if (k == 0) return node{a % p, a < p};
    ll ep = Euler(p);
    node tmp = f(a, k - 1, ep);
    if (__gcd(a, p) == 1)return qpow(a, tmp.res, p);
    if (!tmp.v) {
        tmp.res += ep;
    }
    return qpow(a, tmp.res, p);
}

int main() {
    ll a, k, p;
    init(1e7+2);
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        // k次a次方模p的值
        scanf("%lld%lld%lld", &a, &k, &p);
        if (k == 0) printf("%lld\n", 1 % p);
        else printf("%lld\n", f(a, k - 1, p).res);
    }
    return 0;
}