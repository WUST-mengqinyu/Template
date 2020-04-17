// 循环序列的最大子段和
int a[maxn];
int pre[maxn * 2];
int qu[maxn * 2];
int n, resl, resr, res, k;

int main(int argc, char* argv[]) {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            pre[i] = pre[i - 1] + a[i];
        }
        for (int i = n + 1; i <= 2 * n; ++i) {
            pre[i] = pre[i - 1] + a[i - n];
        }
        res = -0x3f3f3f3f;
        resl = resr = -1;
        int l = 1, r = 0;
        for (int i = 1; i <= 2 * n; ++i) {
            while (l <= r && pre[qu[r]] >= pre[i - 1]) r--;
            qu[++r] = i - 1;
            while (l <= r && qu[l] < i - k) l++;
            int tmp = pre[i] - pre[qu[l]];
            if (tmp > res) {
                res = tmp;
                resl = qu[l] + 1;
                resr = i;
            }
        }
        if (resl > n) resl -= n;
        if (resr > n) resr -= n;
        printf("%d %d %d\n", res, resl, resr);
    }
    return 0;
}