const int inf = 0x3f3f3f3f;
const int maxn = 1000 + 10;
const int maxm = 100000 + 10;

int n, k, cnt, head[maxn], revhead[maxn], dis[maxn];
bool vis[maxn];

struct node { int v, w, nex; } edge[maxm], revedge[maxm];

void init()
{
    cnt = 0;
    memset(head, 0xff, sizeof head);
    memset(revhead, 0xff, sizeof revhead);
}

void add(int u, int v, int w)
{
    edge[cnt].v = v, revedge[cnt].v = u;
    edge[cnt].w = revedge[cnt].w = w;
    edge[cnt].nex = head[u];
    revedge[cnt].nex = revhead[v];
    head[u] = revhead[v] = cnt;
    cnt++;
}

void spfa(int src)      //建立反向图，求图中所有点到终点的最短路径
{
    for (int i = 1; i <= n; i++) dis[i] = inf;
    memset(vis, false, sizeof vis);
    vis[src] = 0;
    queue<int> que;
    que.push(src);
    dis[src] = 0;
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = revhead[u]; ~i; i = revedge[i].nex)
        {
            int v = revedge[i].v, w = revedge[i].w;
            if (dis[v] > dis[u] + w)
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

struct A
{
    int f, g, h;    //f(n),g(n),h(n)函数
    int id;        //当前点的编号
    bool operator<(const A a) const
    {        //定义比较函数
        if (a.f == f) return a.g < g;
        return a.f < f;
    }
};

int Astar(int src, int des)
{
    int cnt = 0;
    priority_queue <A> Q;
    if (src == des) k++;   //如果起点即为终点
    if (dis[src] == inf) return -1;      //如果起点不能到达终点
    A st, now, tmp;
    st.id = src, st.g = 0, st.f = st.g + dis[src];    //定义起始节点
    Q.push(st);
    while (!Q.empty())
    {
        now = Q.top();
        Q.pop();
        if (now.id == des)     //如果当前节点为终点
        {
            cnt++;
            if (cnt == k) return now.g;    //找到第k短路
        }
        for (int i = head[now.id]; ~i; i = edge[i].nex)
        {
            tmp.id = edge[i].v;
            tmp.g = now.g + edge[i].w;     //到该点的实际花费
            tmp.f = tmp.g + dis[tmp.id];   //到最终状态的估计花费
            Q.push(tmp);
        }
    }
    return -1;  //路径总数小于k
}

int main()
{
    int m, s, t, u, v, w;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        init();
        while (m--)
        {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
        }
        scanf("%d%d%d", &s, &t, &k);
        spfa(t);    //求所有点到终点的最短路
        printf("%d\n", Astar(s, t));
    }
    return 0;
}
