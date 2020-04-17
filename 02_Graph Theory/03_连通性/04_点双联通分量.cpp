const int maxn = 10000 + 10;

struct Edge{ int u, v; };
vector<int> G[maxn], bcc[maxn];

int dfn[maxn], low[maxn], bccno[maxn], idx, bcc_cnt, bridge;
bool iscut[maxn];

stack<Edge> st;

void dfs(int u, int pre)
{
	dfn[u] = low[u] = ++idx;
	int child = 0;
	for(auto v : G[u])
	{
		if(v == pre) continue;
		if(!dfn[v])
		{
			child ++;
			st.push({u, v});
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u])
			{
				iscut[u] = true;
				bcc[++bcc_cnt].clear();
				Edge x;
				do
				{
					x = st.top(); st.pop();
					if(bccno[x.u] != bcc_cnt) { bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt; }
					if(bccno[x.v] != bcc_cnt) { bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt; }
				} while(x.u != u || x.v != v);
			}
			if(low[v] > dfn[u]) ++ bridge;
		}
		else if(dfn[v] < dfn[u])
		{
			st.push({u, v});
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(pre < 0 && child == 1) iscut[u] = 0;
}

void find_bcc(int n)
{
	memset(dfn, 0, sizeof dfn);
	memset(iscut, 0, sizeof iscut);
	memset(bccno, 0, sizeof bccno);
	for(int i = 1; i <= bcc_cnt; i ++) bcc[i].clear();
	idx = bcc_cnt = bridge = 0;
	for(int i = 0; i < n; i ++) if(!dfn[i]) dfs(i, -1);
}
