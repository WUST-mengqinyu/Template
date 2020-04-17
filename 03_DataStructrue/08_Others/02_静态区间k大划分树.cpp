// const int maxn = 100010;
int tree[20][maxn];
// 读入sorted并排序，赋值给tree的第0层
int sorted[maxn];
int toleft[20][maxn];
// 保存左子树的和
// ll sum[20][maxn];

// 1, n, 0
void build(int l, int r, int dep) {
    if (l == r) return;
    // sum[dep][0] = 0;
    toleft[dep][0] = 0;
    int mid = l + r >> 1;
    int same = mid - l + 1;
    for (int i = l; i <= r; ++i) {
        if (tree[dep][i] < sorted[mid]) same--;
    }
    int lpos = l, rpos = mid + 1;
    for (int i = l; i <= r; ++i) {
        // sum[dep][i] = sum[dep][i - 1];
        if (tree[dep][i] < sorted[mid]) {
            // sum[dep][i] += tree[dep][i];
            tree[dep + 1][lpos++] = tree[dep][i];
        }
        else if (tree[dep][i] == sorted[mid] && same > 0) {
            // sum[dep][i] += tree[dep][i];
            tree[dep + 1][lpos++] = tree[dep][i];
            same --;
        } else tree[dep + 1][rpos ++] = tree[dep][i];
        toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
    }
    build(l, mid, dep + 1);
    build(mid + 1, r, dep + 1);
}

//(1~k-1)的数的和，注意每次查询前初始化
// ll ress = 0;

// L = 1, R = n， dep = 0, l,r是查询区间
int query(int L, int R, int l, int r, int dep, int k) {
    if (l == r) return tree[dep][l];
    int mid = (L + R) >> 1;
    int cnt = toleft[dep][r] - toleft[dep][l - 1];
    if (cnt >= k) {
        int newl = L + toleft[dep][l - 1] - toleft[dep][L - 1];
        int newr = newl + cnt - 1;
        return query(L, mid, newl, newr, dep + 1, k);
    } else {
        int newr = r + toleft[dep][R] - toleft[dep][r];
        int newl = newr - (r - l - cnt);
        // ress += sum[dep][r] - sum[dep][l - 1];
        return query(mid + 1, R, newl, newr, dep + 1, k - cnt);
    }
}


scan(n), scan(m);
for (int i = 1; i <= n; ++i) {
    scan(sorted[i]);
    tree[0][i] = sorted[i];
}
sort(sorted + 1, sorted + 1 + n);
build(1, n, 0);
int l, r, k;
while (m--) {
    scan(l), scan(r), scan(k);
    printf("%d\n", query(1, n, l, r, 0, k));
}