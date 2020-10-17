#define poly vector<int>

// mod need to be prim
namespace dirichlet {
    int inv[maxn], cnt[maxn];
    bool vis[maxn];
    void init(int n) {
        cnt[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!vis[i]) {
                cnt[i] = 1;
                for (int j = 2, k = i * j; k <= n; ++j, k += i) {
                    vis[k] = true;
                    if (!cnt[k] && cnt[j]) cnt[k] = cnt[j] + 1;
                }
            }
        }
        inv[1] = 1;
        // no need to n (1e6 need 128)
        for (int i = 2; i <= n; ++i) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    }

    // no need to init, nlogn
    poly mul(poly a, poly b) {
        int n = max(a.size(), b.size()) - 1;
        while ((int)a.size() <= n) a.push_back(0);
        while ((int)b.size() <= n) b.push_back(0);
        poly d(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1, k = i; k <= n; k += i, ++j) d[k] = (d[k] + 1ll * a[i] * b[j]) % mod;
        }
        return d;
    }

    // nlogn
    poly qp(poly a, int k) {
        k %= mod;
        if (k < 0) k += mod;
        int n = a.size() - 1;
        poly g(n + 1);
        poly tf = a;
        for (int i = 1; i <= n; ++i) a[i] = 1ll * a[i] * cnt[i] % mod * k % mod;
        for (int i = 1; i <= n; ++i) {
            int v = g[i];
            g[i] = 1ll * g[i] * inv[cnt[i]] % mod + (i == 1);
            for (int j = 2, t = i + i; t <= n; ++j, t += i)
                g[t] = (g[t] + 1ll * g[i] * a[j]) % mod;
            for (int j = 2, t = i + i; t <= n; ++j, t += i)
                g[t] = (g[t] + 1ll * (mod - tf[j]) * v) % mod;
        }
        return g;
    }

    // nlogn
    inline poly ln(const poly& a) {
        int n = a.size() - 1;
        poly b(n + 1);
        for (int i = 2; i <= n; ++i) b[i] = 1ll * a[i] * cnt[i] % mod;
        for (int i = 2; i <= n; ++i) {
            for (int j = 2, k = i * j; k <= n; ++j, k += i) b[k] = (b[k] - 1ll * b[i] * a[j]) % mod;
            b[i] = 1ll * b[i] * inv[cnt[i]] % mod;
            if (b[i] < 0) b[i] += mod;
        }
        return b;
    }

    // nlogn
    inline poly exp(poly a) {
        int n = a.size() - 1;
        poly b(n + 1);
        for (int i = 2; i <= n; ++i) a[i] = 1ll * a[i] * cnt[i] % mod;
        b[1] = 1;
        for (int i = 1; i <= n; ++i) {
            b[i] = 1ll * b[i] * inv[cnt[i]] % mod;
            for (int j = 2, k = i * j; k <= n; ++j, k += i) b[k] = (b[k] + 1ll * b[i] * a[j]) % mod;
        }
        return b;
    }
}
using namespace dirichlet;