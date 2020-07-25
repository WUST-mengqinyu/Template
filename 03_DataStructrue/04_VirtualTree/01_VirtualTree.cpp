const int pow2 = 19;
int n;
vector<int> adj0[maxn], adj1[maxn];
int st[maxn << 1][pow2 + 1], dep[maxn], euler[maxn], euler_clock;
int stk[maxn], fa0[maxn];
vector<int> cache;
void link0(int u, int v) { adj0[u].emplace_back(v); adj0[v].emplace_back(u); }
void link1(int u, int v) { adj1[u].emplace_back(v), cache.push_back(u); }
void clearAll() {
    for (int i = 1; i <= n; ++i) {
        adj0[i].clear();
        adj1[i].clear();
    }
    euler_clock = 0;
}
void clearVT() { for (auto i : cache) adj1[i].clear(); cache.clear(); }
void dfs0(int u, int p) {
    fa0[u] = p;
    dep[u] = dep[p] + 1;
    st[++euler_clock][0] = u;
    euler[u] = euler_clock;
    for (const auto& v : adj0[u]) if (v != p) {
            dfs0(v, u);
            st[++euler_clock][0] = u;
        }
}
inline bool cmp(int u, int v) {return dep[u] < dep[v];}
inline int upper(int u, int v) {return cmp(u, v) ? u : v;}
void lca_init() {
    for (int i = 0; i != 31 - __builtin_clz(euler_clock); ++i)
        for (int j = 1; j + (1 << (i + 1)) <= euler_clock; ++j)
            st[j][i + 1] = upper(st[j][i], st[j + (1 << i)][i]);
}
inline int lca(int u, int v) {
    if (u == v) return u;
    u = euler[u];
    v = euler[v];
    if (u > v) swap(u, v);
    int temp = 31 - __builtin_clz(++v - u);
    return upper(st[u][temp], st[v - (1 << temp)][temp]);
}
// build 后 stk[1] 是该树的根节点，且为有根树
void build(vector<int>& key) {
    sort(key.begin(), key.end(), [&] (int u, int v) { return euler[u] < euler[v]; });
    key.erase(unique(key.begin(), key.end()), key.end());
    int top = 0;
    for (auto u : key) {
        if (!top) {
            stk[++top] = u;
            continue;
        }
        int p = lca(u, stk[top]);
        while (euler[p] < euler[stk[top]]) {
            if (euler[p] >= euler[stk[top - 1]]) {
                link1(p, stk[top]);
                if (stk[--top] != p) stk[++top] = p;
                break;
            }
            link1(stk[top - 1], stk[top]);
            --top;
        }
        stk[++top] = u;
    }
    while (top > 1) {
        link1(stk[top - 1], stk[top]);
        --top;
    }
}

int f[maxn];
int res;
int vis[maxn];
void dfs1(int u) {
    fa1[u] = p;
    len[u] = dep[u] - dep[p];
    for (auto v : adj1[u]) {
        dfs1(v);
    }
}

int main(int argc, char* argv[]) {
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        link0(u, v);
    }
    dfs0(1, 0);
    lca_init();
    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int sz; scanf("%d", &sz);
        vector<int> key(sz);
        for (int j = 0; j < sz; ++j) {
            scanf("%d", &key[j]);
            vis[key[j]] = 1;
        }
        build(key);
        res = 0;
        dfs1(stk[1]);
        printf("%d\n", res);
        for (int j = 0; j < sz; ++j) vis[key[j]] = 0;
        clearVT();
    }
    return 0;
}