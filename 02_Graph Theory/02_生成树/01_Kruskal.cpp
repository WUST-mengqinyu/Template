const int maxn = 1e5 + 10;

int n, m, pre[maxn];
struct edge {int u, v, w; } es[maxn];
int Find(int x) { return x == pre[x] ? x : pre[x] = Find(pre[x]); }
bool cmp(const edge &x, const edge &y) { return x.cost < y.cost; }

int kruskal()
{
	sort(es, es + m, cmp);
	int res = 0;
	for(int i = 0; i < m; i ++)
	{
		int fx = Find(es[i].u), fy = Find(es[i].v);
		if(fx != fy) pre[fx] = fy, res += es[i].cost;
	}
	return res;
}