// maxn 至少是大于m+n的2次方数
// m+n 2e5 maxn (1<<18)+50
// m+n 4e5 maxn (1<<19)+50
// m+n 2e6 maxn (1<<21)+50
#define ld double
const ld PI = acosl(-1);
struct cplx {
    ld a, b;
    cplx(ld a = 0, ld b = 0) : a(a), b(b) {}
    const cplx operator+(const cplx &c) const { return cplx(a + c.a, b + c.b); }
    const cplx operator-(const cplx &c) const { return cplx(a - c.a, b - c.b); }
    const cplx operator*(const cplx &c) const { return cplx(a * c.a - b * c.b, a * c.b + b * c.a); }
    const cplx operator/(const ld &x) const { return cplx(a / x, b / x); }
    const cplx conj() const { return cplx(a, -b); }
};
int rev[maxn];
cplx w[maxn];
cplx f[maxn];
void prepare(int &n) {
    int sz = __builtin_ctz(n);
    for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
    w[0] = 0, w[1] = 1, sz = 1;
    while (1 << sz < n) {
        cplx w_n = cplx(cosl(2 * PI / (1 << (sz + 1))), sinl(2 * PI / (1 << (sz + 1))));
        for (int i = 1 << (sz - 1); i < (1 << sz); ++i) {
            w[i << 1] = w[i], w[i << 1 | 1] = w[i] * w_n;
        }
        ++sz;
    }
}
void fft(cplx *a, int n) {
    for (int i = 1; i < n - 1; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int h = 1; h < n; h <<= 1) {
        for (int s = 0; s < n; s += h << 1) {
            for (int i = 0; i < h; ++i) {
                cplx &u = a[s + i], &v = a[s + i + h], t = v * w[h + i];
                v = u - t, u = u + t;
            }
        }
    }
}
template<class T>
vector<T> multiply(const vector<T> &a, const vector<T> &b) {
    int n = a.size(), m = b.size(), sz = 1;
    while (sz < n + m - 1) sz <<= 1;
    prepare(sz);
    for (int i = 0; i < sz; ++i) f[i] = cplx(i < n ? a[i] : 0, i < m ? b[i] : 0);
    fft(f, sz);
    for (int i = 0; i <= (sz >> 1); ++i) {
        int j = (sz - i) & (sz - 1);
        cplx x = (f[i] * f[i] - (f[j] * f[j]).conj()) * cplx(0, -0.25);
        f[j] = x, f[i] = x.conj();
    }
    fft(f, sz);
    vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) {
        c[i] = ((T) (f[i].a / sz + 0.3));
    }
    return c;
}
#undef ld