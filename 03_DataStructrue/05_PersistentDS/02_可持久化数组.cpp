/*1、操作将u，v合并 2、操作回退 */
const int maxn = 2e5+5;
int n, m, sz;
int root[maxn],ls[maxn*40],rs[maxn*40],v[maxn*40],deep[maxn*40];
int has[maxn];

void build(int &k, int l, int r) {
    if (!k)k = ++sz;
    if (l == r) {
        v[k] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls[k], l, mid);
    build(rs[k], mid + 1, r);
}

void modify(int l, int r, int x, int &y, int pos, int val) {
    y = ++sz;
    if (l == r) {
        v[y] = val;
        deep[y] = deep[x];
        return;
    }
    ls[y] = ls[x];
    rs[y] = rs[x];
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(l, mid, ls[x], ls[y], pos, val);
    else modify(mid + 1, r, rs[x], rs[y], pos, val);
}

int query(int k, int l, int r, int pos) {
    if (l == r)return k;
    int mid = (l + r) >> 1;
    if (pos <= mid)return query(ls[k], l, mid, pos);
    else return query(rs[k], mid + 1, r, pos);
}

void add(int k, int l, int r, int pos) {
    if (l == r) {
        deep[k]++;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)add(ls[k], l, mid, pos);
    else add(rs[k], mid + 1, r, pos);
}

int find(int k, int x) {
    int p = query(k, 1, n, x);
    if (x == v[p])return p;
    return find(k, v[p]);
}

int main() {
    int T = read();
    while (T--) {
        sz = 0;
        memset(root, 0, sizeof root);
        memset(ls, 0, sizeof ls);
        memset(rs, 0, sizeof rs);
        n = read();
        has[0] = n;
        m = read();
        build(root[0], 1, n);
        int f, k, a, b;
        for (int i = 1; i <= m; i++) {
            f = read();
            if (f == 1) {
                root[i] = root[i - 1];
                has[i] = has[i - 1];
                a = read();
                b = read();
                int p = find(root[i], a), q = find(root[i], b);
                if (v[p] == v[q])continue;
                has[i]--;
                if (deep[p] > deep[q])swap(p, q);
                modify(1, n, root[i - 1], root[i], v[p], v[q]);
                if (deep[p] == deep[q])add(root[i], 1, n, v[q]);
            } else if (f == 2) {
                k = read();
                root[i] = root[k];
                has[i] = has[k];
            }
            printf("%d\n", has[i]);
        }
    }
    return 0;
}