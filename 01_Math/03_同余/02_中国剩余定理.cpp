void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b) exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
}

// x % m[i] = a[i]
ll crt(const vector<ll>& m, const vector<ll>& a) {
    ll M = 1, ans = 0;
    int n = a.size();
    for (int i = 0; i < n; i++) M *= m[i];
    for (int i = 0; i < n; i++) {
        ll x = 0, y = 0, Mi = M / m[i];
        exgcd(Mi, m[i], x, y);
        ans = (ans + Mi % M * x % M * a[i] % M + M) % M;
    }
    if (ans < 0) ans += M;
    return ans;
}