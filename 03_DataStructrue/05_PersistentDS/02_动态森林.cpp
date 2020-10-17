const int maxn = 10010;
struct Splay {
    int ch[maxn][2], fa[maxn], tag[maxn];
    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }
    int getch(int x) { return ch[fa[x]][1] == x; }
    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    void pushdown(int x) {
        if (tag[x]) {
            if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
            if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
            tag[x] = 0;
        }
    }
    void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
    }
    void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
            if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
    }
    void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f;
    }
    void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
    }
    int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
    }
} st;

// 动态森林
namespace LCT {
    void clear(int n) { for (int i = 0; i <= n; ++i) st.clear(i); }
    bool isConnect(int u, int v) { return st.find(u) == st.find(v); }
    bool add(int u, int v) {
        if (isConnect(u, v)) return false;
        st.makeroot(u), st.fa[u] = v;
        return true;
    }
    // 无法判断是否存在直接相连的边
    void del(int u, int v) {
        st.makeroot(u);
        st.access(v);
        st.splay(v);
        if (st.ch[v][0] == u && !st.ch[u][1]) st.ch[v][0] = st.fa[u] = 0;
    }
}
using namespace LCT;
