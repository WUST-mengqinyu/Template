bool check(ll a, ll n) {
    if(n == 2 || a >= n) return true;
    if(n == 1 || !(n & 1)) return false;
    ll d = n - 1;
    while(!(d & 1)) d >>= 1;
    ll t = qp(a, d, n);
    while(d != n - 1 && t != 1 && t != n - 1) {
        t = mul(t, t, n);
        d <<= 1;
    } 
    return t == n - 1 || d & 1;
}

bool Miller_Rabin(ll n) {
    static vector<ll> t = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if (n <= 1) return false;
    for (ll k: t) if (!check(k, n)) return false;
    return true;
}