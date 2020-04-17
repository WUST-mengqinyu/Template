// a为二分数组，x为需要查找的数，返回最左端和最右端
pair<int, int> F(vector<int> a, int x) {
    int l = 0, r = a.size() - 1;
    int lres = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        int tt = a[mid];
        if (tt >= x) {
            r = mid - 1;
        } else if (tt < x) {
            l = mid + 1;
        }
    }
    if (l >= a.size() || a[l] != x) return make_pair(-1, -1);
    lres = l;
    l = 0, r = a.size() - 1;
    while (l <= r) {
        int mid = l + r >> 1;
        int tt = a[mid];
        if (tt > x) {
            r = mid - 1;
        } else if (tt <= x) {
            l = mid + 1;
        }
    }
    return make_pair(lres, r);
}