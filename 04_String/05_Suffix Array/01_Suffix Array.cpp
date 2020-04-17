char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n;

//build_sa(n + 1, 130), sa, height下标从1开始,rk下标从0开始
void build_sa(int n, int m) 
{
    int *x = t, *y = t2;
    for(int i = 0; i < m; i++) c[i] = 0;
    for(int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for(int i = 1; i < m; i++) c[i] += c[i - 1];
    for(int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1)
    {
        int p = 0;
        for(int i = n - k; i < n; i++) y[p++] = i;
        for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) c[x[y[i]]]++;
        for(int i = 0; i < m; i++) c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for(int i = 1; i < n; i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
        if(p >= n) break;
        m = p;
    }
}

int rk[maxn], height[maxn];

void getHeight()
{
    for(int i = 1; i <= n; i++) rk[sa[i]] = i;
    for(int i = 0, k = 0; i < n; i++)
    {
        if(k) k--;
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]) k++;
        height[rk[i]] = k;
    }
}

int dp[maxn][20];

void RMQ()
{
    for(int i = 1; i <= n; i ++) dp[i][0] = height[i];
    for(int j = 1; (1 << j) < maxn; j ++)
        for(int i = 1; i + (1 << j) - 1 <= n; i ++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r)
{
    int k = 0;
    while((1 << (k + 1)) <= r - l + 1) k ++;
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int lcp(int x, int y)
{
    x = rk[x], y = rk[y];
    if(x > y) swap(x, y);
    return query(x + 1, y);
}                                                                  