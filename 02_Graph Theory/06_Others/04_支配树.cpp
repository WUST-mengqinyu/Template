const int N = 2e5 + 10;

int n, m;

struct G
{
	vector<int> edge[N];
	inline void add(int u, int v) { edge[u].push_back(v); }
}a, b, c, d;

int dfn[N], id[N], fa[N], cnt;

void dfs(int u)
{
	dfn[u] = ++ cnt; id[cnt] = u;
	int len = a.edge[u].size();
	for(auto v : a.edge[u]) if(!dfn[v]) { fa[v] = u; dfs(v); }
}

int semi[N], idom[N], belong[N], val[N];

int find(int x)
{
	if(x == belong[x]) return x;
	int tmp = find(belong[x]);
	if(dfn[semi[val[belong[x]]]] < dfn[semi[val[x]]]) val[x] = val[belong[x]];
	return belong[x] = tmp;
}

void tarjan()
{
	for(int i = cnt; i > 1; i --)
	{
		int u = id[i];
		for(auto v : b.edge[u])
		{
			if(!dfn[v]) continue;
			find(v);
			if(dfn[semi[val[v]]] < dfn[semi[u]]) semi[u] = semi[val[v]];
		}
		c.add(semi[u], u);
		belong[u] = fa[u];
		u = fa[u];
		for(auto v : c.edge[u])
		{
			find(v);
			if(semi[val[v]] == u) idom[v] = u;
			else idom[v] = val[v];
		}
	}
	for(int i = 2; i <= cnt; i ++)
	{
		int u = id[i];
		if(idom[u] != semi[u]) idom[u] = idom[idom[u]];
	}
}

int ans[N];

void dfs_ans(int u)
{
	ans[u] = 1;
	for(auto v : d.edge[u]) dfs_ans(v), ans[u] += ans[v];
}

void solve()
{
    int u, v;
    scanf("%d%d", &n, &m);
    while(m --)
    {
        scanf("%d%d", &u, &v);
        a.add(u, v);
        b.add(v, u);
    }
	for(int i = 1; i <= n; i ++) semi[i] = belong[i] = val[i] = i;
	dfs(1);
	tarjan();
	for(int i = 2; i <= n; i ++) d.add(idom[i], i);
	dfs_ans(1);
	for(int i = 1; i <= n; i ++) printf("%d ", ans[i]);
}