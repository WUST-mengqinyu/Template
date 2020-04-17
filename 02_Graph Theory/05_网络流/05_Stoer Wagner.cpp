#define INF 100000000
bool vis[maxn], com[maxn];
int mp[maxn][maxn], w[maxn], s, t;

int maxadj(int n, int v) {
    int CUT = 0;
    memset(vis, 0, sizeof vis);
    memset(w, 0, sizeof w);
    for (int i = 0; i < n; ++i) {
        int num = 0, mx = -INF;
        for (int j = 0; j < v; ++j) {
            if (!com[j] && !vis[j] && w[j] > mx) {
                mx = w[j];
                num = j;
            }
        }
        vis[num] = 1;
        s = t;
        t = num;
        CUT = w[t];
        for (int j = 0; j < v; ++j) {
            if (!com[j] && !vis[j]) w[j] += mp[num][j];
        }
    }
    return CUT;
}

int stoer(int v) {
    int mincut = INF;
    int n = v;
    memset(com, 0, sizeof com);
    for (int i = 0; i < v - 1; ++i) {
        int cut;
        s = 0, t = 0;
        cut = maxadj(n, v);
        n --;
        if (cut < mincut) mincut = cut;
        com[t] = 1;
        for (int j = 0; j < v; ++j) {
            if (!com[j]) {
                mp[j][s] += mp[j][t];
                mp[s][j] += mp[t][j];
            }
        }
    }
    return mincut;
}