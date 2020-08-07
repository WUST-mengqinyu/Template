/*2-SAT连边含义：选A必选B
    点$x_i$表示选，$x_i'$表示不选
    1.必选$x_i$，等价于$x_i=1$：$x_i'→x_i$
    2.必不选$x_i$，等价于$x_i=0$，$x_i→x_i'$
    3.$x_i$与$x_j$中至少选择一个，等价于$x_iORx_j=1$，连边$x_i'→x_j$,$x_j'→x_i$
    4.$x_i$与$x_j$不都选，等价于$x_iANDx_j=0$，连边$x_i→x_j',x_j→x_i'$
    5.$x_i$与$x_j$情况相同，等价于$x_iXORx_j=0$，连边$x_i→x_j$,$x_i'→x_j'$,$x_j→x_i$,$x_j'→x_i'$
    6.$x_i$与$x_j$情况相反，等价于$x_iXORx_j=1$，连边$x_i→x_j'$,$x_i'→x_j$,$x_j→x_i'$,$x_j'→x_i$
*/

const int maxn = 2e6 + 10;

namespace twosat {
    int n;
    int low[maxn], dfn[maxn], color[maxn], cnt, scc_cnt;
    bool instack[maxn];

    vector<int> g[maxn];
    stack<int> st;
    
    void init(int _n) {
        n = _n;
        cnt = scc_cnt = 0;
        for (int i = 0; i <= n * 2; ++i) {
            dfn[i] = 0;
            g[i].clear();
        }
    }

    void Tarjan(int u) {
        low[u] = dfn[u] = ++cnt;
        st.push(u);
        instack[u] = true;
        for (const auto &v : g[u]) {
            if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
            else if (instack[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            ++scc_cnt;
            do {
                color[u] = scc_cnt;
                u = st.top();
                st.pop();
                instack[u] = false;
            } while (low[u] != dfn[u]);
        }
    }

    inline void add(int a, int b) { g[a].push_back(b); }

    inline void AND(int a, int b, int c) {
        if (c == 1) add(a, a + n), add(b, b + n);
        else add(a, b + n), add(b, a + n);
    }

    inline void OR(int a, int b, int c) {
        if (c == 0) add(a + n, a), add(b + n, b);
        else add(a + n, b), add(b + n, a);
    }

    inline void XOR(int a, int b, int c) {
        if (c == 0) add(a, b), add(a + n, b + n), add(b, a), add(b + n, a + n);
        else add(a, b + n), add(a + n, b), add(b, a + n), add(b + n, a);
    }

    bool TWO_SAT() {
        for (int i = 1; i <= (n << 1); i++) if (!dfn[i]) Tarjan(i);
        for (int i = 1; i <= n; i++)
            if (color[i] == color[i + n]) return false;
        for (int i = 1; i <= n; i++)
            printf("%d ", color[i] > color[i + n]);
        return true;
    }
}