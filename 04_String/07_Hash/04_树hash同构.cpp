// n=1e5的话base开2e6+9，可以输出看到top不比n小即可
const int base = 2e6+9;
// vis大小要开到素数大小， turn表示当前树的编号，p是预处理数组
int vis[base + 1], top, turn, p[base + 1];
// 程序开头调用一次
void init() {
    top = 0;
    for (int i = 2; i <= base; ++i) {
        if (!vis[i]) {
            p[++top] = i;
        }
        for (int j = 1; j <= top && i * p[j] <= base; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
    assert(top >= maxn);
}

vector<int> edge[maxn];
// h[x]表示x这棵子树的hash值， g[x]表示以x为根的hash值
int h[maxn], g[maxn], sz[maxn];

struct TreeHash {
    int n;
    // 如果树比较多，在类内部开edge可能会炸内存，可以改到外面做前向星
    // 除了hs是答案其他都可以改到外部，只有edge需要清零
    // vector<int> edge[maxn];
    // int h[maxn], g[maxn], sz[maxn];
    vector<int> hs;

    void init(int n_ = 0) {
        n = n_;
        hs.clear();
    }

    void dfs1(int u, int pre) {
        sz[u] = 1;
        h[u] = 1;
        for (auto v : edge[u]) {
            if (v == pre) continue;
            dfs1(v, u);
            h[u] = (h[u] + 1ll * h[v] * p[sz[v]] % mod) % mod;
            sz[u] += sz[v];
        }
    }

    void dfs2(int u, int pre, int V, int needres = 1) {
        g[u] = (h[u] + 1ll * V * p[n - sz[u]] % mod) % mod;
        if (needres) hs.push_back(g[u]);
        for (auto v : edge[u]) {
            if (v == pre) continue;
            dfs2(v, u, (g[u] - 1ll * h[v] * p[sz[v]] % mod + mod) % mod);
        }
    }

    void work(int needres = 1) {
        // 无根树选一个不存在的点当pre即可，当多棵无根树判重时需要sort
        dfs1(1, 0);
        dfs2(1, 0, 0, needres);
        sort(hs.begin(), hs.end());
    }
};

// 获取删掉某叶子节点后以与该叶子节点相邻点开头的hash值
// int res = (hs[edge[i][0]] - 2 + mod) % mod;