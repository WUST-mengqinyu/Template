const int pow2 = 19;
const int maxn = 1 << pow2;
vector<int> adj0[maxn], adj1[maxn];
int st[maxn << 1][pow2 + 1], dep[maxn], euler[maxn], euler_clock;
// fa0 是原树的父节点
// fa1 是虚树的父节点
// len 是虚树每个节点的权重，每个节点代表原树的几个节点，也是虚树到它父节点的链的长度
int stk[maxn], fa0[maxn], fa1[maxn], len[maxn];
ll val[maxn];

void link0(int u, int v) { adj0[u].emplace_back(v); adj0[v].emplace_back(u); }
void link1(int u, int v) { adj1[u].emplace_back(v); adj1[v].emplace_back(u); }
void dfs0(int u, int p) {
    fa0[u] = p;
    dep[u] = dep[p] + 1;
    st[++euler_clock][0] = u;
    euler[u] = euler_clock;
    for (const auto& v : adj0[u]) if (v != p) {
            dfs0(v, u);
            st[++euler_clock][0] = u;
        }
}
inline bool cmp(int u, int v) {return dep[u] < dep[v];}
inline int upper(int u, int v) {return cmp(u, v) ? u : v;}
void lca_init() {
    for (int i = 0; i != 31 - __builtin_clz(euler_clock); ++i)
        for (int j = 1; j + (1 << (i + 1)) <= euler_clock; ++j)
            st[j][i + 1] = upper(st[j][i], st[j + (1 << i)][i]);
}
inline int lca(int u, int v) {
    if (u == v) return u;
    u = euler[u];
    v = euler[v];
    if (u > v) swap(u, v);
    int temp = 31 - __builtin_clz(++v - u);
    return upper(st[u][temp], st[v - (1 << temp)][temp]);
}
void build(vector<int>& key) {
    sort(key.begin(), key.end(), [&] (int u, int v) { return euler[u] < euler[v]; });
    key.resize(unique(key.begin(), key.end()) - key.begin());
    int top = 0;
    for (const auto& u : key) {
        if (!top) {
            stk[++top] = u;
            continue;
        }
        int p = lca(u, stk[top]);
        while (euler[p] < euler[stk[top]]) {
            if (euler[p] >= euler[stk[top - 1]]) {
                link1(p, stk[top]);
                if (stk[--top] != p) stk[++top] = p;
                break;
            }
            link1(stk[top - 1], stk[top]);
            --top;
        }
        stk[++top] = u;
    }
    while (top > 1) {
        link1(stk[top - 1], stk[top]);
        --top;
    }
}

void dfs1(int u, int p) {
    fa1[u] = p;
    val[u] = 0;
    len[u] = dep[u] - dep[p];
    for (const auto& v : adj1[u]) if (v != p) dfs1(v, u);
}

int main() {
    // 多组清空操作
    for (int i = 1; i <= n; ++i) {
        adj0[i].clear();
        adj1[i].clear();
    }
    euler_clock = 0;

    // 读入原树 link0 加边
    // 读入处理关键节点存入vector key，包含1和链的端点和他们的lca的父节点（lca如果为1就不加）。
    dfs0(1, 0);
    lca_init();

    vector<int> key(1, 1);
    for (auto& q : query) {
        cin >> q.u >> q.v;
        key.emplace_back(q.u);
        key.emplace_back(q.v);
        int p = lca(q.u, q.v);
        if (p != 1) key.emplace_back(fa0[p]);
    }

    build(key);
    dfs1(1, 0);
    return 0;
}