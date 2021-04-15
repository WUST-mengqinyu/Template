/*================================================================
*
*   创 建 者： badcw
*   创建日期： 2020/12/27 10:56 下午
*
================================================================*/
#include <bits/stdc++.h>

#define VI vector<int>
#define ll long long
using namespace std;

const int maxn = 5e4+50;
const int mod = 1e9+7;

ll qp(ll a, ll n) {
    ll res = 1;
    n %= mod - 1;
    if (n < 0) n += mod - 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll qp(ll a, ll n, int mod) {
    ll res = 1;
    n %= mod - 1;
    if (n < 0) n += mod - 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int n, a[maxn];
const int inf = 1e9+5;

namespace splay_tree {
    int rt[maxn << 2], tot, fa[maxn << 2], son[maxn << 2][2];
    int val[maxn << 2], cnt[maxn << 2], sz[maxn << 2];
    void Push(int o) { sz[o] = sz[son[o][0]] + sz[son[o][1]] + cnt[o]; }
    bool Get(int o) { return son[fa[o]][1] == o; }
    void Clear(int o) { son[o][0] = son[o][1] = fa[o] = val[o] = sz[o] = cnt[o] = 0; }
    void Rotate(int o) {
        int p = fa[o], q = fa[p], ck = Get(o);
        son[p][ck] = son[o][ck ^ 1], fa[son[o][ck ^ 1]] = p;
        son[o][ck ^ 1] = p, son[o][ck ^ 1] = p;
        fa[p] = o, fa[o] = q;
        if (p) son[q][p == son[q][1]] = o;
        Push(p), Push(o);
    }
    void Splay(int &root, int o) {
        for (int f; (f = fa[o]); Rotate(o))
            if (fa[f]) Rotate(Get(o) == Get(f) ? f : o);
        root = o;
    }
    void Insert(int &root, int x) {
        if (!root) {
            val[++tot] = x;
            cnt[tot] ++;
            root = tot;
            Push(root);
            return;
        }
        int cur = root, f = 0;
        while (1) {
            if (val[cur] == x) {
                cnt[cur] ++;
                Push(cur), Push(f);
                Splay(root, cur);
                break;
            }
            f = cur;
            cur = son[cur][val[cur] < x];
            if (!cur) {
                val[++tot] = x;
                cnt[tot] ++;
                fa[tot] = f;
                son[f][val[f] < x] = tot;
                Push(tot), Push(f);
                Splay(root, tot);
                break;
            }
        }
    }
    int GetRank(int &root, int x) {
        int ans = 0, cur = root;
        while (cur) {
            if (x < val[cur]) {
                cur = son[cur][0];
                continue;
            }
            ans += sz[son[cur][0]];
            if (x == val[cur]) {
                Splay(root, cur);
                return ans;
            }
            if (x > val[cur]) {
                ans += cnt[cur];
                cur = son[cur][1];
            }
        }
        return ans;
    }
    int Getkth(int &root, int k) {
        int cur = root;
        while (1) {
            if (son[cur][0] && k <= sz[son[cur][0]]) cur = son[cur][0];
            else {
                k -= cnt[cur] + sz[son[cur][0]];
                if (k <= 0) return cur;
                cur = son[cur][1];
            }
        }
    }
    int Find(int &root, int x) {
        int ans = 0, cur = root;
        while (cur) {
            if (x < val[cur]) {
                cur = son[cur][0];
                continue;
            }
            ans += sz[son[cur][0]];
            if (x == val[cur]) {
                Splay(root, cur);
                return ans + 1;
            }
            ans += cnt[cur];
            cur = son[cur][1];
        }
    }
    int GetPrev(int &root) {
        int cur= son[root][0];
        while (son[cur][1]) cur = son[cur][1];
        return cur;
    }
    int GetPrevVal(int &root, int x) {
        int ans = -inf, cur = root;
        while (cur) {
            if (x > val[cur]) {
                ans = max(ans, val[cur]);
                cur = son[cur][1];
                continue;
            }
            cur = son[cur][0];
        }
        return ans;
    }
    int GetNext(int &root) {
        int cur = son[root][1];
        while (son[cur][0]) cur = son[cur][0];
        return cur;
    }
    int GetNextVal(int &root, int x) {
        int ans = inf, cur = root;
        while (cur) {
            if (x < val[cur]) {
                ans = min(ans, val[cur]);
                cur = son[cur][0];
                continue;
            }
            cur = son[cur][1];
        }
        return ans;
    }
    void Delete(int &root, int x) {
        Find(root, x);
        if (cnt[root] > 1) {
            cnt[root] --;
            Push(root);
            return;
        }
        if (!son[root][0] && !son[root][1]) {
            Clear(root);
            root = 0;
            return;
        }
        int p = GetPrev(root), cur = root;
        Splay(root, p);
        fa[son[cur][1]] = p;
        son[p][1] = son[cur][1];
        Clear(cur);
        Push(root);
    }
}

namespace seg_tree {
    int tree[maxn << 2];
    void build(int rt, int l, int r) {
        for (int i = l; i <= r; ++i) splay_tree::Insert(tree[rt], a[i]);
        if (l == r) return;
        int mid = l + r >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
    }
    void update(int rt, int l, int r, int le, int re, int u, int v) {
        splay_tree::Delete(tree[rt], u); splay_tree::Insert(tree[rt], v);
        if (l == r) return;
        int mid = l + r >> 1;
        if (le <= mid) update(rt << 1, l, mid, le, re, u, v);
        if (re > mid) update(rt << 1 | 1, mid + 1, r, le, re, u, v);
    }
    int QueryRank(int rt, int l, int r, int le, int re, int v) {
        if (le <= l && r <= re) return splay_tree::GetRank(tree[rt], v);
        int mid = l + r >> 1, ans = 0;
        if (le <= mid) ans += QueryRank(rt << 1, l, mid, le, re, v);
        if (re > mid) ans += QueryRank(rt << 1 | 1, mid + 1, r, le, re, v);
        return ans;
    }
    int QueryPrev(int rt, int l, int r, int le, int re, int v) {
        if (le <= l && r <= re) return splay_tree::GetPrevVal(tree[rt], v);
        int mid = l + r >> 1, ans = -inf;
        if (le <= mid) ans = max(ans, QueryPrev(rt << 1, l, mid, le, re, v));
        if (re > mid) ans = max(ans, QueryPrev(rt << 1 | 1, mid + 1, r, le, re, v));
        return ans;
    }
    int QueryNext(int rt, int l, int r, int le, int re, int v) {
        if (le <= l && r <= re) return splay_tree::GetNextVal(tree[rt], v);
        int mid = l + r >> 1, ans = inf;
        if (le <= mid) ans = min(ans, QueryNext(rt << 1, l, mid, le, re, v));
        if (re > mid) ans = min(ans, QueryNext(rt << 1 | 1, mid + 1, r, le, re, v));
        return ans;
    }
    int QueryKth(int le, int re, int k) {
        int l = 0, r = 1e8+10;
        int res = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (QueryRank(1, 1, n, le, re, mid) < k) l = mid + 1, res = mid;
            else r = mid - 1;
        }
        return res;
    }
}

int main(int argc, char* argv[]) {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    splay_tree::tot = 0;
    seg_tree::build(1, 1, n);
    for (int i = 0, op, l, r, pos, k; i < m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", seg_tree::QueryRank(1, 1, n, l, r, k) + 1);
        } else if (op == 2) {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", seg_tree::QueryKth(l, r, k));
        } else if (op == 3) {
            scanf("%d%d", &pos, &k);
            seg_tree::update(1, 1, n, pos, pos, a[pos], k);
            a[pos] = k;
        } else if (op == 4) {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", seg_tree::QueryPrev(1, 1, n, l, r, k));
        } else {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", seg_tree::QueryNext(1, 1, n, l, r, k));
        }
    }
    return 0;
}