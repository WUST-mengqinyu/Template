int pmax(int x, int y) { return a[x] > a[y] ? x : y; }
int pmin(int x, int y) { return a[x] < a[y] ? x : y; }
void init() {
    for (int i = 1; i <= n; i++) {
        maxx[i][0] = minn[i][0] = i;
    }
    for (int j = 1; 1 << (j - 1) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            int t = 1 << (j - 1);
            maxx[i][j] = pmax(maxx[i][j - 1], maxx[i + t][j - 1]);
            minn[i][j] = pmin(minn[i][j - 1], minn[i + t][j - 1]);
        }
    }
}
int query(int l, int r) {
    int j = 0;
    while ((1 << (j + 1)) <= r - l + 1) j++;
    int i = r - (1 << j) + 1;
//    return pmax(maxx[l][j], maxx[i][j]);
	return pmin(minn[l][j], minn[i][j]);
}