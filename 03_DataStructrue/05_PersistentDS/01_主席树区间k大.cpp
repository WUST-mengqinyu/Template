// const int maxn = 100005;
int n, m;
int a[maxn];
int root[maxn];
int cnt = 0;
vector<int> b;
struct node {
    int l, r, val;
}p[maxn * 40];

void update(int l, int r, int pre, int &now, int pos) {
    p[now = ++cnt] = p[pre];
    p[now].val++;
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(l, mid, p[pre].l, p[now].l, pos);
    else update(mid + 1, r, p[pre].r, p[now].r, pos);
}

/*
void build(int pre, int &now, int pos) {
    now = pre;
    for (auto i : a[pos]) {
        update(1, n, pre, now, i);
    }
}
*/

int query(int l, int r, int x, int y, int k) {
    if (l == r) return b[l - 1];
    int mid = l + r >> 1;
    int temp = p[p[y].l].val - p[p[x].l].val;
    if (k <= temp) return query(l, mid, p[x].l, p[y].l, k);
    return query(mid + 1, r, p[x].r, p[y].r, k - temp);
}

int main(int argc,char *argv[])
{
    while (scanf("%d%d", &n, &m) != EOF) {
        b.clear();
        cnt = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), b.push_back(a[i]);
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        for (int i = 1; i <= n; ++i) {
            update(1, b.size(), root[i - 1], root[i], lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1);
        }
        int L, R, k;
        while (m--) {
            scanf("%d%d%d", &L, &R, &k);
            printf("%d\n", query(1, b.size(), root[L - 1], root[R], k));
        }
    }
    return 0;
}