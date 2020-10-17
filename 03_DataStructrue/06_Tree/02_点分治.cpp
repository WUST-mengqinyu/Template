int n, k;

// 清零 head 和 tot
const int maxm = maxn * 2;
int ver[maxm], Next[maxm], head[maxn], edge[maxm];
int tot;
void addEdge(int u, int v, int w){
    ver[++tot]=v;
    Next[tot]=head[u];
    head[u]=tot;
    edge[tot]=w;
}

int sz[maxn], vis[maxn];
int rt, mxsz, has;

void getrt(int u, int pre) {
    sz[u] = 1;
    int mxnow = 0;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (v == pre || vis[v]) continue;
        getrt(v, u);
        sz[u] += sz[v];
        mxnow = max(mxnow, sz[v]);
    }
    mxnow = max(mxnow, has - sz[u]);
    if (mxnow < mxsz) {
        mxsz = mxnow, rt = u;
    }
}

int dl[maxn], r;
int val[maxn];

void getdis(int u, int pre) {
    dl[r++] = val[u];
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (v == pre || vis[v]) continue;
        val[v] = val[u] + edge[i];
        getdis(v, u);
    }
}

ll cal(int u, int pre) {
    r = 0;
    val[u] = pre;
    getdis(u, 0);
    ll sum = 0;
    sort(dl, dl + r);
    r --;
    int l = 0;
    while (l < r) {
        if (dl[l] + dl[r] > k) r --;
        else sum += r - l, l ++;
    }
    return sum;
}

ll res = 0;
void dfs(int u) {
    res += cal(u, 0);
    vis[u] = 1;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (vis[v]) continue;
        res -= cal(v, edge[i]);
        has = sz[v];
        mxsz = 0x3f3f3f3f;
        getrt(v, 0);
        dfs(rt);
    }
}

int main(int argc, char* argv[]) {
    while (scanf("%d%d", &n, &k) != EOF && (n || k)) {
        tot = 0; memset(head, 0, sizeof head);
        memset(vis, 0, sizeof vis);
        res = 0;
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        mxsz = 0x3f3f3f3f;
        has = n;
        getrt(1, 0);
        dfs(rt);
        printf("%lld\n", res);
    }
    return 0;
}