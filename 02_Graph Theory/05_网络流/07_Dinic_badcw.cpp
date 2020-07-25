const ll inf = 1e18;

struct Dinic{
#define maxn    105
#define maxm    10005
    queue <int> que;
    struct Edge{ int v, w, next; } edge[maxm];
    int first[maxn], cur[maxn], dep[maxn];
    int S, T, Top; ll flow;
    void init(int x, int y) {
        S = x, T = y, Top = 1, flow = 0;
        memset(first, 0, sizeof first);
    }
    void add(int u, int v, int w = 1){
        edge[++Top] = (Edge) {v, w, first[u]};
        first[u] = Top;
        edge[++Top] = (Edge) {u, 0, first[v]};
        first[v] = Top;
    }
    bool bfs(){
        while (que.size()) que.pop(); que.push(S);
        memset(dep, 0, sizeof dep), dep[S] = 1;
        while (que.size()){
            int u = que.front(); que.pop();
            for (int i = first[u]; i; i = edge[i].next){
                int v = edge[i].v, w = edge[i].w;
                if (!dep[v] && w) que.push(v), dep[v] = dep[u] + 1;
            }
        }
        return dep[T];
    }
    ll dinic(int u, ll flow){
        if (!flow || u == T) return flow;
        ll rest = flow;
        for (int &i = cur[u]; i; i = edge[i].next){
            int v = edge[i].v, w = edge[i].w;
            if (dep[v] != dep[u] + 1 || !w) continue;
            ll k = dinic(v, min((ll) w, rest));
            if (!k) dep[v] = -1;
            else edge[i].w -= k, edge[i ^ 1].w += k, rest -= k;
            if (!rest) return flow;
        }
        return flow - rest;
    }
    ll max_flow(){
        while (bfs()){
            memcpy(cur, first, sizeof first);
            flow += dinic(S, inf);
        }
        return flow;
    }
} G;