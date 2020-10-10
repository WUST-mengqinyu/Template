#define poly vector<int>
const int maxn = 2097152;
const int mod = 998244353;
const int root = 3;
// 998244353 -> 3
// 1004535809 -> 3

// m+n 2e5 maxn (1<<18)
// m+n 4e5 maxn (1<<19)
// m+n 2e6 maxn (1<<21)

template<int mod, int root>
struct NTT {
    int omega[maxn + 5];

    NTT() {
        int x = fpow(root, (mod - 1) / maxn);
        omega[0] = 1;
        for (int i = 1; i <= maxn; ++i) omega[i] = 1ll * omega[i - 1] * x % mod;
    }

    int fpow(int a, int n) {
        n %= mod - 1;
        if (n < 0) n += mod - 1;
        a %= mod;
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1ll * res * a % mod;
            a = 1ll * a * a % mod;
            n >>= 1;
        }
        return res;
    }

    int L, rev[maxn + 5], p[maxn + 5];
    int A[maxn + 5], B[maxn + 5];
    unsigned ll tp[maxn+5];
    void init(int n) {
        L = 1;
        while (L <= n) L <<= 1;
        for (int i = 0; i <= L - 1; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (L >> 1) : 0);
    }

    // 0 ntt 1 intt
    void ntt(int *a, int n, int flag = 0) {
        for (int i = 0; i < n; ++i) tp[rev[i]] = a[i];
        for (int d = 1; d < n; d <<= 1) {
            int len = maxn / (d << 1);
            for (int i = 0, j = 0; i < d; ++i, j += len) p[i] = omega[j];
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; ++j) {
                    int y = tp[i + j + d] * p[j] % mod;
                    tp[i + j + d] = tp[i + j] + mod - y;
                    tp[i + j] += y;
                }
            if (d == 1 << 15) {
                for (int i = 0; i < n; ++i) tp[i] %= mod;
            }
        }
        if (flag == 0) {
            for (int i = 0; i < n; ++i) a[i] = tp[i] % mod;
        } else {
            int inv = fpow(n, mod - 2);
            for (int i = 1; i < n / 2; ++i) swap(tp[i], tp[n - i]);
            for (int i = 0; i < n; ++i) a[i] = tp[i] * inv % mod;
        }
    }

    void intt(int *a, int n) { ntt(a, n, 1); }

    void shrink(poly &c) { while (!c.empty() && c.back() == 0) c.pop_back(); }

    poly operator()(const poly& a, const poly& b) {
        int sza = a.size(), szb = b.size();
        if (sza <= 30 || szb <= 30) {
            poly c(sza + szb - 1);
            for (int i = 0; i < sza; ++i) for (int j = 0; j < szb; ++j) {
                c[i + j] += 1ll * a[i] * b[j] % mod;
                if (c[i + j] >= mod) c[i + j] -= mod;
            }
            return c;
        }
        init(sza + szb - 2);
        for (int i = 0; i < L; ++i) {
            A[i] = (i < sza ? a[i] : 0);
            B[i] = (i < szb ? b[i] : 0);
        }
        ntt(A, L), ntt(B, L);
        for (int i = 0; i < L; ++i) A[i] = 1ll * A[i] * B[i] % mod;
        intt(A, L);
        return poly(A, A + sza + szb - 1);
    }

    poly operator()(const poly& a, int n) {
        int sza = a.size();
        init((sza - 1) * n + 1);
        for (int i = 0; i < L; ++i) A[i] = (i < sza ? a[i] : 0);
        ntt(A, L);
        for (int i = 0; i < L; ++i) A[i] = fpow(A[i], n);
        intt(A, L);
        return poly(A, A + (sza - 1) * n + 1);
    }
};

NTT<mod, root> conv;