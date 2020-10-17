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