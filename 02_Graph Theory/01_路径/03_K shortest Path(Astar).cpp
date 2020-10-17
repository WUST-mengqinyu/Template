// 有向图 k 短路
const int N = 1010, M = 10010, inf = 1e9+50;
int n, m;
int g[N], h[N], v[M<<1], w[M<<1], nxt[M<<1], ed, d[N], vis[N], ans[N];
typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> > Q;
void add(int x, int y, int z) {
    v[++ed] = x, w[ed] = z, nxt[ed] = g[y], g[y] = ed;
    v[++ed] = y, w[ed] = z, nxt[ed] = h[x], h[x] = ed;
}

int KthShortest(int S, int T, int k) {
    int x;
    for (int i = 1; i <= k; ++i) ans[i] = -1;
    for (int i = 1; i <= n; ++i) d[i] = inf;
    Q.push(P(d[T] = 0, T));
    while (!Q.empty()) {
        P t = Q.top(); Q.pop();
        if (d[t.second] < t.first) continue;
        for (int i = g[x = t.second]; i; i = nxt[i]) {
            if (d[x] + w[i] < d[v[i]]) Q.push(P(d[v[i]] = d[x] + w[i], v[i]));
        }
    }
    if (d[S] < inf) Q.push(P(d[S], S));
    while (!Q.empty()) {
        P t = Q.top(); Q.pop(); vis[x = t.second] ++;
        if (x == T && vis[T] <= k) ans[vis[T]] = t.first;
        if (vis[T] > k) break;
        if (vis[x] <= k) for (int i = h[x]; i; i = nxt[i]) {
            Q.push(P(t.first - d[x] + d[v[i]] + w[i], v[i]));
        }
    }
    return ans[k];
}