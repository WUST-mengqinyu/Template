// 简单写法(下标从0开始,只返回长度)
int dp[N];
int LIS(int a[], int n)
{
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++) *lower_bound(dp, dp + n, a[i]) = a[i];
    return lower_bound(dp, dp + n, INF) - dp;
}

// 小常数nlogn求序列用树状数组维护dp即可
// dp[i] = max(dp[j]) + 1 (j < i && a[j] < a[i])