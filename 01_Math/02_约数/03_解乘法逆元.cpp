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

int main(int argc, char* argv[]) {
    int T;
    scanf("%d", &T);
    ll p, x;
    for (int kase = 1; kase <= T; ++kase) {
        scanf("%lld%lld", &p, &x);
        ll b, y;
        exgcd(p, x, p, x - 1, b, y);
        printf("%lld/%lld\n", b * x - p * y, b);
    }
    return 0;
}