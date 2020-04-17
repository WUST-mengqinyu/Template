// const int maxn = 1e5 + 10;

// 普通倍增lca
int n, dep[maxn], fa[maxn][30];
vector<int> edge[maxn];

void dfs(int u, int pre) {
	dep[u] = dep[pre] + 1, fa[u][0] = pre;
	for(int i = 1; (1 << i) <= n; i ++) 
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(auto v : edge[u]) if(v != pre) dfs(v, u);
}

int LCA(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	int d = dep[u] - dep[v];
	for(int i = 0; (1 << i) <= d; i ++) 
		if((1 << i) & d) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i --) 
		if(fa[u][i] != fa[v][i]) 
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}


// 欧拉序lca
// pow2 = 19
// maxn = 1 << pow2
int st[maxn << 1][pow2 + 1], dep[maxn], euler[maxn], euler_clock， fa[maxn];
void dfs(int u, int p) {
    fa[u] = p;
    dep[u] = dep[p] + 1;
    st[++euler_clock][0] = u;
    euler[u] = euler_clock;
    for (const auto& v : adj0[u]) if (v != p) {
            dfs(v, u);
            st[++euler_clock][0] = u;
        }
}
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

// dfs(1, 0);
// lca_init();

// 另有树剖lca详见hld模板