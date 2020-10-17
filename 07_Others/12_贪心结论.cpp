// n个区间，挪到使得某个点被所有区间覆盖需要的最少步数时，选择的点是所有区间端点的中位数（mid~mid+1答案都是一样的）

// 2 * n 的格子填数，使得列上的最大和最小的填充方法：最大配最小，次大配次小，以此类推

// n个数，重排后使得相同位置上数不同的最大值为：如果max<=(sum - max)则为sum，如果max>(sum-max)则为2*(sum-max)

// 不重叠区间贪心
pair<int, int> a[maxn];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].second >> a[i].first;
    }
    sort(a + 1, a + 1 + n);
    int res = 1;
    int tmp = a[1].first;
//    printf("%d %d\n", a[1].second, a[1].first);
    for (int i = 2; i <= n; ++i) {
        if (a[i].second > tmp) {
            res ++;
//            printf("%d %d\n", a[i].second, a[i].first);
            tmp = a[i].first;
        }
    }
    printf("%d\n", res);
    return 0;
}
