#include <bits/stdc++.h>
#define ll long long
using namespace std;
/*
node 计算点权， path 下放后计算边权， edge 根据边的编号计算边权
work 中没有build需手动写
sz[]数组，以x为根的子树节点个数
top[]数组，当前节点的所在链的顶端节点
son[]数组，重儿子
deep[]数组，当前节点的深度
fa[]数组，当前节点的父亲
idx[]数组，树中每个节点剖分后的新编号
rnk[]数组，idx的逆，表示线段上中当前位置表示哪个节点
*/

const int maxn = 1e5+5;

int sz[maxn], top[maxn], son[maxn], deep[maxn], fa[maxn], idx[maxn], rnk[maxn];
int tot;
int n, le, re;
ll k;

struct HLD {
#define type int

    struct edge {
        int a, b;
        type v;

        edge(int _a, int _b, type _v = 0) : a(_a), b(_b), v(_v) {}
    };

    struct node {
        int to;
        type w;

        node() {}

        node(int _to, type _w) : to(_to), w(_w) {}
    };

    vector<int> mp[maxn];
    vector<edge> e;

    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; i++) mp[i].clear();
        e.clear();
        e.push_back(edge(0, 0));
    }

    void add_edge(int a, int b, type v = 0) {
//        e.push_back(edge(a,b,v));
        mp[a].push_back(b);
        mp[b].push_back(a);
    }

    void dfs1(int x, int pre, int h) {
        int i, to;
        deep[x] = h;
        fa[x] = pre;
        sz[x] = 1;
        for (i = 0; i < (int) (mp[x].size()); i++) {
            to = mp[x][i];
            if (to == pre) continue;
            dfs1(to, x, h + 1);
            sz[x] += sz[to];
            if (son[x] == -1 || sz[to] > sz[son[x]]) son[x] = to;
        }
    }

    void dfs2(int x, int tp) {
        int i, to;
        top[x] = tp;
        idx[x] = ++tot;
        rnk[idx[x]] = x;
        if (son[x] == -1) return;
        dfs2(son[x], tp);
        for (i = 0; i < (int) (mp[x].size()); i++) {
            to = mp[x][i];
            if (to != son[x] && to != fa[x]) dfs2(to, to);
        }
    }

    void work(int _rt = 1) {
        memset(son, -1, sizeof son);
        tot = 0;
        dfs1(_rt, 0, 0);
        dfs2(_rt, _rt);
    }

    int LCA(int x, int y) {
        while (top[x] != top[y]) {
            if (deep[top[x]] < deep[top[y]]) swap(x, y);
            x = fa[top[x]];
        }
        if (deep[x] > deep[y]) swap(x, y);
        return x;
    }

    void modify_node(int x, int y, type val) {
        while (top[x] != top[y]) {
            if (deep[top[x]] < deep[top[y]]) swap(x, y);
            le = idx[top[x]], re = idx[x];
            k = val;
            update(1, 1, n);
            x = fa[top[x]];
        }
        if (deep[x] > deep[y]) swap(x, y);
        le = idx[x], re = idx[y];
        k = val;
        update(1, 1, n);
    }

    type query_node(int x, int y) {
        type res = 0;
        while (top[x] != top[y]) {
            if (deep[top[x]] < deep[top[y]]) swap(x, y);
            le = idx[top[x]], re = idx[x];
            res += query(1, 1, n);
            x = fa[top[x]];
        }
        if (deep[x] > deep[y]) swap(x, y);
        le = idx[x], re = idx[y];
        res += query(1, 1, n);
        return res;
    }

    //path
//    void init_path()
//    {
//        v[idx[rt]]=0;
//        for(int i=1;i<n;i++)
//        {
//            if(deep[e[i].a]<deep[e[i].b]) swap(e[i].a,e[i].b);
//            a[idx[e[i].a]]=e[i].v;
//        }
//        build(n);
//    }
    void modify_edge(int id, type val) {
        if (deep[e[id].a] > deep[e[id].b]) {
            le = idx[e[id].a], re = idx[e[id].a];
            k = val;
            update(1, 1, n);
        } else {
            le = idx[e[id].b], re = idx[e[id].b];
            k = val;
            update(1, 1, n);
        }
    }

    void modify_path(int x, int y, type val) {
        while (top[x] != top[y]) {
            if (deep[top[x]] < deep[top[y]]) swap(x, y);
            le = idx[top[x]], re = idx[x];
            k = val;
            update(1, 1, n);
            x = fa[top[x]];
        }
        if (deep[x] > deep[y]) swap(x, y);
        if (x != y) {
            le = idx[x] + 1, re = idx[y];
            k = val;
            update(1, 1, n);
        }
    }

    type query_path(int x, int y) {
        type res = 0;
        while (top[x] != top[y]) {
            if (deep[top[x]] < deep[top[y]]) swap(x, y);
            le = idx[top[x]], re = idx[x];
            res += query(1, 1, n);
            x = fa[top[x]];
        }
        if (deep[x] > deep[y]) swap(x, y);
        if (x != y) {
            le = idx[x] + 1, re = idx[y];
            res += query(1, 1, n);
        }
        return res;
    }

#undef type
} hld;