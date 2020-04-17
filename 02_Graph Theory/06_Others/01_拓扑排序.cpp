const int maxn = 1e5 + 10;

vector<int> edge[maxn];
int indegree[maxn];

void add(int u, int v)
{
    edge[u].push_back(v);
    indegree[v]++;
}

void Toposort(int n)
{
    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!indegree[i]) que.push(i);    //将图中没有前驱，即入度为0的点加入队列
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        indegree[u] = -1;    //从图中删去此顶点	
        for (int i = 0; i < edge[u].size(); i++)
        {
            int v = edge[u][i];
            indegree[v]--;    //删去图中以u为尾的弧
            if (!indegree[v]) que.push(v);    //将新增的当前入度为0的点压入队列中
        }
    }
}