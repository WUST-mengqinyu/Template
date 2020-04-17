int root[100005];
int ls[1800000], rs[1800000], sum[1800000];
int sz = 0;

void insert(int &k, int l, int r, int val){
    if (!k) k = ++sz;
    if (l == r) {
        sum[k] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) insert(ls[k], l, mid, val);
    else insert(rs[k], mid + 1, r, val);
    sum[k] = sum[ls[k]] + sum[rs[k]];
}

int query(int k, int l, int r, int rank) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (sum[ls[k]] >= rank) return query(ls[k], l, mid, rank);
    else return query(rs[k], mid + 1, r, rank - sum[ls[k]]);
}
int merge(int x, int y)
{
    if (!x) return y;
    if (!y) return x;
    ls[x] = merge(ls[x], ls[y]);
    rs[x] = merge(rs[x], rs[y]);
    sum[x] = sum[ls[x]] + sum[rs[x]];
    return x;
}
insert(root[i], 1, n, a[i]);
query(root[p], 1, n, x);