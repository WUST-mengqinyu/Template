void exgcd(ll a, ll b, ll c, ll d, ll &x, ll &y) {
    ll z = (a + b - 1) / b;
    if (z <= c / d) {
        x = z;
        y = 1;
        return;
    }
    a -= (z - 1) * b; c -= (z - 1) * d;
    exgcd(d, c, b, a, y, x);
    x += (z - 1) * y;
}

// 求 a/b mod p = x mod p，优先 b 小
pair<ll, ll> invInv(ll p, ll x) {
    ll b, y;
    exgcd(p, x, p, x - 1, b, y);
    return {b * x - p * y, b};
}