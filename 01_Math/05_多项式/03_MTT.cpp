const int maxn = 262144;
int mod = 1e9+7;

namespace MTT {
    struct comp {
        double x, y;
        comp(double x_ = 0, double y_ = 0): x(x_), y(y_) {}
    };
    inline comp operator + (const comp& a, const comp& b) { return comp(a.x + b.x, a.y + b.y); }
    inline comp operator - (const comp& a, const comp& b) { return comp(a.x - b.x, a.y - b.y); }
    inline comp operator * (const comp& a, const comp& b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    inline comp conj(const comp& a) { return comp(a.x, -a.y); }

    const double PI = acosl(-1);
    comp w[maxn + 5];
    int bitrev[maxn + 5];
    int N, L;

    void fft(vector<comp>& a) {
        for (int i = 0; i < N; ++i) if (i < bitrev[i]) swap(a[i], a[bitrev[i]]);
        for (int i = 2, lyc = N >> 1; i <= N; i <<= 1, lyc >>= 1) {
            for (int j = 0; j < N; j += i) {
                int pl = j, pr = j + (i >> 1), p = 0;
                for (int k = 0; k < (i >> 1); ++k) {
                    comp tmp = a[pr] * w[p];
                    a[pr] = a[pl] - tmp, a[pl] = a[pl] + tmp;
                    ++ pl, ++ pr, p += lyc;
                }
            }
        }
    }

    inline void fft_prepare() {
        for (int i = 0; i < N; ++i) bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (L - 1));
        for (int i = 0; i < N; ++i) w[i] = comp(cos(2 * PI * i / N), sin(2 * PI * i / N));
    }

    // if max ans is n+m, n=n+m+1
    void init(int n) {
        L = 0;
        while ((1 << L) < n) ++ L;
        N = 1 << L;
        fft_prepare();
    }

    inline vector<int> conv(vector<int> x, vector<int> y) {
        vector<comp> a(N + 5), b(N + 5);
        vector<comp> dfta(N + 5), dftb(N + 5), dftc(N + 5), dftd(N + 5);
        for (int i = 0; i < (int)x.size(); ++i) {
            if ((x[i] %= mod) < 0) x[i] += mod;
            a[i] = comp(x[i] & 32767, x[i] >> 15);
        }
        for (int i = 0; i < (int)y.size(); ++i) {
            if ((y[i] %= mod) < 0) y[i] += mod;
            b[i] = comp(y[i] & 32767, y[i] >> 15);
        }
        fft(a), fft(b);
        for (int i = 0; i < N; ++i) {
            int j = (N - i) & (N - 1);
            comp da = (a[i] + conj(a[j])) * comp(0.5, 0);
            comp db = (a[i] - conj(a[j])) * comp(0, -0.5);
            comp dc = (b[i] + conj(b[j])) * comp(0.5, 0);
            comp dd = (b[i] - conj(b[j])) * comp(0, -0.5);
            dfta[j] = da * dc;
            dftb[j] = da * dd;
            dftc[j] = db * dc;
            dftd[j] = db * dd;
        }
        for (int i = 0; i < N; ++i) a[i] = dfta[i] + dftb[i] * comp(0, 1);
        for (int i = 0; i < N; ++i) b[i] = dftc[i] + dftd[i] * comp(0, 1);
        fft(a), fft(b);
        vector<int> z(N);
        for (int i = 0; i < N; ++i) {
            int da = (ll)(a[i].x / N + 0.5) % mod;
            int db = (ll)(a[i].y / N + 0.5) % mod;
            int dc = (ll)(b[i].x / N + 0.5) % mod;
            int dd = (ll)(b[i].y / N + 0.5) % mod;
            z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
            if (z[i] < 0) z[i] += mod;
        }
        while (!z.empty() && z.back() == 0) z.pop_back();
        return z;
    }
}

int main(int argc, char* argv[]) {
    int n, m;
    R(n, m);
    VI a(n + 5), b(m + 5);
    MTT::init(n + m + 1);
    for (int i = 0; i <= n; ++i) R(a[i]);
    for (int i = 0; i <= m; ++i) R(b[i]);
    auto res = MTT::conv(a, b);
    while (res.size() < (n + m + 1)) res.push_back(0);
    W(res);
    return 0;
}