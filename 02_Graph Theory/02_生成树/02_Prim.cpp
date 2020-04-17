const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;

int n, mp[maxn][maxn], cost[maxn];
bool vis[maxn];

int prim()
{
	for(int i = 0; i < n; i ++) cost[u] = inf, vis[u] = false;
	int res = 0; cost[0] = 0;
	for(;;)
	{
		int v = -1;
		for(int u = 0; u < n; u ++)
			if(!vis[u] && (v == -1 || cost[u] < cost[v])) v = u;
		if(v == -1) break;
		res += cost[v];
		vis[v] = true;
		for(int u = 0; u < n; u ++) cost[u] = min(cost[u], mp[v][u]);
	}
	return res; 
}