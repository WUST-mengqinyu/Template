const int maxn = 1e4 + 10;

vector<int> edge[maxn];
int n, dfn[maxn], low[maxn], cnt = 0;
bool vis[maxn], cut[maxn];

void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++cnt;
    vis[u] = true;
    int children = 0;
    for (int i = 0; i < edge[u].size(); i++)
    {
        int v = edge[u][i];
        if (v != fa && vis[v])
            low[u] = min(low[u], dfn[v]);
        else if (!vis[v])
        {
            Tarjan(v, u);
            children++;
            low[u] = min(low[u], low[v]);
            if (fa == -1 && children > 1) //若u是根节点且子节点数大于1
                cut[u] = true;    //u是割点
            else if (fa != -1 && low[v] >= dfn[u])    //若u不是根节点且v不能访问到u的父节点
                cut[u] = true;    //u是割点
        }
    }
}