//以$x_i-x_j≤y$为约束条件，建图求最短路后得到的是最大解。所有的解都不大于且尽可能逼近$dis[x0]$
//最短路对应最大解，最长路对应最小解

const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;

struct Edge
{
    int nex, to, w;
} edge[10 * maxn];

int head[maxn], cnt, dis[maxn], n;
bool vis[maxn];

void init()
{
    cnt = 0;
    memset(head, 0xff, sizeof head);
}

void add(int u, int v, int w)
{
    edge[cnt].nex = head[u];
    edge[cnt].to = v;
    edge[cnt].w = w;
    head[u] = ++cnt;
}

void spfa(int u)
{
    int u, v, w;
    for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = false;
    dis[u] = 0;
    queue<int> que;
    que.push(u);
    vis[u] = true;
    while (!que.empty())
    {
        u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = edge[i].nex)
        {
            v = edge[i].v, w = edge[i].w;
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                if (!vis[v])
                {
                    que.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}