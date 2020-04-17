const int maxn = 1e4 + 10;

vector<int> edge[maxn];
int n, dfn[maxn], low[maxn], father[maxn], cnt = 0;
bool bridge[maxn][maxn];

void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++cnt;
    for (int i = 0; i < edge[u].size(); i++)
    {
        int v = edge[u][i];
        if (!dfn[v])    //未访问节点v
        {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) //节点v到达祖先必须经过(u,v)
                bridge[u][v] = bridge[v][u] = true;    //(u,v)是桥
        } 
        else if (fa != v)    //u的父节点不是v，（u,v)不存在重边
            low[u] = min(low[u], dfn[v]);
    }
}