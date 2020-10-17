int r = 1;
for (int i = 1; i <= n; ++i) {
    while (r <= n && !vis[a[r]]) vis[a[r++]] = 1;
    vis[a[i]] = 0;
    R[i] = r - 1;
}
int l = n;
for (int i = n; i >= 1; --i) {
    while (l >= 1 && !vis[a[l]]) vis[a[l--]] = 1;
    vis[a[i]] = 0;
    L[i] = l + 1;
}