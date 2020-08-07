//复杂度O(n^0.5*m)
struct Hopcroft {
#define maxn 100005
#define maxm 100005
#define INF 0x3f3f3f3f
    struct Edge { int v, next; } edge[maxm];
    int nx, cnt, dis;
    int first[maxn];
    int xlink[maxn], ylink[maxn];
    int dx[maxn], dy[maxn];
    int vis[maxn];

    void init(int n) {
        cnt = 0;
        for (int i = 0; i <= n; ++i) first[i] = ylink[i] = xlink[i] = -1;
        nx = n + 1;
    }

    void add_edge(int u, int v) {
        edge[cnt].v = v, edge[cnt].next = first[u], first[u] = cnt++;
    }

    int bfs() {
        queue<int> q;
        dis = INF;
        for (int i = 0; i < nx; ++i) dx[i] = dy[i] = -1;
        for (int i = 0; i < nx; i++) {
            if (xlink[i] == -1) {
                q.push(i);
                dx[i] = 0;
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dx[u] > dis) break;
            for (int e = first[u]; e != -1; e = edge[e].next) {
                int v = edge[e].v;
                if (dy[v] == -1) {
                    dy[v] = dx[u] + 1;
                    if (ylink[v] == -1) dis = dy[v];
                    else {
                        dx[ylink[v]] = dy[v] + 1;
                        q.push(ylink[v]);
                    }
                }
            }
        }
        return dis != INF;
    }

    int find(int u) {
        for (int e = first[u]; e != -1; e = edge[e].next) {
            int v = edge[e].v;
            if (!vis[v] && dy[v] == dx[u] + 1) {
                vis[v] = 1;
                if (ylink[v] != -1 && dy[v] == dis) continue;
                if (ylink[v] == -1 || find(ylink[v])) {
                    xlink[u] = v, ylink[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

    int maxmatch() {
        int ans = 0;
        for (int i = 0; i < nx; ++i) vis[i] = 0;
        while (bfs()) {
            for (int i = 0; i < nx; ++i) vis[i] = 0;
            for (int i = 0; i < nx; i++)
                if (xlink[i] == -1)
                    ans += find(i);
        }
        return ans;
    }

#undef maxn
#undef maxm
} solve;