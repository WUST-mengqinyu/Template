//计算欧拉phi函数，phi(n)且与n互素的正整数个数

//单点欧拉 O(sqrt(n))
ll euler(ll n) {
    ll rea = n;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) {
            rea = rea - rea / i;
            while (n % i == 0) n /= i;
        }
    if (n > 1) rea = rea - rea / n;
    return rea;
}


// maxn 为根号最值
// maxprime 为 maxn 内素数个数
// 素数线筛 + 单点求值
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
ll phi(ll n) {
    ll rea = n;
    for (ll i = 1; prim[i] * prim[i] <= n; i++)
        if (n % prim[i] == 0) {
            rea = rea - rea / n;
            while (n % prim[i] == 0) n /= prim[i];
        }
    if (n > 1) rea = rea - rea / n;
    return rea;
}


// 线筛素数+欧拉函数
int phi[maxn], prim[maxprime], cnt;
bool v[maxn];
void init() {
    phi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!v[i]) prim[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt; ++j) {
            if (i * prim[j] >= maxn) break;
            v[i * prim[j]] = 1;
            if (i % prim[j] == 0) {
                phi[i * prim[j]] = phi[i] * prim[j]; break;
            } else phi[i * prim[j]] = phi[i] * phi[prim[j]];
        }
    }
}