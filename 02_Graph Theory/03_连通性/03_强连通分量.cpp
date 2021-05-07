const int maxn=1000+10;

vector<int> edge[maxn];

int dfn[maxn], low[maxn];
int st[maxn], idx, tot;
int belong[maxn], scc;
bool vis[maxn];

void add(int u, int v)
{
	edge[u].push_back(v);
	edge[v].push_back(u);
}

void Tarjan(int u)
{
    dfn[u] = low[u] = ++tot;
    st[++idx] = u;
    vis[u] = true;
    int v;
    for(v : edge[u])
    {
        if(!dfn[v])
        {
            Tarjan(v);
            low[u] = min(low[v], low[u]);
        }
        else if(vis[v]) low[u] = min(low[v], dfn[u]);
    }
    if(dfn[u] == low[u])
    {
        scc++;
        do
        {
            v = st[idx--];
            vis[v] = false;
            belong[v] = scc;
        }while(v != u);
    }
}