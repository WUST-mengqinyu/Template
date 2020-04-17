struct Fenwick_Tree {
#define type int
    type bit[maxn][maxn];
    int n, m;
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        mem(bit, 0);
    }
    int lowbit(int x) { return x & (-x); }
    void update(int x, int y, type v) {
        int i, j;
        for (i = x; i <= n; i += lowbit(i)) {
            for (j = y; j <= m; j += lowbit(j)) {
                bit[i][j] += v;
            }
        }
    }
    type get(int x, int y) {
        type i, j, res = 0;
        for (i = x; i > 0; i -= lowbit(i)) {
            for (j = y; j > 0; j -= lowbit(j)) {
                res += bit[i][j];
            }
        }
        return res;
    }
    type query(int x1, int x2, int y1, int y2) {
        x1--;
        y1--;
        return get(x2, y2) - get(x1, y2) - get(x2, y1) + get(x1, y1);
    }
#undef type
} tr;

// 二维区间前缀和写法（非树状数组）
inline void range_add(int xa, int ya, int xb, int yb) { add(xa, ya, 1), add(xa, yb + 1, -1), add(xb + 1, ya, -1), add(xb + 1, yb + 1, 1); }
inline ll range_ask(int xa, int ya, int xb, int yb){ return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1); }
inline void build() {
    // 预处理出每个点的单点值
	for (int i = 1; i < n + 5; ++i) {
        for (int j = 1; j < m + 5; ++j) {
            st[i][j] += st[i - 1][j] + st[i][j - 1] - st[i - 1][j - 1];
        }
    }
    // 再求一次处理出每个点的前缀和
    for (int i = 1; i < n + 5; ++i) {
        for (int j = 1; j < m + 5; ++j) {
            if (st[i][j] > 1) st[i][j] = 1;
            st[i][j] += st[i - 1][j] + st[i][j - 1] - st[i - 1][j - 1];
        }
    }
}

// 二维树状数组区间加与求和
ll t1[maxn][maxn], t2[maxn][maxn], t3[maxn][maxn], t4[maxn][maxn];
void add(ll x, ll y, ll z){
    for(int X = x; X <= n; X += X & -X)
        for(int Y = y; Y <= m; Y += Y & -Y){
            t1[X][Y] += z;
            t2[X][Y] += z * x;
            t3[X][Y] += z * y;
            t4[X][Y] += z * x * y;
        }
}
ll ask(ll x, ll y){
    ll res = 0;
    for(int i = x; i; i -= i & -i)
        for(int j = y; j; j -= j & -j)
            res += (x + 1) * (y + 1) * t1[i][j]
                - (y + 1) * t2[i][j]
                - (x + 1) * t3[i][j]
                + t4[i][j];
    return res;
}

// 区间加，询问单点：直接维护前缀差分数组，求单点=普通求前缀和