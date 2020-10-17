//FWT 完后需要先模一遍
template<typename T>
void fwt(ll a[], int n, T f) {
    for (int d = 1; d < n; d *= 2)
        for (int i = 0, t = d * 2; i < n; i += t)
            for(int j = 0; j < d; j ++)
                f(a[i + j], a[i + j + d]);
}

void AND(ll& a, ll& b) { a += b; }
void OR(ll& a, ll& b) { b += a; }
void XOR (ll& a, ll& b) {
    ll x = a, y = b;
    a = (x + y) % mod;
    b = (x - y + mod) % mod;
}
void rAND(ll& a, ll& b) { a -= b; }
void rOR(ll& a, ll& b) { b -= a; }
void rXOR(ll& a, ll& b) {
    static ll INV2 = (mod + 1) / 2;
    ll x = a, y = b;
    a = (x + y) * INV2 % mod;
    b = (x - y + mod) * INV2 % mod;
}

//FWT 子集卷积 i与j=0，i或j为k
a[popcount(x)][x] = A[x]
b[popcount(x)][x] = B[x]
fwt(a[i]) fwt(b[i])
c[i + j][x] += a[i][x] * b[j][x]
rfwt(c[i])
ans[x] = c[popcount(x)][x]