// rnk保存欧拉序
int sz[maxn], top[maxn], son[maxn], deep[maxn], fa[maxn], idx[maxn], ed[maxn], rnk[maxn*2];
int tot, n, m;
vector<int> edge[maxn];
int val[maxn];
vector<int> xpos;

inline void dfs1(int u, int pre, int h) {
    deep[u] = h;
    fa[u] = pre;
    sz[u] = 1;
    for (auto to : edge[u]) {
        if (to == pre) continue;
        dfs1(to, u, h + 1);
        sz[u] += sz[to];
        if (son[u] == 0 || sz[to] > sz[son[u]]) son[u] = to;
    }
}

inline void dfs2(int u, int tp) {
    top[u] = tp;
    idx[u] = ++tot, rnk[tot] = u;
    if (son[u] == 0) {
        ed[u] = ++tot, rnk[tot] = u;
        return;
    }
    dfs2(son[u], tp);
    for (auto to : edge[u]) {
        if (to != son[u] && to != fa[u]) dfs2(to, to);
    }
    ed[u] = ++tot, rnk[tot] = u;
}

inline int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if (deep[x] > deep[y]) swap(x, y);
    return x;
}

int belong[maxn*2], block;
int res[maxn], ans;
// 每个点是否访问（欧拉序去重）
int vis[maxn];
// 标记数组
int pre[maxn];
struct MO {
    int l, r, id, lca;
    bool operator < (const MO& oth) const {
        return belong[l] == belong[oth.l] ? r < oth.r : belong[l] < belong[oth.l];
    }
}q[maxm];

inline void add(int x) {
    pre[x] ++;
    if (pre[x] == 1) ans ++;
}

inline void del(int x) {
    pre[x] --;
    if (pre[x] == 0) ans --;
}

inline void deal(int x) {
    vis[x] ? del(val[x]) : add(val[x]);
    vis[x] = !vis[x];
}

int main(int argc, char* argv[]) {
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    xpos.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &val[i]);
        xpos[i] = val[i];
    }
    sort(xpos.begin(), xpos.end());
    xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
    for (int i = 1; i <= n; ++i) val[i] = lower_bound(xpos.begin(), xpos.end(), val[i]) - xpos.begin();
    // 欧拉序长度为n两倍所以分块要分两倍大小
    for (int i = 1; i <= n * 2; ++i) {
        belong[i] = (i - 1) / block + 1;
    }
    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    // 树剖预处理lca
    dfs1(1, 0, 0);
    dfs2(1, 1);
    for (int i = 1, x, y; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        if (idx[x] > idx[y]) swap(x, y);
        int _lca = LCA(x, y);
        q[i].id = i;
        if (_lca == x) q[i].l = idx[x], q[i].r = idx[y], q[i].lca = 0;
        else q[i].l = ed[x], q[i].r = idx[y], q[i].lca = _lca;
//        cerr << q[i].l << " " << q[i].r << " " << q[i].id << " " << q[i].lca << endl;
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while(r < q[i].r) deal(rnk[++r]);
        while(r > q[i].r) deal(rnk[r--]);
        while(l < q[i].l) deal(rnk[l++]);
        while(l > q[i].l) deal(rnk[--l]);
        if (q[i].lca) deal(q[i].lca);
        res[q[i].id] = ans;
        if (q[i].lca) deal(q[i].lca);
    }
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", res[i]);
    }
    return 0;
}