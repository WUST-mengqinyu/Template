//复杂度O(n^0.5*m),注意这个板子的下标是从0开始的

const int MAXN = 3010;//左边节点数量、右边节点数量
const int MAXM = 3010 * 3010;//边的数量
const int INF = 0x3f3f3f3f;

struct Edge
{
    int v;
    int next;
} edge[MAXM];

int nx, ny;
int cnt;
int dis;

int first[MAXN];
int xlink[MAXN], ylink[MAXN];
/*xlink[i]表示左集合顶点所匹配的右集合顶点序号，ylink[i]表示右集合i顶点匹配到的左集合顶点序号。*/
int dx[MAXN], dy[MAXN];
/*dx[i]表示左集合i顶点的距离编号，dy[i]表示右集合i顶点的距离编号*/
int vis[MAXN]; //寻找增广路的标记数组

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
    memset(xlink, -1, sizeof(xlink));
    memset(ylink, -1, sizeof(ylink));
}

void read_graph(int u, int v)
{
    edge[cnt].v = v;
    edge[cnt].next = first[u], first[u] = cnt++;
}

int bfs()
{
    queue<int> q;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i = 0; i < nx; i++)
    {
        if (xlink[i] == -1)
        {
            q.push(i);
            dx[i] = 0;
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (dx[u] > dis) break;
        for (int e = first[u]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v;
            if (dy[v] == -1)
            {
                dy[v] = dx[u] + 1;
                if (ylink[v] == -1) dis = dy[v];
                else
                {
                    dx[ylink[v]] = dy[v] + 1;
                    q.push(ylink[v]);
                }
            }
        }
    }
    return dis != INF;
}

int find(int u)
{
    for (int e = first[u]; e != -1; e = edge[e].next)
    {
        int v = edge[e].v;
        if (!vis[v] && dy[v] == dx[u] + 1)
        {
            vis[v] = 1;
            if (ylink[v] != -1 && dy[v] == dis) continue;
            if (ylink[v] == -1 || find(ylink[v]))
            {
                xlink[u] = v, ylink[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int MaxMatch()
{
    int ans = 0;
    while (bfs())
    {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < nx; i++)
            if (xlink[i] == -1)
                ans += find(i);
    }
    return ans;
}