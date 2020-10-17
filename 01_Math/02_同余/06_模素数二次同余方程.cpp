// 要求模为素数，输入n, mod，返回 x^2 % mod = n，可解任意一元二次方程

bool Legendre(ll a, ll p) {
    return qp(a, p - 1 >> 1, p) == 1;
}

ll modsqr(ll a, ll p) {
    ll x;
    ll i, k, b;
    if (p == 2) x = a % p;
    else if (p % 4 == 3) x = qp(a, p + 1 >> 2, p);
    else {
        for (b = 1; Legendre(b, p); ++b);
        i = p - 1 >> 1;
        k = 0;
        do {
            i >>= 1;
            k >>= 1;
            if (!((1LL * qp(a, i, p) * qp(b, k, p) + 1) % p)) k += p - 1 >> 1;
        } while (!(i & 1));
        x = 1ll * qp(a, i + 1 >> 1, p) * qp(b, k >> 1, p) % p;
    }
    return min(x, p - x);
//    if(p-x<x) x=p-x;
//    if(x==p-x) printf("%d\n",x);
//    else printf("%d %d\n",x,p-x);
}