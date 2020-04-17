struct MCMF
{
    int last[maxn], dis[maxn], cnt, ans;
    int s, t;
    bool vis[maxn];
    struct edge { int from, to, cap, w, op, nex; } e[500000 + 10];
 
    void init(int S, int T)
    {
        s = S, t = T;
        cnt = 0, ans = 0;
        memset(vis, 0, sizeof vis);
        memset(dis, 0, sizeof dis);
        memset(last, 0, sizeof last);
    }
 
    void add(int u, int v, int cap, int cost)
    {
        e[++ cnt] = { u, v, cap, cost, cnt + 1, last[u] };
        last[u] = cnt;
        e[++ cnt] = { v, u, 0, -cost, cnt - 1, last[v] };
        last[v] = cnt;
    }
 
    int dfs(int x, int maxf)
    {
        if(x == t || maxf == 0) return maxf;
        int ret = 0;
        vis[x] = 1;
        for(int i = last[x]; i; i = e[i].nex)
            if(e[i].cap && dis[e[i].to] + e[i].w == dis[x] && !vis[e[i].to])
            {
                int f = dfs(e[i].to, min(e[i].cap, maxf - ret));
                ans += f * e[i].w;
                e[i].cap -= f;
                e[e[i].op].cap += f;
                ret += f;
                if(ret == maxf) break;
            }
        return ret;
    }
 
    bool change()
    {
        int mn = inf;
        for(int i = 0; i <= t; i ++)
            if(vis[i])
                for(int j = last[i]; j; j = e[j].nex)
                    if(!vis[e[j].to] && e[j].cap) mn = min(mn, -dis[i] + e[j].w + dis[e[j].to]);
        if(mn == inf) return false;
        for(int i = 0; i <= t; i ++) if(vis[i]) dis[i] += mn;
        return true;
    }
 
    void zkw()
    {
        do
        {
            for(int i = 0; i <= t; i ++) vis[i] = 0;
            while(dfs(s, inf)) for(int i = 0; i <= t; i ++) vis[i] = 0;
        }
        while(change());
    }
}ans;
