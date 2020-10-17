// maxn 至少是大于m+n的2次方数
// m+n 2e5 maxn (1<<18)+50
// m+n 4e5 maxn (1<<19)+50
// m+n 2e6 maxn (1<<21)+50

// 普通fft
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Complex {
    double r, i;

    Complex(double r, double i) : r(r), i(i) {}
    Complex() {}
    inline Complex operator+(const Complex &rhs) const { return Complex(r + rhs.r, i + rhs.i); }
    inline Complex operator-(const Complex &rhs) const { return Complex(r - rhs.r, i - rhs.i); }
    inline Complex operator*(const Complex &rhs) const { return Complex(r * rhs.r - i * rhs.i, r * rhs.i + i * rhs.r); }
    inline void operator/=(const double &x) { r /= x, i /= x; }
    inline void operator*=(const Complex &rhs) { *this = Complex(r * rhs.r - i * rhs.i, r * rhs.i + i * rhs.r); }
    inline void operator+=(const Complex &rhs) { r += rhs.r, i += rhs.i; }
};

const int maxn = 4e6 + 6;
#define PI 3.14159265354
int pos[maxn];

void init(const int &n) {
    for (int i = 0, j = 0; i < n; ++i) {
        pos[i] = j;
        for (int l = n >> 1; (j ^= l) < l; l >>= 1);
    }
}

void transform(Complex *a, const int &n, bool inverse) {
    for (int i = 0; i < n; ++i) if (i > pos[i]) std::swap(a[i], a[pos[i]]);
    for (int l = 2; l <= n; l <<= 1) {
        int m = l / 2;
        Complex omega = {cos(2 * PI / l), inverse ? -sin(2 * PI / l) : sin(2 * PI / l)};
        for (Complex *p = a; p != a + n; p += l) {
            Complex x = {1, 0};
            for (int i = 0; i < m; ++i, x *= omega) {
                Complex t = x * p[m + i];
                p[m + i] = p[i] - t;
                p[i] += t;
            }
        }
    }
}

void dft(Complex *a, const int &n) { transform(a, n, 0); }

void idft(Complex *a, const int &n) {
    transform(a, n, 1);
    for (int i = 0; i < n; ++i) a[i] /= n;
}

Complex A[maxn], B[maxn], C[maxn];

void FFT(int n, int m) {// len(A),len(B)
    int cnt = 1;
    while (cnt <= (n + m)) cnt <<= 1;
    init(cnt);
    dft(A, cnt);
    dft(B, cnt);
    for (int i = 0; i < cnt; i++) C[i] = A[i] * B[i];
    idft(C, cnt);
    for (int i = 0; i <= n + m; i++) C[i].r = ll(C[i].r + 0.01);
}

int main() {
    int n, m, tem;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) scanf("%d", &tem), A[i].r = tem;
    for (int i = 0; i <= m; i++) scanf("%d", &tem), B[i].r = tem;
    FFT(n, m);
    for (int i = 0; i <= n + m; i++) printf("%lld ", ll(C[i].r));
    cout << "\n";
}

// 两次变换
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