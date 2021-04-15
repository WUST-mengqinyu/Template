// 1. 区间 加
// 2. 区间 翻转
// 3. 区间最大值
#define inf 1000000007
#define N 50007
#define ls c[p][0]
#define rs c[p][1]
using namespace std;
int n, m, rt;
int fa[N], val[N], rev[N], mx[N], sz[N], flag[N], c[N][2];

inline void update(int p) {
    sz[p] = sz[ls] + sz[rs] + 1;
    mx[p] = max(mx[ls], mx[rs]);
    mx[p] = max(mx[p], val[p]);
}
inline void pushdown(int p) {
    if (flag[p]) {
        int f = flag[p];
        flag[p] = 0;
        if (ls) { flag[ls] += f, mx[ls] += f, val[ls] += f; }
        if (rs) { flag[rs] += f, mx[rs] += f, val[rs] += f; }
    }
    if (rev[p]) {
        rev[p] ^= 1;
        rev[ls] ^= 1, rev[rs] ^= 1;
        swap(c[p][1], c[p][0]);
    }
}
void rotate(int x, int &k) {
    int y = fa[x], z = fa[y], l, r;
    if (c[y][0] == x) l = 0; else l = 1;
    r = l ^ 1;
    if (y == k) k = x;//交换后x就等于y
    else if (c[z][0] == y) c[z][0] = x;
    else c[z][1] = x;
    fa[x] = z, fa[y] = x, fa[c[x][r]] = y;
    c[y][l] = c[x][r], c[x][r] = y;
    update(y), update(x);
}
void splay(int x, int &k) {
    while (x != k) {
        int y = fa[x], z = fa[y];
        if (y != k) {
            if (c[y][0] == x ^ c[z][0] == y) rotate(x, k);
            else rotate(y, k);
        }
        rotate(x, k);
    }
}
int find(int p, int num) {
    pushdown(p);
    if (sz[ls] >= num) return find(ls, num);
    else if (sz[ls] + 1 == num) return p;
    else return find(rs, num - sz[ls] - 1);
}
void add(int l, int r, int z) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt), splay(y, c[x][1]);
    int now = c[c[x][1]][0];
    val[now] += z, flag[now] += z, mx[now] += z;
}
void spin(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt), splay(y, c[x][1]);
    int now = c[c[x][1]][0];
    rev[now] ^= 1;
}
int query(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt), splay(y, c[x][1]);
    int now = c[c[x][1]][0];
    return mx[now];
}
void build(int l, int r, int p) {
    if (l > r) return;
    if (l == r) {
        fa[l] = p, sz[l] = 1;
        if (l < p) c[p][0] = l;
        else c[p][1] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid - 1, mid), build(mid + 1, r, mid);
    fa[mid] = p;
    if (mid < p) c[p][0] = mid;
    else c[p][1] = mid;
    update(mid);
}
int main() {
    scanf("%d%d", &n, &m);
    mx[0] = -inf;
    build(1, n + 2, 0), rt = (n + 3) >> 1;
    while (m--) {
        int op, x, y, z;
        scanf("%d", &op);
        switch (flag) {
            case 1:
                scanf("%d%d%d", &x, &y, &z);
                add(x, y, z);
                break;
            case 2:
                scanf("%d%d", &x, &y);
                spin(x, y);
                break;
            case 3:
                scanf("%d%d", &x, &y);
                printf("%d\n", query(x, y));
                break;
        }
    }
}