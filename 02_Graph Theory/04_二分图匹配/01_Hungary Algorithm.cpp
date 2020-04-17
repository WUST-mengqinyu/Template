const int maxn = 150;

int n;
int edge[maxn][maxn];
int linker[maxn];
bool vis[maxn];

bool path(int u)
{
    for (int v = 1; v <= n; v++)
    {
        if (edge[u][v] && !vis[v])
        {
            vis[v] = true;
            if (linker[v] == -1 || path(linker[v]))
            {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    int res = 0;
    memset(linker, 0xff, sizeof(linker));
    for (int i = 1; i <= n; i++)
    {
        memset(vis, false, sizeof(vis));
        res += path(i);
    }
    return res;
}