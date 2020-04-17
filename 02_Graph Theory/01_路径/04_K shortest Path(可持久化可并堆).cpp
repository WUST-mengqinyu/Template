#include <bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

using namespace std;

const int N = '';
const int M = '';
const int logM = 20;
const int inf = 0x3f3f3f3f;

int n, m, k, S, T;

struct Edge{ int nex, to, w; };

struct Graph
{
    int head[N], cnt;
    Edge edge[M];
    void init(int n) { for(int i = 0; i <= n; i ++) head[i] = 0; cnt = 0; }
    void addedge(int u, int v, int val) { edge[++ cnt].nex = head[u], edge[cnt].to = v, edge[cnt].w = val, head[u] = cnt; }
}g, rg;

int dis[N];

void dijkstra()
{
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    memset(dis, inf, sizeof dis);
    que.push({0, T}); dis[T] = 0;
    const int *head = rg.head; const Edge *edge = rg.edge;
    while(!que.empty())
    {
        auto f = que.top(); que.pop();
        int u = f.second, d = f.first;
        if(d != dis[u]) continue;
        for(int i = head[u]; i; i = edge[i].nex)
        {
            int v = edge[i].to, w = edge[i].w;
            if(dis[u] + w < dis[v]) { dis[v] = dis[u] + w; que.push({dis[v], v}); }
        }
    }
}

bool tree_edge[M], vis[N];
int fa[N], st[N], top;

void dfs(int u)
{
    vis[u] = true;
    st[++ top] = u;
    for(int i = rg.head[u]; i; i = rg.edge[i].nex)
    {
        int v = rg.edge[i].to;
        if(!vis[v] && dis[v] == dis[u] + rg.edge[i].w)
        {
            fa[v] = u;
            tree_edge[i] = true;
            dfs(v);
        }
    }
}

namespace LT
{
    int son[M * logM][2];
    int ht[M * logM], val[M * logM], id[M * logM];
    int tot;

    int newnode(int _val, int _id, int _dis = 0)
    {
        int now = ++ tot;
        val[now] = _val, id[now] = _id;
        ht[now] = _dis, son[now][0] = son[now][1] = 0;
        return now;
    }

    int _copy(int ori)
    {
        int now = ++tot;
        val[now] = val[ori], id[now] = id[ori];
        ht[now] = ht[ori], son[now][0] = son[ori][0], son[now][1] = son[ori][1];
        return now;
    }

    int merge(int a, int b)
    {
        if(!a || !b) return a | b;
        if(val[a] > val[b]) swap(a, b);
        int now = _copy(a);
        son[now][1] = merge(son[now][1], b);
        if(ht[son[now][0]] < ht[son[now][1]]) swap(son[now][0], son[now][1]);
        ht[now] = ht[son[now][1]] + 1;
        return now;
    }

    void insert(int &rt, int val, int id) { rt = merge(newnode(val, id), rt); }
}

int rt[M];

void build_heap()
{
    for(int i = 1; i <= top; i ++)
    {
        int u = st[i];
        rt[u] = rt[fa[u]];
        for(int i = g.head[u]; i; i = g.edge[i].nex)
        {
            int v = g.edge[i].to;
            if(!tree_edge[i] && dis[v] != inf) LT::insert(rt[u], dis[v] - dis[u] + g.edge[i].w, v);
        }
    }
}

int solve(int k)
{
    if(k == 1) return dis[S];
    __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int> > > que;
    que.push({dis[S] + LT::val[rt[S]], rt[S]});
    while(!que.empty())
    {
        pair<int, int> f = que.top(); que.pop();
        if((--k) == 1) return f.first;
        int v = f.first, u = f.second;
        int lc = LT::son[u][0], rc = LT::son[u][1], o = LT::id[u];
        if(rt[o]) que.push({v + LT::val[rt[o]], rt[o]});
        if(lc) que.push({v + LT::val[lc] - LT::val[u], lc});
        if(rc) que.push({v + LT::val[rc] - LT::val[u], rc});
    }
    return -1;
}

void init()
{
    g.init(n), rg.init(n);
    memset(rt, 0, sizeof rt);
    memset(tree_edge, 0, sizeof tree_edge);
    top = LT::tot = 0;
}

void getans()
{
    //input S-T
    init();
    dijkstra();
    dfs(T);
    build_heap();
    cout << solve(k);
}
