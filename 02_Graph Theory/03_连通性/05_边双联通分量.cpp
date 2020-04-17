const int maxn = 10000 + 10;

int low[maxn], dfn[maxn], head[maxn], cnt, idx;
int cutEdge[maxn << 2];
struct  Edge { int nex, v; }edge[maxn << 2];

void add(int u, int v) { edge[cnt].nex = head[u], edge[cnt].v = v, head[u] = cnt ++; }

void dfs(int u, int pre)
{
	low[u] = dfn[u] = ++idx;
	for(int i = head[u]; ~i; i = edge[i].nex)
	{
		int v = edge[i].v;
		if(v == pre) continue;
		if(!dfn[v])
		{
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) cutEdge[i] = cutEdge[i ^ 1] = 1;
		}
		else if(dfn[v] < dfn[u]) low[u] = min(low[u], dfn[v]);
	}
}